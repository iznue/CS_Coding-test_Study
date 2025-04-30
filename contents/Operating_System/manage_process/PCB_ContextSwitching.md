# Process Control Block (PCB)
- 특정 프로세스에 대한 정보를 담고 있는 운영체제의 자료구조
- 프로세스는 운영체제의 스케줄링 알고리즘에 따라 CPU를 할당받음
- 작업 진행 중 프로세스 전환이 발생하면 하던 일을 저장하고 CPU를 반환해야 함

    &rarr; 나중에 스케줄링에 의해 재실행 되었을 때 이전에 어디까지 작업이 진행되었는지 정보를 알아야 함

    ⇒ ***이 정보가 담긴 공간이 PCB***

- 프로세스 생성과 동시에 그 프로세스의 고유한 PCB도 함께 생성됨, 프로세스 완료 시 PCB는 제거됨

### PCB에 저장되는 정보

![pcb](/contents/Operating_System/img/pcb.png)

#### 프로세스 제어 블록
- 프로세스 식별자 (Process ID, PID)
- 프로세스 상태 (Process state) : new, ready, running, waiting, terminated
- 프로그램 카운터 (Program counter) : 프로세스가 다음에 실행할 명령어의 주소를 가리킴
- CPU 레지스터 : Accumulator, Index Register, 범용 레지스터 등
- CPU 스케줄링 정보 : 프로세스 우선순위, 최종 실행 시각, CPU 점유 시간 등
- 메모리 관리 정보 : Page table, Segment table 등
- 계정 정보 : CPU 사용 시간, 제한 시간, 계정 번호 등
- 입출력 상태 정보 : 프로세스에 할당된 입출력 장치, 개방된 파일 목록 등

---
# Context-Switching

- **CPU 코어를 다른 프로세스로 전환하기 위해 현재 프로세스의 상태 저장 및 다른 프로세스의 상태 복원을 수행하는 작업**
    - Context = CPU가 프로세스를 실행하기 위한 정보, PCB에 저장되는 정보들이 해당됨
    - Context-Switching이 발생하면 커널이 이전 프로세스의 context를 그 프로세스의 PCB에 저장하고 새롭게 실행할 (스케줄링으로 예약) 프로세스의 저장된 context를 불러옴
    - **수행 중**에는 CPU의 자원이 어떤 프로세스에 할당된 상태가 아니므로 **CPU가 아무 작업도 할 수 없음**

    &rarr; **Context-Swtiching time(프로세스가 실행되기 전까지의 기다리는 시간) = pure overhead**
 
### Context Switching 과정

![context_switching](/contents/Operating_System/img/context_switching.png)

1. Process P1이 실행되는 도중 인터럽트나 시스템 콜이 발생

2. PCB1에 P1의 정보를 저장하고 PCB2의 상태를 불러옴

3. Process P2를 실행

4. P2가 실행되는 도중 인터럽트나 시스템 콜이 발생

5. PCB2에 P2의 정보를 저장하고 PCB1의 상태를 불러옴

6. Process P1을 실행
