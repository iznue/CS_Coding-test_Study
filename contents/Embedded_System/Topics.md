# Embedded System
- 특정한 기능을 수행하도록 설계된 **내장형 컴퓨팅 시스템**
- 제품이 출시될 때 하드웨어 장치에 sw가 이미 내재되어 있음 &rarr; HW와 SW 중간에 있다는 의미로 **'Firmware'**라 함
- ***HW 환경을 고려한 개발 필수!*** 

#### 임베디드 SW와 일반 응용 SW의 다른 점
- 임베디드 SW
     - HW와 밀접하게 결합되어 있으므로 해당 장치나 기계에서만 사용 가능
     - 데이터 처리보다 HW 제어가 주 목적
- 일반응용 SW
     - 운영체계가 같으면 어떤 PC에서도 사용 가능
     - 데이터 처리가 주 목적이므로 데이터를 저장하는 DB가 중요함

#### 왜 임베디드 개발에 C, C++이 용이한가?

---
## Yocto
- **하드웨어에 상관없이 작동하는 커스텀 리눅스 개발을 도와주는 오픈소스 프로젝트**
- tool chain, kernel, root file system등과 런타임에 설치할 수 있는 바이너리 패키지와 패키지 관리자까지 설치 가능한 강력한 빌드 시스템
- 여러 **레이어**로 구성돼 있으며 레이어들은 관습적으로 **meta-**라는 접두어를 가짐
     - meta : OpenEmbedded의 OE-Core
     - meta-poky : Poky의 배포판에 해당하는 메타 데이터
     - meta-yocto-bsp : Yocto project가 지원하는 머신에 대한 bsp 포함

[Yocto와 추상화 개념 / bitbake](./About_Yocto_bitbake.md)

[Poky란 ?](./Poky.md)

[빌드 속도 개선을 위한 작업들](./Tasks_for_improve_build_speed.md)

[레이어 & 레시피 생성](./Create_layer_recipe.md)

[초기화 관리자 추가 및 로그 파일을 통한 디버깅](./Add_initial_manager_debugging_through_logfile.md)

[유용한 오픈임베디드 코어 클래스 기능을 사용한 빌드 최적화](./Optimize_build_using_openembedded_core_class.md)

---
## CI / CD
- 소프트웨어 개발 및 배포를 자동화 하는 프로세스 &rarr; 새로운 기능을 빠르고 안정적으로 제공

### Continuous Integration (CI, 지속적 통합)
- 여러 개발자가 작성한 코드 변경 사항을 주기적으로 통합하고 자동으로 테스트하여 오류를 빠르게 발견하는 프로세스

#### **CI 주요 단계**
> 1. 개발자가 새로운 코드 변경 사항을 Git등의 **형상 관리 시스템**에 Push
> 2. 자동으로 빌드(Build) 수행
> 3. 유닛 테스트(Unit Test), 통합 테스트(Integration Test) 진행
> 4. 코드 품질 유지를 위해 정적 분석 및 코드 리뷰 도구 사용

**➡️ CI를 통해 코드 변경 사항이 문제없이 빌드 & 테스트되는지 확인**

#### CI 주요 도구 
- Jenkins, Github Actions, GitLab CI/CD, CircleCI, Travis CI

### Continuous Deployment (CD, 지속적 배포)
- CI 이후 배포 단계를 자동화하여 실제 환경에 안정적으로 전달되는 것이 목표
- Continuous Delivery & Continuous Deployment로 나뉨

#### Continuous Delivery 
- CI 과정을 거친 후 운영 환경에 배포할 준비가 된 상태로 자동화 &rarr; 실제 배포는 사람의 승인 후 진행
- Amazon, google 등

#### Continuous Deployment
- CI/CD 파이프라인 끝단까지 **완전 자동화** &rarr; 사람의 개입 없이 배포가 이루어져 신속한 서비스 업데이트 가능
- Netfilx, Facebook, Twitter 등

---
## OTA (Over the Air)
- 무선 네트워크(wi-fi, 셀룰러, V2X 등)를 통해 소프트웨어 or 펌웨어 등을 원격으로 업데이트하는 기술
    - **FOTA (Firmware Over-The-Air)**: 펌웨어 업데이트
    - **SOTA (Software Over-The-Air)**: 소프트웨어 업데이트
    - **DOTA (Data Over-The-Air)**: 데이터 전송을 통한 학습 및 설정 변경
 
#### OTA의 핵심 요소
> 1. **서버** : 클라우드 또는 원격 서버에서 소프트웨어 업데이트 파일을 관리하고 배포함
> 2. **네트워크 연결** : Wi-Fi, LTE, 5G 등 무선 네트워크를 이용하여 업데이트를 전송함
> 3. **디바이스(클라이언트)** : 업데이트를 적용할 대상 장치(스마트폰, 자동차, IoT 디바이스 등)
> 4. **보안 및 인증** :업데이트 파일이 위변조되지 않도록 보안 인증을 수행하고, 신뢰할 수 있는 소스에서만 다운로드 되도록 보장
>     - 업데이트 과정에서 보안 위협 (예: 중간자 공격, 펌웨어 위-변조, 비인가 접근)이 발생할 수 있으므로 이를 방어하는 보안 메커니즘이 필요함
>       1. 암호화 기술 적용 : 데이터 전송 보안
>       2. 디지털 서명 사용 : 펌웨어 인증
>       3. 보안 부트로더 적용 : 비인가 접근 방어
>       4. 접근 제어 시스템 강화 : 비인가 접근 방어

[OTA_RAUC](./RAUC.md)

[OTA detail _ secure](./OTA.md)

---