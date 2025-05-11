# Process Scheduling
- 프로세스 스케줄러는 **멀티 프로그래밍**과 **time sharing**의 목적을 달성하기 위해 실행 가능한 여러 프로세스 중 하나의 프로세스를 선택해 실행
- 각 CPU 코어는 한번에 한 프로세스 실행 &rarr; 단일 CPU 코어 시스템에 반해 멀티 코어 시스템은 한번에 여러 프로세스 실행 가능

- 멀티 프로그래밍
    - CPU 사용률을 최대화하기 위해 항상 프로세스를 실행하도록 함
    - 특정 프로세스가 CPU를 사용하다가 필요로 하지 않는 순간이 오면 다른 프로세스가 사용할 수 있도록 함
 
- 시분할 (Time sharing)
    - 각 프로그램이 실행되는 동안 사용자들이 상호작용 하도록 프로세스 간 CPU 코어를 자주 전홚함
    - CPU가 하나의 프로그램을 수행하는 시간을 매우 짧은 시간(ms)으로 제한해 번갈아 수행하도록 하면 CPU가 하나인 환경에서도 여러 사용자가 동시에 사용하는 듯한 효과를 줌

## 프로세스의 생명 주기
![process_state](/contents/Operating_System/img/process_state.png)

- 프로세스 실행은 **CPU 실행(execution)과** **입/출력 대기(I/O wait)의** 사이클로 구성됨

&rarr; ***이를 CPU I/O Burst Cycle***이라 함

> New : 프로세스가 생성됨, 메모리에 올라간 상태
> 
> Ready : 프로세서에 할당되기를 기다림 (다른 프로세스가 CPU를 사용하고 있는 상황)
> 
> Running : 프로세스의 Instruction이 실행됨, 프로세스가 CPU를 점령하여 명령어가 실행되고 있는 상태
> 
> Waiting : (I/O requests나 신호 수신과 같은) 이벤트가 완료되기를 기다림, 해당 작업이 완료되면 Ready Queue로 이동
> 
> Terminated : 프로세스 명령어가 끝까지 진행되었거나 중간에 exit()이 발생하면 프로세스가 종료됨

---
# CPU Scheduling
- ***운영체제가 프로세스들에게 공정하고 합리적으로 CPU 자원을 배분하는 것***
- CPU 스케줄링 알고리즘에 따라 프로세스에서 해야 하는 일을 스레드 단위로 CPU에 할당

&rarr; CPU 이용률을 높게, 주어진 시간에 많은 일을 수행 / **ready queue에 있는 프로세스는 적게, 응답 시간을 짧게 설정하는 것이 목표**

#### CPU 스케줄링이 왜 필요할까?
- 프로세스가 CPU를 점유해 작업을 수행하는 도중 I/O or Interrupt가 발생하면 일시적으로 프로세스는 CPU를 사용하지 않는데도 점유하고 있음

&rarr; 이러한 상황을 줄여서 CPU를 최대한 활용하면 프로세스들이 효율적으로 CPU를 사용할 수 있지 않을까?에서 시작됨

### Process Priority
- 프로세스의 중요도에 따라 운영체제가 우선순위를 부여함
- 우선순위가 높은 프로세스는 대표적으로 입출력이 많은 프로세스

&rarr; 입출력 작업 완료 전끼지 입출력 집중 프로세스는 대기 상태이므로 다른 프로세스가 CPU를 사용할 수 있기 때문

## Schedulng Queue
- 각 프로세스의 PCB에 부여된 우선순위에 따라 CPU를 사용할 수 있도록 줄을 세우는 것
- Ready queue (CPU를 사용하고 싶은 프로세스들) / Waiting queue (입출력장치 이용을 위해 대기 상태에 접어든 프로세스들)

![scheduling_queue](/contents/Operating_System/img/scheduling_queue.jpeg)

&rarr; 프로세스는 종료될 때까지 위의 주기를 반복, 종료되면 모든 큐에서 제거되고 PCB 및 자원 할당이 해제됨

### CPU Scheduling 발생 상황
> 1. 프로세스가 running → waiting 상태로 전환 (ex. I/O 요청 또는 하위 프로세스 종료를 위한 wait() 호출)
> 
> 2. 프로세스가 running → ready 상태로 전환 (ex. interrupt 발생)
> 
> 3. 프로세스가 waiting → ready 상태로 전환 (ex. I/O 완료)
> 
> 4. 프로세스 종료

&rarr; 상황 1,4에서는 새 프로세스를 선택해야 함 but **상황 2,3에서는 Preemptive or Nonpreemptive 중에서 선택 가능**

***Preemptive = 선점형 : 강제로 CPU 회수***

&rarr; 비선점에 비해 context switching이 자주 발생해 오버헤드가 발생할 수 있지만 CPU 독점 현상 방지 가능

***Nonpreemptive = 비선점형 : 강제로 빼앗지 않고 자진해서 CPU 반납***

&rarr; 모든 프로세스가 골고루 자원을 사용할 수 없음 (자원 독점 가능)

## Preemptive / Nonpreemptive에 속하는 CPU Scheduling Algorithm 기법의 종류
- Preemptive
    - SRT (Shortest Remaining Time) : SJF + RR / 짧은 시간 순서대로 수행 
    - RR (Round-Robin) : 정해진 타임 슬라이스(CPU를 사용할 수 있는 정해진 시간)만큼동안 CPU 할당
    - Multi-level queue : ready queue를 여러 개 사용 / queue마다 RR or FCFS 등 다른 스케줄링 알고리즘 적용
    - Multi-level feedback queue : multi-level queue와 비슷하나 프로세스들이 큐를 이동할 수 있음 
        - 정해진 타임 슬라이스 동안 해당 큐에서 실행이 끝나지 않으면 다음 큐로 삽입되어 CPU를 오래 사용해야 하는 프로세스는 점차 우선순위가 낮아짐
- Nonpreemptive
    - FCFS (First Come First Served) : ready queue에 삽입된 순서대로 CPU 할당
    - SJF (Shortest Job First) : 예상 CPU 사용 시간이 짧은 프로세스 먼저 실행
    - Priority : 가장 높은 우선순위를 가진 프로세스부터 실행
        - 우선순위가 낮은 프로세스는 실행이 계속 연기돼 Starvation(기아) 상태에 빠질 수 있으며, Aging을 통해 시간 흐름에 따라 우선순위를 증가시켜 기아 현상을 방지함
    - HRN (Highest Response ration Next) : 수행시간의 길이와 대기 시간을 모두 고려해 우선순위 결정
    - Deadline : 작업을 명시된 시간이나 기한 내에 완료하도록 스케줄링

---
# CPU가 여러개인 경우의 Scheduling
**1. Multiple-Processor Scheduling**
- Homogeneous processor인 경우
    - queue에 한줄로 세워 각 프로세서가 알아서 꺼내가도록 but 특정 프로세서에서 수행돼야 하는 프로세스가 있는 경우 문제가 복잡해짐
- Load sharing
    - 별개의 큐 or 공동 큐를 사용해 일부 프로세서에 일이 몰리지 않도록 부하 조정
- Symmetric Multiprocessing (SMP) : 각 프로세서가 알아서 스케줄링 결정
- Asymmetric Multiprocessing : 하나의 프로세서가 시스템 데이터의 접근과 공유를 책임지고 나머지는 그에 따름

 **2. Real-Time Scheduling**
 - Hard real-time system : 정해진 시간 안에 반드시 끝내도록 (데드라인을 반드시 지킴)
 - Soft real-time computing : soft real-time task는 일반 프로세스에 비해 높은 우선순위를 부여 (데드라인을 반드시 지키지는 않음)

**3. Thread Scheduling**
- Local Scheduling
    - user 프로세스가 직접 어떤 thread에 CPU를 줄지 결정
- Global Scheduling
    - kernel level thread의 경우 커널의 단기 스케줄러가 결정
    - OS가 알고리즘에 의거해 어떤 thread에 CPU에 줄지 결정
