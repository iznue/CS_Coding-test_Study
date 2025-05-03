# Race Condition = 경쟁 상태
- **공유 자원을 둘 이상의 스레드 혹은 프로세스가 읽거나 쓰면서 실행 순서에 따라 결과값이 의도와 달라질 수 있는 문제**
- 해당 문제를 방지하기 위해 **공유 메모리를 쓰는 프로세스 끼리 `동기화` 해야 함**

![race_condition](/contents/Operating_System/img/race_condition.png)

---
## Race Condision이 발생하는 경우
- **커널 코드 실행 중 인터럽트가 발생한 경우**
    - 커널 모드에서 데이터를 로드해 작업하는 도중 인터럽트가 발생해 같은 데이터를 조작하는 경우
    - 커널이 가진 전역변수는 모든 프로세스의 공유물이므로 경쟁 상태 가능성 존재
- **프로세스가 시스템 콜을 해 커널모드로 진입해서 작업하는 도중에 context switching이 일어난 경우**
    - 프로세스1이 커널 모드에서 데이터를 조작하던 도중 시간이 초과되어 CPU 제어권이 프로세스2로 넘어가 같은 데이터를 조작함
- **멀티 프로세서 환경에서 2개의 cpu가 동시에 커널 내부의 공유 데이터에 접근해 조작하는 경우 or 멀티 스레드 환경에서 공통 자원을 병행해 작업하는 경우**
    - 멀티 프로세스 환경에서 2개의 CPU가 동시에 커널 내부의 공유 데이터에 접근해 조작하는 경우

---
## Race Condition 문제 상황
1. **상호 배제 (Mutual Exclusion)**
    - 여러 프로세스가 공용 데이터에 동시 접근하는 것을 막아야 함
    - 한 프로세스가 공용 데이터를 사용하고 있으면 해당 자원을 사용하지 못하게 막음
2. **교착 상태 (Dead Lock)**
    - 상호 배제 시행 시 프로세스가 각자 프로그램을 실행하기 위해 두 자원 모두 액세스 해야한다고 할 때, 프로세스는 두 자원을 모두 필요로 하므로 프로그램 수행 완료까지 이미 소유한 리소스를 해제하지 않음
3. **기아 상태 (Starvation)**
    - 프로세스들이 더 이상 진행하지 못하고 영구적으로 블락된 상태
    - 시스템 자원에 대한 경쟁 도중 또는 프로세스 간 통신 과정에서 발생할 수 있음
    - 여러 작업이 서로 상대방의 작업이 끝나기만을 기다리므로 결과적으로 아무것도 완료하지 못함

---
## Race Condision의 문제점
1. 예측 불가능한 결과
    - 여러 스레드나 프로세스마다 실행 속도가 달라 잘못된 값을 읽거나 수정 가능
    - a 스레드가 수정한 결과를 b가 수정하면서 a가 수정한 결과는 없어짐
2. 일관성 손실
    - 여러 스레드나 프로세스가 데이터 수정 시 예기치 않은 상태로 데이터 변경 가능
3. 디버깅 어려움
    - 여러 스레드나 프로세스의 각각 다른 실행 속도로 인해 흐름을 읽기 어려움
4. 잠금 대기 시간
    - Race condition 방지를 위해 무분별한 `Lock`을 사용할 시, 대기 시간으로 성능 저하 발생

---
## Race Condition 예방
- **상호 배제 (Mutual Exclusion)**
    - 공유 데이터에 접근하는 부분을 `Critical Section`으로 지정, 한번에 하나의 실행 흐름만 해당 영역에 들어가게 함
- **공유 데이터를 최소화한 병렬 처리 설계**
    - 데이터를 적절히 분리해 각 스레드가 독립적으로 처리하게 함
- **스레드 안전성 보장 (Thread Safe)**
    - 공유 데이터 수정 함수나 메서드를 스레드 안전하도록 구현
    - 스레드 동기화 기법을 사용하거나 불변 객체 (Immutable object) 패턴 적용

⇒ **결국 스레드의 순차적 실행을 보장하면 됨 !**

> 대표적인 예 : 탈의실
>
> 동기화에서 탈의실을 `critical section` / 오직 한 명만 들어갈 수 있는 것을 `mutually exclusive`
> 
> We must synchronize the execution of the threads. Need to guarantee **mutually exclusive access to critical sections.**

---
## 예시

```c++
int counter = 0; // 전역 변수
item nextProduced;
item nextConsumed;

// PRODUCER Thread
while (TRUE){
  while(counter == BUFFER_SIZE);
  buffer[in] = newxtProduced;
  in = (in + 1) % BUFFER_SIZE;
  counter++;
}

// CONSUMER Thread
while (TRUE){
  while(counter == 0);
  nextConsumed = buffer[out];
  out = (out + 1) % BUFFER_SIZE;
  counter--;
}

```

- Producer는 공유 메모리에 데이터를 쓰는 스레드, Consumer는 공유 메모리에서 데이터를 가져가는 스레드
- 두 스레드가 각각 counter++, counter--를 실행했다고 가정할 때 결과 값이 항상 같다고 보장할 수 있을까?

&rarr; 불가능. 이는 3가지 assembly code로 이루어져 있으므로

> // counter++
> 
> register1 = counter // load from memory
> 
> register1 = register + 1
> 
> counter = register1 // store in memory
>
> // counter--
> 
> register2 = counter // load from memory
> 
> register2 = register - 1
> 
> counter = register2 // store in memory



> - 순차적으로 실행되는 경우 : counter 최종 값 = 3
> 
> T0 : producer execute register1 = counter             {register1 = 3 : 가정}
>
> T1 : producer execute register1 = register1 + 1       {register1 = 4}
> 
> T2 : producer execute counter = register1             {counter = 4}
> 
> T3 : consumer execute register2 = counter             {register2 = 4}
> 
> T4 : consumer execute register2 = register2 - 1       {register2 = 3}
> 
> T5 : consumer execute counter = register2             {counter = 3}



> - T1 수행 중 Context Switching이 일어나 T3가 실행되는 경우 : counter 최종 값 = 2
>   
> T0 : producer execute register1 = counter             {register1 = 3 : 가정}
>
> T1 : producer execute register1 = register1 + 1       {register1 = 4}
> 
> context switch P1 &rarr; P2
> 
> T2 : consumer execute register2 = counter             {register2 = 3}
> 
> T3 : consumer execute register2 = register2 - 1       {register2 = 2}
> 
> context switch P2 &rarr; P1
> 
> T4 : producer execute counter = register1             {counter = 4}
> 
> context switch P1 &rarr; P2
> 
> T5 : consumer execute counter = register2             {counter = 2}
