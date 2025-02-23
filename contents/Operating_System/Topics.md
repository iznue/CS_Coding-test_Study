# Operating System
- user가 사용하는 **application과 hardware 사이**에서 동작하는 소프트웨어 계층
- 응용프로그램이 요청하는 **시스템 리소스를 효율적으로 분배하고, 지원하는 소프트웨어**

[Operating System detail](./Operating_system.md)

---
## Memory
- RAM(Random access memory)의 다른 표현으로, CPU가 처리할 데이터나 명령어들을 임시로 저장하는 작업 공간 역할
- 프로그램 실행을 위해 먼저 프로그램이 메모리에 로드되어야 함
- 프로그램을 실행하게 되면 **OS는 메모리에 공간을 할당함**

#### 메모리 구조 
![memory_structure](./img/memory_structure.png)

- Code : 실행할 프로그램의 코드
- Data : 전역 변수, 정적 변수
- Heap : 런타임 시 크기가 결정됨 (사용자의 동적 할당)
- Stack : 컴파일 타임에 크기가 결정됨
    - Compile time : 작성한 소스코드가 기계가 읽을 수 있는 형태로 변환되는 과정
    - Run time : 컴파일 과정을 마친 컴퓨터 프로그램이 실행되고 있는 환경 또는 동작 시간

[Memory detail](./Memory.md)