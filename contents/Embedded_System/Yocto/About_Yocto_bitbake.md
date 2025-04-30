# Yocto와 추상화 개념 & Bitbake

- Yocto란? = 임베디드 장치용 리눅스 배포판 생성 프로젝트 &rarr; Poky 리눅스를 기반으로 만들어짐
     - **커스텀 리눅스 배포를 위한 소프트웨어 스택을 구성하는 도구 및 템플릿의 집합**
     - 리눅스 빌드에 필요한 **bitbake, OpenEmbedded Core, Poky**가 key point
     - OpenEmbedded build system이 리눅스 소프트웨어 스택을 빌드하는데 필요한 정보를 제공하고, 제공된 **bitbake가 빌드 수행**
     - 소스 빌드에 필요한 cross compiler, library 등이 포함됨

![structure_of_Poky](/contents/Embedded_System/img/structure_of_Poky.png)

- meta directory
     - OpenEmbedded Core
     - Bitbake build 도구
&rarr; 참고한 책에서는 Yocto dunfell 버전을 사용하지만 최신 버전은 kikstone임

---
## Bitbake
1. 파이썬 및 셸 스크립트 혼합 코드를 분석하는 작업 스케줄러
2. 임베디드 리눅스의 크로스 컴파일을 위한 패키지 및 관련 파일 빌드에 사용되는 툴

- poky안에 딸린 빌드 도구가 아님 &rarr; Yocto 버전과 일치하는 bitbake 소스를 사용함
- 빌드 수행을 위해 **meta data**를 사용
- **metadata 파일들을 parsing하고 이에 기반해 빌드 수행 및 최종 이미지 생성**

### Metadata
- **소프트웨어를 어떻게 빌드할지, 빌드하려는 소프트웨어들 간에 어떤 의존성이 있는지 기술함**

![types_of_metadata](/contents/Embedded_System/img/types_of_metadata.png)
&rarr; 다섯 종류의 파일에서 사용됨 : **메타 데이터 파일**

> **1. 변수**
> - 모든 메타데이터 파일에서 사용 가능
>
> **2. 실행 가능 함수 or task**
> - bitbake가 실행하는 셸 함수 또는 파이썬 함수
> - 환경 설정 파일에서 사용 불가

- **환경 설정 파일** = 변수의 집합
    - **전역 변수**의 특징을 가짐 ⇒ 다른 메타 데이터 파일에서 사용 가능
    - 확장자 **‘.conf’**
- **레시피 파일**
    - bitbake가 실행할 함수 정의 = **task / 실행이 가능한 메타데이터 모인 파일**
    - 소프트웨어를 어디서 다운로드 받고, 받은 소프트웨어는 어떻게 빌드되어야하고, 빌드된 산출물은 어디에 위치하는지 등의 빌드 전반의 내용
    - 확장자 **‘.bb’**
- **클래스 파일**
    - 빌드를 위한 기능들을 추상화해 레시피 파일이 사용할 수 있게 함
    - 해당 클래스 파일을 상속한 레시피에서만 변수, 함수 사용 가능 → 공식적 내용 공유
    - 상속을 위해 **inherit** 지시자 사용 / 확장자 **‘.bbclass’**
- **레시피 확장 파일**
    - **레시피에서 선언한 변수나 태스크 재정의**
    - 확장자 **‘.bbappend’**
- **인클루드 파일**
    - **클래스, 인클루드 파일 모두 다른 메타데이터 파일과 공유**할 수 있게 해줌
    - 비공식적 내용 공유에 사용 / 확장자 **‘.inc’**
 
---
### Bitbake 문법
1. 변수 타입 X → 모두 문자열로 인식
2. 변수 이름 대문자로 시작
3. 변수에 값 할당 시 큰따옴표 사용

---
### Bitbake 실행
- **bitbake/bin**의 절대 경로를 PATH 환경 변수에 추가 → bitbake 파일이 모든 경로에서 실행 가능하도록

![steps_for_execute_bitbake](/contents/Embedded_System/img/steps_for_execute_bitbake.png)

> 1. **BBPATH 설정 및 bblayers.conf 파일 탐색**
>     - bitbake가 특정 디렉토리의 metadata를 인식하게 함
>     - BBPATH 변수에 저장된 경로 중 **‘.conf’ / ‘.bbclass’** 파일을 찾음
> 2. **bitbake.conf의 BBLAYERS 변수로 layer.conf 분석**
> 3. **layer.conf의 BBFILES 변수로 .bb 경로 탐색**
> 4. **BBPATH로 bitbake.conf 파일 탐색**
> 5. **BBPATH로  .bbclass 탐색 및 분석**
> 6. **분석한 메타데이터 기반으로 .bb 파일 분석**
>     - 클래스와 레시피 파일에서 정의된 태스크는 **Task chain**으로 실행 순서가 정해짐
  
- bitbake를 통한 레시피 파일 실행
    
    ```python
    $ bitbake <recipe file name>
    $ bitbake <recipe file name> -c <task name>
    ```
    
    - 수행한 테스크 다시 수행 시, **이전 태스크 변경 여부와 실행 이력을 확인함**

#### bblayes.conf 파일
- **bitbake 처음 수행 시 bblayers.conf를 먼저 찾음**
- conf 디렉토리 내의 bblayers.conf는 **bitbake에게 빌드 수행을 위한 레이어들의 경로를** 알려줌
    
    ```python
    BBLAYERS ?= "\
    	/home/iz/bitbake-test/mylayer \ 
    "
    ```
    
#### layer.conf 파일
- bitbake에게 **현재 레이어의 경로** 및 **레이어 내의 레시피 파일들의 경로**를 알려줌
    
    ```python
    BBPATH .= "  ${LAYERDIR)"
    BBFILES - ? ""${LAYERDIR}/*.bb"  # 레이어의 레시피 및 레시피 확장 파일 경로
    BBFILE_COLLECTIONS - ? ""mylayer"  # laye.conf를 포함하는 레이어의 이름
    BBFILE_PATTERN_mylayer := ,  A${LAYERDIR}/"  # 모든 레이어의 레시피 파일이 저장된 경로
    ```

#### bitbake.conf 파일
- 기본적인 환경 설정 / 각 단계에서 만들어진 산출물들을 지정한 디렉터리에 저장
    
    ```python
    PN = "${bb.parse.vars-from_file(d.getVar('FILE', False),d)[0]or 'defaultpkgname'}"
    TMPDIR = "$(TOPDIR)/tmp"
    CACHE = "${TMPDIR}/cache"
    STAMP = "${TMPDIR}/${PN}/stamps"
    T     = "${TMPDIR}/${PN}/work")
    B     = "${TMPDIR}/${PN}"
    ```
    
    - **TOPDIR**은 **Poky가 포함된** 빌드 시스템에서 **build 디렉토리** 의미
    - **TMPDIR** = tmp 디렉토리 : 산출물 저장 위치
    - **PN** = pakage name :  **레시피 파일 이름**
    - **CACHE** : 메타데이터 분석 기록
    - **STAMP** : bitbake가 **태스크 수행 완료 시 생성**하는 파일의 경로
        - 재빌드 시 해당 태스크의 stamp 파일이 존재하면 다시 실행하지 않고 건너뜀
    - **T** : 태스크 실행 로그, 스크립트 파일 등 임시 파일 저장 디렉토리
    - **B** : 레시피 빌드 과정에서 함수를 실행하는 디렉토리 / 빌드 과정에서의 임시 파일들 & 빌드 결과물 등 저장

![steps_for_execute_bitbake2](/contents/Embedded_System/img/steps_for_execute_bitbake2.png)

![openembedded_architecture_workflow](/contents/Embedded_System/img/openembedded_architecture_workflow.png)

![steps_for_analyze_bitbake](/contents/Embedded_System/img/steps_for_analyze_bitbake.png)

