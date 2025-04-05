# Wayland
<details>
<summary>wayland는 아래의 입/출력 장치를 지원함</summary>
  
- 입력장치
    - 키보드
    - 마우스
    - 터치 패드
    - 터치 스크린
    - 태블릿
- 출력장치
    - Desktop display
    - Laptop display
    - Mobile display
     
</details>

- 위의 리소스는 모든 wayland application간에 공유되며 wayland compositor가 입력 이벤트를 전달하고 적절한 위치의 창에 추력하도록 함
- 출력에 표시하는 모든 애플리케이션 창을 모으는 과정을 compositing이라 하며 이를 수행하는 소프트웨어가 compositor !

---
### Wayland의 구성요소

1. **Compositor**
- 화면 위에 겹쳐있는 모든 윈도우(client)들을 하나의 스크린 위에 합쳐 보여주며, 하드웨어 이벤트를 제어하고 scenegraph를 통해 이벤트를 수신할 client를 결정해 이벤트를 직접 전달함
- scenegraph = 화면에 있는 내용
- compositor는 이를 이용해 입력된 이벤트가 어떤 client에 해당하는 이벤트인지 인지함
- client로부터 화면 업데이트 요청을 수집해 화면을 재구성하며 ioctl을 직접 발행해 KMS로 페이지 플립을 예약함

2. **Client**
- 화면에 나타낼 각각의 창 의미
- compositor로부터 이벤트를 수신해 ui 업데이트를 수행함
- X11과 달리 client의 렌더링은 compositor가 아닌 client 내에서 이루어지며 업데이트 된 내용을 compositor에게 전달해 화면에 나타낼 것을 요청함

3. **Shell**
- 윈도우를 옮기거나 크기를 변경하고 패널이나 배경화면을 보여주는 역할 수행
- 일반적인 윈도우 환경에서 사용하는 대부분의 기능을 수행함

4. **Seat**
- 키보드, 마우스 등 입력장치를 관리하는 객체 의미

---
## Wayland 동작

![wayland_operate](./img/wayland_operate.png)

- wayland 프로토콜은 렌더링 API가 없음
- 클라이언트가 스스로 렌더링 하기 위해서는 렌더링 라이브러리(Cairo, OpenGL)나 wayland가 지원하는 high-level widget 라이브러리를 사용해야함
- 만약 클라이언트가 소프트웨어 렌더링을 사용하고 결과가 system 메모리에 저장되어 있다면, 버퍼 커뮤니케이션을 구현하기 위해 클라이언트와 컴포지터는 shared memory를 사용할 수 있음 (특별한 복사 없이)
- 전형적인 방법은 클라이언트가 GPU API(OpenGL, OpenGL ES, Vulkan)를 사용해 비디오 메모리 버퍼에 직접 렌더링 하는 것임

![opengl_app_operate](./img/opengl_app_operate.png)
- DRM을 사용하는 리눅스 시스템에서 OpenGL을 사용하는 애플리케이션의 동작 방식
- 기존 OpenGL 애플리케이션과 같이 Wayland 애플리케이션도 EGL을 이용해 direct rendering을 사용함

---
#### Linux graphics system without wayland
![linux_graphics_system_without_wayland](./img/linux_graphics_system_without_wayland.png)

- wayland 없이 OpenGL과 DRM 드라이버를 사용하는 구조
- 애플리케이션 스스로가 OpenGL과 커널 DRM interface를 이용해 최종 이미지를 원하는 영역에 출력해야함

#### Linux graphics system with wayland
![linux_graphics_system_with_wayland](./img/linux_graphics_system_with_wayland.png)

- wayland를 이용해 OpenGL과 DRM 드라이버를 사용하는 구조
- 윈도우 매니저 기능을 하는 wayland가 OpenGL 명령과 KMS 제어에 관여해 애플리케이션의 최종 이미지를 합성하거나 렌더링함
