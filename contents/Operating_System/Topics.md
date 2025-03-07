# Operating System
- user가 사용하는 **application과 hardware 사이**에서 동작하는 소프트웨어 계층
- 응용프로그램이 요청하는 **시스템 리소스를 효율적으로 분배하고, 지원하는 소프트웨어**

[Operating System detail](./Operating_system.md)

<details>
<summary>Table of Contents</summary>

- [Memory](#memory)
- [Process VS Thread](#process--thread)
- [PCB](#process-control-block-pcb)
- [Context-Switching](#context-switching)

</details>

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

--- 
## Process VS Thread
- **프로세스는 서로 다른 메모리 공간에서 실행**되는 반면 동일한 프로세스의 **스레드는 공유 메모리 공간에서 실행**된다는 점에서 차이가 있음
&rarr; ***스레드는 하나에서 오류가 발생하면 같은 프로세스 내의 다른 스레드 모두가 강제 종료됨 but 프로세스는 한 프로세스가 강제 종료되어도 공유 자원을 손상시키는 경우가 아니라면 다른 프로세스에 영향을 주지 않음***

#### Program & Process
- **프로그램** : 특정 작업을 수행하기 위해 작성된 지침 &rarr; 디스크 or 다른 저장 매체에 저장되는 정적 entity
    - 프로그램을 실행하면 운영체제는 해당 프로그램을 디스크에서 시스템 메로리로 로드하고 실행
    - **프로그램의 실행 중인 인스턴스** = **프로세스** &rarr; 각 프로세스에는 자체 메모리 공간과 시스템 리소스가 있음
    - ***파일 단위로 저장 장치에 저장되며, 아직 실행되지 않은 상태의 코드 덩어리***
- **프로그램은 정적**이지만 **프로세스는 동적**
- 동일 프로그램의 여러 인스턴스를 동시에 실행해 여러 프로세스 생성 가능 &rarr; 각 프로세스는 자체 메모리와 리소스를 가지며 독립적

⇒ **프로그램은 코드, 프로세스는 코드가 실행될 때 발생**

## Process & Thread
- 프로세스는 자체 메모리 공간이 있는 독립적인(애플리케이션에 대한 격리 : **isolation** 제공) entity로 **프로그램의 실행 중인 인스턴스**
- 스레드는 **프로세스 내의 더 가벼운 공유 메모리**로 병렬 실행을 가능하게 함
    - **프로세스의 하위 집합이며 경량 프로세스**라고도 함 &rarr; 프로세스에는 둘 이상의 스레드가 존재할 수 있으며 **스케줄러에 의해 독립적으로 관리됨** = 동시성 : **concurrency**
    - ***프로세스의 실행 단위, 같은 프로세스 내에 있는 스레드끼리는 프로세스의 자원을 공유할 수 있음***
    - 스레드는 프로세스 메모리 영역을 공유하므로 어떤 스레드 하나에서 오류가 발생하면 같은 프로세스 내의 다른 스레드 모두가 강제로 종료됨
 
[Process & Thread detail](./Process_Thread.md)

---
## Process Control Block (PCB)
- 특정 프로세스에 대한 정보를 담고 있는 운영체제의 자료구조
- 프로세스는 운영체제의 스케줄링 알고리즘에 따라 CPU를 할당받음
- 작업 진행 중 프로세스 전환이 발생하면 하던 일을 저장하고 CPU를 반환해야 함
&rarr; 나중에 스케줄링에 의해 재실행 되었을 때 이전에 어디까지 작업이 진행되었는지 정보를 알아야 함 ⇒ ***이 정보가 담긴 공간이 PCB***
- 프로세스 생성과 동시에 그 프로세스의 고유한 PCB도 함께 생성됨, 프로세스 완료 시 PCB는 제거됨

#### PCB에 저장되는 정보
<details>
<summary>프로세스 제어 블록</summary>

![pcb](./img/pcb.png)

- 프로세스 식별자 (Process ID, PID)
- 프로세스 상태 (Process state) : new, ready, running, waiting, terminated
- 프로그램 카운터 (Program counter) : 프로세스가 다음에 실행할 명령어의 주소를 가리킴
- CPU 레지스터 : Accumulator, Index Register, 범용 레지스터 등
- CPU 스케줄링 정보 : 프로세스 우선순위, 최종 실행 시각, CPU 점유 시간 등
- 메모리 관리 정보 : Page table, Segment table 등
- 계정 정보 : CPU 사용 시간, 제한 시간, 계정 번호 등
- 입출력 상태 정보 : 프로세스에 할당된 입출력 장치, 개방된 파일 목록 등

</details>

---
## Context-Switching
- **CPU 코어를 다른 프로세스로 전환하기 위해 현재 프로세스의 상태 저장 및 다른 프로세스의 상태 복원을 수행하는 작업**
    - Context = CPU가 프로세스를 실행하기 위한 정보, PCB에 저장되는 정보들이 해당됨
    - Context-Switching이 발생하면 커널이 이전 프로세스의 context를 그 프로세스의 PCB에 저장하고 새롭게 실행할 (스케줄링으로 예약) 프로세스의 저장된 context를 불러옴
    - **수행 중**에는 CPU의 자원이 어떤 프로세스에 할당된 상태가 아니므로 **CPU가 아무 작업도 할 수 없음** &rarr; **Context-Swtiching time(프로세스가 실행되기 전까지의 기다리는 시간) = pure overhead**
 
#### Context Switching 과정

![context_switching](./img/context_switching.png)

<details>
<summary>과정</summary>

1. Process P1이 실행되는 도중 인터럽트나 시스템 콜이 발생합니다.

2. PCB1에 P1의 정보를 저장하고 PCB2의 상태를 불러옵니다.

3. Process P2를 실행합니다.

4. P2가 실행되는 도중 인터럽트나 시스템 콜이 발생합니다.

5. PCB2에 P2의 정보를 저장하고 PCB1의 상태를 불러옵니다.

6. Process P1을 실행합니다.

</details>

---

