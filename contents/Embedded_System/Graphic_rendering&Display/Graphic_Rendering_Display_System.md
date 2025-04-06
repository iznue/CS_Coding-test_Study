# Linux에서의 GUI Architecture
![gui_operate](/contents/Embedded_System/img/gui_operate.png)

> **동작 흐름**
> 
>     사용자 입력 → Graphical Interface → Display Server (X11 or Wayland) → Kernel → HW
>
>     HW 결과 → Kernel → Display Server → Graphical Interface (GUI 반영)

1. **User**
    - 최종 사용자. 키보드, 마우스, 터치 등을 통해 시스템과 상호작용
2. **Graphical Interface**
    - 사용자가 직접 보는 UI 요소. Desktop Environment를 포함함 (GNOME Shell, KDE Plasma 등)
3. **Display Server**
    - 그래픽 출력과 입력 이벤트를 관리하는 중간 관리자, 그래픽 인터페이스와 커널 사이에서 처리함 (Wayland, Weston, X.Org Server 등)
4. **Window Manager**
    - 창의 크기 조정, 위치 이동 등 윈도우 자체를 제어. Display server와 협력해 창의 레이아웃을 담당함 (Mutter, OpenBox 등)
5. **Kernel**
    - 하드웨어와 소프트웨어의 인터페이스 역할, 입력장치 & 출력장치와 직접 통신 (Linux, FreeBSD Kernel 등)
6. **Hardware**
    - CPU, GPU, 디스플레이, 키보드, 마우스 등의 물리적인 장치

---
# X11
- 리눅스 환경의 각종 애플리케이션과 유틸리티에 대해 GUI를 제공하며, 플랫폼과 독립적으로 작동하는 그래픽 시스템
- 네트워크 기반의 그래픽 환경을 지원하며 이기종 시스템 사이에서도 사용가능함
- 스크롤바, 아이콘, 색상 등 그래픽 환경 자원들이 특정 형태로 정의되어 있지 않음
- 디스플레이 장치에 의존적이지 않으며 원하는 인터페이스를 만들 수 있음

- X-윈도우는 네트워크 프로토콜(X 프로토콜) 기반의 클라이언트 / 서버 시스템임
    - **서버**는 클라이언트들의 디스플레이에 관한 접근 허용, 클라이언트 간의 자원공유, 네트워크 메시지 전달, 클라이언트와 입출력 기기와의 중계를 담당함
    - **클라이언트**는 애플리케이션으로 X 서버가 제공하는 기능들을 이용함

- 오픈 데스크톱 환경으로 KDE, GNOME, XFCE 등이 있음

[X11 System](./X11.md)

---
# Wayland 
- Wayland는 X11을 대체하는 디스플레이 서버 프로토콜로, 간단하며 보안성 높은 그래픽 구성을 목표로 함
- 리눅스 데스크탑 환경을 구현하기 위한 프로토콜로, 컴포지터와 클라이언트의 통신을 지원함
- X11과 달리 컴포지터를 직접 구현하지 않으며, 대신 프로토콜과 관련 API를 제공하고 컴포지터와 쉘은 서드파티가 구현하도록 함

&rarr; 따라서 유연하며 확장성있는 구조를 취하며 Wayfire와 같이 창의적인 데스크탑 환경을 만들 수 있게 되었음

- 데스크탑 환경은 크게 **컴포지터**와 **쉘**로 구분됨
    - UI가 쉘을 그리고, 애플리케이션들의 창이 겹쳐졌을 때 처리를 컴포지터가 함
- Wayland는 컴포지터와 쉘의 구현을 돕는 API와 쉘이 애플리케이션과 통신할 수 있도록 프로토콜을 제공함

- Wayland 이전에는 X11이 컴포지터(X Server)의 역할을 했으며, 이 위에서 Gnome, KDE와 같은 서드파티 쉘이 동작했음
- 하지만 커널 구조가 많이 변경되면서 이전에는 X11에서 처리했던 많은 일들이 DRI, DRM 등을 통해 커널이 처리하기 시작했음

&rarr; 즉 X11이라는 단일 컴포지터가 모든 쉘을 관리하는 모델은 리눅스 GUI 환경 변화를 따라오기에는 너무 거대했기에 Wayland가 탄생함

> wayland를 사용하는 대표적인 이유
> 1. 기존 X11대비 경량화, 체계화된 framework
>     - 기존 X11이 사용하지 않는 부분을 제거하고 필요한 부분만을 구현함
>     - 표준 GEM/DRM 스택을 이용해 최대한 단순하게 구현함 (커널에서 DRM/GEM을 지원해 더 이상 user framework가 복잡해질 필요가 없음)
>     - X11의 1/10의 크기
> 2. Genivi, AGL, Tizen 플랫폼에서 사용함

### Wayland & X Window
- wayland는 기존 X window를 더 단순하게 바꾸려는 목적으로 wayland 레퍼런스 컴포지터인 weston의 개발이 함께 시작됨
- X window에서 수행되던 많은 하부 기능들이 커널이나 라이브러리로 옮겨져 사용되지 않음에도 불구하고 user는 잔존해 있는 X protocol을 지원해야만 했기에 해당 wayland 오픈소스 프로젝트가 시작됨

|X window|wayland|
|---|---|
|독립적인 프로세스로서 동작|라이브러리 형태로 구현되어 OS의 오버헤드가 줄어듦|
|서버와 컴포지터가 분리되어 있음|서버와 컴포지터가 하나로 합쳐져 불필요한 통신이 줄어듦|
|렌더링을 서버가 담당|렌더링을 크라이언트가 담당하여 서버와의 복잡도가 감소함|
|X 서버가 클라이언트, 컴포지터, 커널간의 모든 동작을 중개함|서버가 클라이언트와 커널만 중개함|
|Window Manager + X server로 구현이 복잡함|Compositor가 모든 역할을 함|
|X.Org Server|Weston, Kwin, GNOME Mutter 등|

### Wayland 동작 과정
![wayland](/contents/Embedded_System/img/wayland.png)
1. 커널은 이벤트(예: input event)를 가져와 컴포지터로 전달함
2. 컴포지터는 어떤 윈도우가 이벤트를 수신해야하는지 결정함
3. 클라이언트는 이벤트를 수신하면 클라이언트에서 렌더링이 발생함. 클라이언트가 컴포지터에게 업데이트된 영역을 표시하는 요청만 보냄
4. 컴포지터는 클라이언트로부터 요청을 받은 다음 화면을 다시 구성하고, 직접 ioctl을 실행해 KMS로 최종화면을 요청함

- 애플리케이션은 EGL을 사용해 직접 컨텐츠를 그리고, compositor와(새 컨텐츠를 렌더링했는지) 통신함
- EGL은 DRM API를 사용해 버퍼에 엑세스 할 수 있으며, 프레임 버퍼는 DRM에 의해 관리됨

[Wayland](./Wayland.md)

---
# Weston
- wayland는 라이브러리로써 X11을 대체하기 위해 Weston과 같은 컴포지터를 필요로 함
- wayland는 결국 protocol / compositor를 구현하며 윈도우들을 여러 계층으로(레이어) 구분해 관리함
- shell plugin(desktop-shell, xdg-shell...)을 지원하며 shell을 이용해 출력되는 각 윈도우(뷰)의 순서를 결정함
- 윈도우를 화면에 나타나게 하거나 위치를 옮기거나 크기를 변경하는 기능을 지원함

![weston](/contents/Embedded_System/img/weston.png)

- weston compositor는 weston의 동작을 준비 / 실행하는 핵심 component임
    1. wayland 객체, backend 컴포넌트, shell 컴포넌트를 생성 / 로딩 / 실행
    2. 주요 wayland interface의 동작 (=컴포지팅) 정의
- weston 컴포지터 코드는 compositor 폴더에서 찾을 수 있으며, **libweston** 폴더를 참조함

---
# OpenGL
- 그래픽 렌더링 표준. 라이브러리가 아닌 문서임
- 2D/3D 그래픽을 GPU를 통해 직접 렌더링할 수 있게 해주는 API
- GStreamer, Qt, 게임엔진 등에서 사용됨
- 그래픽 처리 장치 제조업체에서 구현해 그래픽 카드에 드라이버와 함께 제공되며 보통 이 코드들을 라이브러리처럼 가져다 사용함

>      OpenGL app (Qt, GLFW, SDL ...)
>                    ↓
>     OpenGL API 호출 → glDrawArrays(), glBindTexture()
>                    ↓
>     EGL / GLX / WGL → Context 생성 및 관리
>                    ↓
>      GPU Driver (Mesa, NVIDIA, AMD)
>                    ↓
>       DRM / KMS or X11 or Wayland
>                    ↓
>               디스플레이 출력

|구성요소|설명|
|---|---|
|GLX / EGL|X11 또는 wayland / DRM에서 OpenGL Context를 생성하기 위한 라이브러리|
|Shaders|GPU에서 동작하는 프로그램|
|Framebuffer|최종 이미지가 그려지는 영역|
|Texture / VBO|비디오 프레임, 이미지 등을 GPU에 업로드할 때 사용|

---
# GStreamer
- 오디오와 비디오 스트리밍 및 처리 프레임워크
- 애플리케이션에서 멀티미디어 처리 (재생, 인코딩, 디코딩, 필터링 등)을 쉽게 구현할 수 있게 해줌
- **플러그인 기반 파이프라인 아키텍처로 동작함**

>     File Source → Decoder → Converter/Scaler → Video Sink
>                                     ↓
>                       OpenGL or XVideo or DRM Sink

### 렌더링 방식
1. **OpenGL 기반 렌더링 (glimagesink)**
    - GStreamer는 OpenGL context를 만들고, 비디오 프레임을 텍스처로 렌더링함
    - QtQuick과 같이 GPU 기반 GUI와 통합하기 좋음
2. **DRM 기반 렌더링 (kmssink)**
    - X 서버 없이 직접 프레임버퍼에 출력
    - 하드웨어 가속된 재생 가능
3. **X11 기반 (xvimagesink, ximagesink)**
    - X 서버를 통해 비디오 출력. 비교적 구형 방식임

---
# DRM (Direct Rendering Manager) & KMS (Kernel Mode Setting)
- 리눅스 커널에서 GPU와 디스플레이 출력을 직접 제어하는 서브시스템
- 사용자 공간의 애플리케이션이 GPU를 통해 직접 렌더링 가능하게 함 (**X11 없이도 동작**)

|구성요소|설명|
|---|---|
|DRM|GPU에 직접 접근할 수 있는 인터페이스 (`/dev/dri/card0`)|
|KMS|화면 해상도, 주파수, 모니터 연결 등을 설정|
|Framebuffer|그래픽 데이터가 실제 메모리에 존재하는 공간 (색 정보 포함)|
