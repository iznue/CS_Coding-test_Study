# RAUC (Robust auto-update controller)

- meta-rauc = Yocto 프로젝트에 통합하기 위한 yocto layer (meta layer)
- linux 기반 시스템에서 신뢰할 수 있는 **A/B 시스템 업데이트** 및 **OTA 업데이트**를 수행하는 프레임워크
- RAUC에서 업데이트를 수행하려면 **`.raucb`** 파일 필요
    - 단순 압축 파일이 아닌, RAUC 시스템이 인식할 수 있도록 특정 메타데이터와 서명이 포함된 이미지 파일

- 파일 구조 예
    
      update.raucb
      ├── manifest.rauc     # 업데이트 메타데이터
      ├── boot.img          # 부트로더 이미지 (선택적)
      ├── rootfs.img        # 루트 파일 시스템 이미지
      ├── kernel.img        # 커널 이미지 (선택적)
      └── signature.pem     # 디지털 서명 파일 (업데이트 인증용)
    - `manifest.rauc`→ 업데이트할 대상, 버전 정보, 파티션 정보, 설치 방법 등을 정의하는 파일
    - `boot.img`→ 부트로더 업데이트가 필요한 경우 포함 (예: U-Boot, GRUB)
    - `rootfs.img`→ 새로운 루트 파일 시스템 이미지
    - `kernel.img`→ 새로운 커널 이미지 (선택적)
    - `signature.pem`→ 업데이트가 신뢰할 수 있는지 확인하기 위한 디지털 서명

⇒ 패키징된 `,raucb` 파일이 OTA 서버(git repo)에 업로드되고, 디바이스가 이를 다운로드해서 업데이트 수행

### meta-rauc 주요 기능

1. RAUC 패키지 제공 : Yocto 빌드 시스템에서 rauc를 쉽게 포함하도록 도움
2. 이미지 생성 지원 : rauc 업데이트 시스템에 맞는 **Bundled Image** 생성
3. 비밀 키 및 서명 기능 지원 : 보안성을 위한 업데이트 이미지 서명 및 검증
4. A/B 업데이트 구조 지원 : 업데이트 도중 문제 발생 시 롤백이 가능하도록 설계됨
5. OTA 및 오프라인 업데이트 지원 : 네트워크를 통한 원격 업데이트

---
## A/B 시스템 업데이트
- 도중에 중단되지 않으며 신뢰성 있는 소프트웨어 업데이트를 제공하기 위해 2개의 독립적인 파티션을 활용하는 업데이트 방식
- Ex : 시스템에 두 개의 파티션 세트 (A,B)가 존재 → rootfs_A, rootfs_B
    - 실행 중인 파티션 (A)에서 시스템이 동작하는 동안, **업데이트는 비활성 파티션 (B)에 적용**
    - 업데이트가 완료되면 부트로더가 **B 파티션을 부팅하도록 변경**
    - 새로운 파티션에서 부팅 후 정상 작동 시 해당 파티션(B) 활성화
    - 정상 작동하지 않으면 **자동으로 이전 파티션(A)로 롤백**

---
### RAUC 적용

- **기본 RAUC 적용 방식**
    - `meta-rauc` 및 `meta-rauc-raspberrypi`를 Yocto 프로젝트에 추가
    - A/B 파티션을 구성하고 `rootfs_A`, `rootfs_B`만 업데이트 가능
    - 하지만 기본 설정에서는 **kernel, dtb 등 boot 파티션은 업데이트되지 않음**
- **Boot까지 업데이트하려면**
    - `boot` 파티션을 포함하여 RAUC bundle을 구성해야 함
    - `uboot` 혹은 `grub`을 설정하여 새로운 커널로 부팅할 수 있도록 해야 함
1. 개발 후 sw 빌드
    1. 최신 코드에 대한 새로운 rootfs 이미지 및 kernel 이미지 생성
    2. `rauc bundle` 명령어를 사용해 `.raucb` 업데이트 파일 생성
2. github actions가 자동으로 rauc bundle 업로드
    1. `update.raucb` 파일이 git repo 또는 OTA 서버에 push
    2. 디바이스는 OTA 서버를 주기적으로 확인하고 새로운 업데이트가 있는지 체크
3. 디바이스에서 업데이트 실행
    1. RAUC가 `.raucb` 파일의 서명을 검증해 업데이트의 무결성 확인
    2. 기존 시스템과 병렬로 A/B 업데이트 수행
4. 롤백 지원 

- **Yocto에서 RAUC 적용**
    1. `meta-rauc` 및 `meta-rauc-raspberrypi` 추가
        - `meta-rauc-raspberrypi` 사용 시 다음 레이어가 필요
            - `openembedded-core`
            - `meta-rauc`
            - `meta-raspberrypi` / (raspberry pi5의 경우) `meta-lts-mixins`
    2. A/B 파티션 구성 → WKS 파일 수정 (파티션 구조 정의)
        - WKS : 임베디드 리눅 시스템에서 A/B 파티션을 포함한 **디스크 이미지(파티션) 레이아웃** 정의 파일
            - A/B 파티션 구조 정의 : rootfs_A, rootfs_B, boot, data 등
            - 파티션 크기 및 파일 시스템 종류 설정 : ext4, vfat, squashfs 등
            - 부트로더 설치 위치 지정 : MBR, GPT
            - OTA 업데이트를 고려한 파티션 매핑
    3. RAUC 시스템 설정 (system.conf)
    4. RAUC 번들 생성 (번들 생성 시 빌드 옵션 설정 필요 : local.conf) → 빌드 수행 시 `.raucb` 번들 생성됨
    5. (USB, network, SCP)를 이용해 번들을 타겟 보드에 복사 → 타겟 보드에서 업데이트 (rauc install로 수행)
    6. 부팅 및 검증 → 업데이트된 커널 및 루트 파일 시스템으로 부팅, 실패하는 경우 이전 파티션으로 롤백
    
    +) 7. hawkBit로 OTA 업데이트 자동화 &rarr; 클라이언트 설치 / 서버 설정
    <details>
    <summary>hawkBit ?</summary>


    &rarr; **Eclipse Foundation**에서 개발한 **OTA(Over-the-Air) 소프트웨어 업데이트 관리 솔루션**

    - 주로 **임베디드 시스템, IoT 디바이스, 자동차 및 산업용 장비**의 원격 업데이트를 관리하는 데 사용
    - **완전한 OTA 업데이트 관리 시스템**: 업데이트 배포, 진행 상태 모니터링, 롤백 지원
    - **RAUC, SWUpdate, Mender 등과 연동 가능**
    - **대규모 디바이스 관리**: 수천~수백만 개의 디바이스를 업데이트할 수 있음
    - **REST API 지원**: 클라이언트 및 외부 서비스와의 연동이 쉬움


    **1. 중앙 집중식 OTA 업데이트 관리**
    - 여러 개의 디바이스를 **그룹화하여 일괄 업데이트** 가능
    - 개별 디바이스 또는 특정 그룹에만 업데이트 적용 가능
    - 업데이트 진행 상황을 실시간으로 모니터링할 수 있음


    **2. 다양한 업데이트 방식 지원**
    - **Full Image Update**: 전체 OS 또는 파일 시스템 업데이트
    - **Delta Update**: 변경된 부분만 업데이트하여 네트워크 사용량 절감
    - **Application Update**: 개별 애플리케이션 업데이트 가능


    **3. A/B 시스템 및 롤백 기능 지원**    
    - **RAUC, SWUpdate 등과 연동 가능**하여 A/B 파티션 업데이트를 지원
    - 업데이트 실패 시 **자동으로 이전 버전으로 롤백**


    **4. REST API 기반 연동**    
    - REST API를 통해 클라이언트와 통신
    - JSON 기반 요청/응답으로 사용이 간편

    </details>

---
#### hawkBit을 **RAUC 기반 OTA 업데이트**에 적용하는 경우:

1. **RAUC 번들(.raucb) 생성**
    - `bitbake rauc bundle`을 이용해 `.raucb` 파일 생성
  
2. **hawkBit 서버에 RAUC 번들 업로드**
    - hawkBit 웹 UI 또는 REST API를 사용해 `.raucb` 파일 등록

3. **디바이스에서 hawkBit 클라이언트 실행**
    - `rauc-hawkbit-client`가 서버에 접속하여 새로운 업데이트 확인

4. **업데이트 다운로드 및 설치**
    - `rauc install update.raucb` 명령어를 실행하여 업데이트 수행

5. **업데이트 성공/실패 상태 보고**
    - 업데이트 성공: 정상 부팅 후 `hawkBit 서버`에 상태 보고
    - 업데이트 실패: 자동 롤백 후 기존 버전 유지

