# Operating System
- user가 사용하는 **application과 hardware 사이**에서 동작하는 소프트웨어 계층
- 응용프로그램이 요청하는 **시스템 리소스를 효율적으로 분배하고, 지원하는 소프트웨어**

[Operating System detail](./Operating_system.md)

<details>
<summary>Table of Contents</summary>

- [Memory](#memory)
- [Process VS Thread](#process-vs-thread)
- [PCB](#process-control-block-pcb)
- [Context Switching](#context-switching)
- [Multi Process VS Multi Thread](#multi-process-vs-multi-thread)
- [Critical Section](#critical-section-임계영역)
- [동기화 메커니즘 : Spinlock & Mutex & Semaphore](#동기화-메커니즘--spinlock--mutex--semaphore)

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
- 동일 프로그램의 여러 인스턴스를 동시에 실행해 여러 프로세스 생성 가능

    &rarr; 각 프로세스는 자체 메모리와 리소스를 가지며 독립적

⇒ **프로그램은 코드, 프로세스는 코드가 실행될 때 발생**

## Process & Thread
- 프로세스는 자체 메모리 공간이 있는 독립적인(애플리케이션에 대한 격리 : **isolation** 제공) entity로 **프로그램의 실행 중인 인스턴스**
- 스레드는 **프로세스 내의 더 가벼운 공유 메모리**로 병렬 실행을 가능하게 함
    - **프로세스의 하위 집합이며 경량 프로세스**라고도 함
    
        &rarr; 프로세스에는 둘 이상의 스레드가 존재할 수 있으며 **스케줄러에 의해 독립적으로 관리됨** = 동시성 : **concurrency**
    
    - ***프로세스의 실행 단위, 같은 프로세스 내에 있는 스레드끼리는 프로세스의 자원을 공유할 수 있음***
    - 스레드는 프로세스 메모리 영역을 공유하므로 어떤 스레드 하나에서 오류가 발생하면 같은 프로세스 내의 다른 스레드 모두가 강제로 종료됨
 
[Process & Thread detail](./Process_Thread.md)

---
## Process Control Block (PCB)
- 특정 프로세스에 대한 정보를 담고 있는 운영체제의 자료구조
- 프로세스는 운영체제의 스케줄링 알고리즘에 따라 CPU를 할당받음
- 작업 진행 중 프로세스 전환이 발생하면 하던 일을 저장하고 CPU를 반환해야 함

    &rarr; 나중에 스케줄링에 의해 재실행 되었을 때 이전에 어디까지 작업이 진행되었는지 정보를 알아야 함

    ⇒ ***이 정보가 담긴 공간이 PCB***

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
    - **수행 중**에는 CPU의 자원이 어떤 프로세스에 할당된 상태가 아니므로 **CPU가 아무 작업도 할 수 없음**

    &rarr; **Context-Swtiching time(프로세스가 실행되기 전까지의 기다리는 시간) = pure overhead**
 
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
## Multi-Process VS Multi-Thread

![multi-process_multi-thread](./img/multi-process_multi-thread.png)

&rarr; **Multi Processing과 Multi Threading은 효율성과 성능을 높이기 위해 컴퓨팅 작업을 병렬화하는 두 가지 접근 방식**

### Single Thread
- 하나의 프로세스에서 하나의 스레드 실행
- 하나의 레지스터와 스택으로 표현
- 요청에 대한 빠른 반응을 요구하는 네트워크 서버의 프로그램일 경우 단일 스레드 모델이 더 적합함

> 장점
> - 자원 접근에 대한 동기화를 신경쓰지 않아도 됨
> - context switching 작업을 요구하지 않음
>
> 단점
> - 한번에 하나의 일만 처리할 수 있으므로 작업에서 블로킹이 발생하면 다음 일을 처리하기까지 기다려야 하는 문제가 발생함

### Multi-Process
- 각각 자체 메모리 공간이 있는 여러 프로세스 사용
- 한 프로세스의 충돌이 다른 프로세스에 직접적인 영향을 미치지 않으므로 이러한 격리를 통해 안정성이 향상될 수 있음
- but **프로세스 간 통신은 스레드에 비해 더 복잡하고 느릴 수 있음**
- **많은 메모리와 CPU 점유시간을 가지며 Context Switching이 느림**

### Multi-Thread
- 단일 프로세스에 여러 스레드가 포함될 수 있음
- 프로세스 내의 모든 스레드는 동일한 메모리 공간을 공유하므로 스레드 간에 정보를 더 쉽고 빠르게 공유할 수 있음
- but **동일 메모리를 공유하므로 경쟁 조건 및 교착 상태**와 같은 문제를 방지하려면 관리가 필요함
- **적은 메모리와 적은 CPU 점유 시간을 가지며 Context Switching 비용이 낮음**

&rarr; ***메모리를 나누어 안정성을 높일 때는 Multi-process를 Context Switching이 많고 빠른 처리 속도를 요구할 경우 Multi-thread를 이용하는게 좋음***

[Multi-Process & Multi-Thread detail](./MultiProcess_MultiThread.md)

---
## Critical Section (임계영역)
- 여러 프로세스가 데이터를 공유하며 수행될 때, 각 프로세스에서 공유 데이터를 접근하는 프로그램 코드 블록

&rarr; ***여러 프로세스가 동일 자원을 동시에 참조하여 값이 오염될 위험 가능성이 있는 영역***

- 공유하는 자원에 동시에 접근하는 경우, 스레드는 데이터와 힙 영역을 공유하기에 어떤 스레드가 다른 스레드에서 사용 중인 변수나 자료구조에 접근해 값을 수정할 수 있음

&rarr; ***따라서 동기화가 필요하며 프로그래밍 시 임계 영역을 최소화하는 설계를 해야함***

⇒ 하나의 메서드에 하나의 스레드만이 진입해서 실행(= mutual exclusion) 하는 메서드 영역 = Critical Section
but 불필요한 부분까지 동기화 하는 경우, 과도한 lock으로 병목 현상을 발생시켜 성능이 저하될 가능성이 높으므로 주의해야함

### Critical Section Problem
- 임계 영역을 만족하기 위해서는 아래 3가지 문제 소지들을 해결해야함
<details>
<summary>problems</summary>

**1. Mutual Exclusion (상호 배제)**
- 한 순간에 오직 하나의 스레드만이 임계 영역에 진입할 수 있음을 보장
- 여러 스레드가 동시에 임계 영역에 접근하지 못하도록 하는 것을 의미

**2. Progress (진행)**
- 어떤 스레드가 임계 영역에 진입하기 위해 대기 중인 상태에서, 다른 스레드가 진입할 수 있음을 보장해야 함

**3. Bounded Waiting (제한된 대기)**
- 한 스레드가 임계 영역에 진입하기 위해 대기하는 시간은 제한되어야 함
- 특정 스레드가 계속해서 다른 스레드에게 우선권을 주며 무제한으로 대기하는 상황이 발생하지 않도록 해야 함

</details>

---
## 동기화 메커니즘 : Spinlock & Mutex & Semaphore
- 동기화 메커니즘은 여러 개의 스레드가 **공유 자원에 동시 접근하는 것을 조절하고 조율하는데 사용되는 기술**
- 주로 운영체제의 **커널(Kernel)**에서 사용됨
- 동기화 메커니즘으로 사용되는 도구로는 **Spinlock, Mutex, Semaphore** 등이 있음

&rarr; ***다중 스레드 환경에서 공유 자원에 대한 접근을 조절하여 Critical section에서의 Race Condition과 같은 문제를 해결하기 위해 사용됨***

### Spinlock
- Critical section이 락이 걸려 진입이 불가능할 때, **임계영역이 unlock되어 진입이 가능해질 때까지 루프를 돌면서 재시도하여 스레드가 CPU를 점유하고 있는 상태**
- 무의미한 코드를 계속 수행하며 언락되길 기다리기 때문에 **Busy Waiting** 상태임

    &rarr; 오랜 시간 동안 언락되지 않으면 해당 시간동안 계속 CPU를 점유하고 있으므로 **오버헤드**가 존재함
  
- 운영체제의 스케줄링 지원을 받지 않기 때문에 해당 스레드에 대한 **Context switching이 일어나지 않음**

    &rarr; 멀티 프로세스 시스템에서만 사용 가능
- 상태가 오직 **Lock / Unlock**만 존재하므로 한번에 하나의 컴포넌트만 접근 가능 & 주체가 동일해야함

### Mutex = Mutual Exclusion
- 상태가 **Lock / Unlock**만 존재한다는 점은 spinlock과 동일
- Spinlock이 임계영역이 언락되어 권한을 획득하기까지 Busy Waiting 상태를 유지한다면, mutex는 **Sleep 상태로 들어갔다 Wakeup 되면 다시 권한 획득을 시도함**
- ***Locking 메커니즘으로 락을 걸은 스레드만이 임계영역을 나갈때 락을 해제할 수 있음***
- 시스템 전반의 성능에 영향을 주지 않고 길게 처리해야하는 작업에 주로 사용 &rarr; ex: 스레드 작업

### Semaphore
- spinlock & mutex와 달리 **표현형이 정수형** &rarr; 하나 이상의 컴포넌트가 공유자원에 접근할 수 있도록 허용
- 컴포넌트가 특정 자원에 접근할 때 **semWait이 먼저 호출되어 임계영역에 들어갈 수 있는지 먼저 확인**
- 임계영역에 접근이 가능하면 **semWait을 빠져나와 임계영역에 들어가고, 이후 semSignal이 호출되어 임계영역에서 빠져나옴**
- ***Signaling 메커니즘으로 락을 걸지 않은 스레드도 signal을 통해 락을 해제할 수 있음***

<details>
<summary>semWait & semSignal</summary>

- **semWait 연산**
    - 세마포어의 값을 감소
    - 만약 값이 음수가 되면 semWait을 호출한 스레드는 블록되지만 음수가 아니면 작업 수행
- **semSignal 연산**
    - 세마포어의 값을 증가
    - 만약 값이 양수가 아니면 semWait 연산에 의해 블록된 스레드를 다시 wake 시킴

</details>

<details>
<summary>사용할 수 있는 자원의 수(= 세마포어 값)에 따른 두가지 유형</summary>

- **Counting Semaphore (개수 세마포어)**
    - 도메인이 0이상인 임의의 정수값인 세마포어
    - 여러개의 자원을 가질 수 있으며 제한된 자원을 가지고 액세스 작업할 때 사용
- **Binary Semaphore (이진 세마포어)**
    - 0 또는 1값만 가질 수 있는 세마포어
    - 임계영역 문제를 해결하는데에 사용하며. 자원이 하나이므로 뮤텍스로도 사용 가능

</details>

[Spinlock & Mutex & Semaphore detail](./Spinlock_Mutex_Semaphore.md)

---
## Process Scheduling
- 프로세스 스케줄러는 **멀티 프로그래밍**과 **time sharing**의 목적을 달성하기 위해 실행 가능한 여러 프로세스 중 하나의 프로세스를 선택해 실행
- 각 CPU 코어는 한번에 한 프로세스 실행 &rarr; 단일 CPU 코어 시스템에 반해 멀티 코어 시스템은 한번에 여러 프로세스 실행 가능

- 멀티 프로그래밍
    - CPU 사용률을 최대화하기 위해 항상 프로세스를 실행하도록 함
    - 특정 프로세스가 CPU를 사용하다가 필요로 하지 않는 순간이 오면 다른 프로세스가 사용할 수 있도록 함
 
- 시분할 (Time sharing)
    - 각 프로그램이 실행되는 동안 사용자들이 상호작용 하도록 프로세스 간 CPU 코어를 자주 전홚함
    - CPU가 하나의 프로그램을 수행하는 시간을 매우 짧은 시간(ms)으로 제한해 번갈아 수행하도록 하면 CPU가 하나인 환경에서도 여러 사용자가 동시에 사용하는 듯한 효과를 줌

### 프로세스 상태 
![process_state](./img/process_state.png)


    New : 프로세스가 생성됨
    Running : 프로세스의 Instruction이 실행됨
    Waiting : (I/O 작업 완료나 신호 수신과 같은) 이벤트가 발생하기를 기다림
    Ready : 프로세서에 할당되기를 기다림
    Terminated : 프로세스가 실행을 끝냄

