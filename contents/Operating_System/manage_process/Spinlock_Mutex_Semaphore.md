# Spinlock & Mutex & Semaphore

---
## Spinlock
![spinlock](/contents/Operating_System/img/spinlock.png)

- Thread0이 스핀락을 얻고 critical section에 진입해 공유 자원에 접근하게 되면 스핀락을 얻지 못한 Thread1은 대기하는 동안 락을 얻을 수 있는지 확인하는 작업을 무한반복함
- 무한반복 중 Thread0이 critical section을 나와 스핀락을 반환하면, Thread1이 스핀락을 얻고 critical section으로 들어감

- 장점
    - 단순하고 구현이 쉬움
    - 락을 기다리는 동안 스레드가 대기하지 않고 계속 실행되므로 일부 상황에서 빠를 수 있음
- 단점
    - **Busy wait 방식으로 인해 계속해서 CPU 자원을 낭비하므로 효율성이 떨어질 수 있음**
    - 운영체제가 제공하는 스케줄링 정책에 영향을 받을 수 있음

#### 간이 코드
```c++
volatile int lock = 0;

int TestAndSet(int* lockPtr){
  int oldLock = *lockPtr;
  *lockPtr = 1;
  return oldLock;
}

void critical(){
  while (test_and_set(&lock)==1);
  ... critical section
  lock = 0;
}
```
&rarr; global 변수인 lock에 여러 스레드 접근 가능

&rarr; 스레드들은 critical() 메서드에서 while 루프를 통해 락을 획득하려 시도하고, 락을 획득한 하나의 스레드만이 critical section에 진입

***testAndSet 메서드는 어떻게 mutual exclusion을 보장하는가?***

&rarr; 해당 메서드는 CPU의 도움을 받아 한번에 하나의 스레드만이 진입 가능

&rarr; 여러 스레드가 해당 메서드에 진입하려해도 결과적으로 락을 취득하는 스레드는 반드시 1개임

⇒ testAndSet 메서드는 CPU atomic(= 단일 기계 명령어, 실행 중간에 간섭 OR 중단 X) 명령어로 동기화가 보장됨

⇒ 다른 스레드가 현재 값을 읽어가기 전에 새로운 값을 먼저 설정하여 Race condition을 방지함

---
## Mutex
![mutex](/contents/Operating_System/img/mutex.png)
![mutex_](/contents/Operating_System/img/mutex_.jpg)

- 하나의 스레드가 락을 얻어 critical section에 진입했다면, 락을 취득하지 못한 다른 스레드는 락을 가질 수 있을 때까지 휴식
- 한번에 하나의 스레드만 임계 영역에 진입할 수 있음
- **Binary Semaphore**의 특수한 형태로 볼 수 있으며, **1인 경우 뮤텍스를 소유하지 않은 상태 / 0인 경우 뮤텍스를 소유한 상태**를 나타냄
- **Key를 기반으로 한 기법이며, key에 해당하는 어떤 object가 있으면 이를 소유한 스레드/프로세스 만이 공유자원에 접근 가능**

#### 간이 코드

```c++
class Mutex{
  int value = 1;
  int guard = 0;
}

Mutex::lock(){
  while (test_and_set(&guard));
  if (value == 0){
    ... 현재 스레드를 큐에 넣음;
    guard = 0; & go to sleep
  } else{
      value = 0;
      buard = 0;
  }
}

Mutex::unlock(){
  while (test_and_set(&guard));
  if (큐에 하나라도 대기중이라면){
    그 중에 하나를 깨움;
  } else{
    value = 1;
  }
  guard = 0;
}

mutex->lock();
...critical section
mutex->unlock();
```
&rarr; 락을 얻지 못하고 대기해야 하는 스레드라면 큐에 넣고 sleep, 락을 반환하는 과정에서 sleep 중인 스레드가 있다면 락을 반화하기 전에 깨우는 과정이 추가됨

&rarr; value를 얻어야만 critical section에서 동작 가능하며 단 하나의 스레드만이 실행되도록 함

&rarr; lock()에서 value 값을 안전하게 변경하기 위해 guard가 보장하는 critical section 내에서 value 값을 변경함

### Mutex VS Spinlock
- Mutex는 **대부분의 상황에서 스핀락보다 효율적으로 동작이 가능하며 대기 시간이 길거나 대기 스레드가 많은 상황에서 더 효율적**
- Spinlock은 **멀티 코어 환경이며. critical section에서의 작업이 context switching 보다 빨리 일어나는 경우 더 효율적**

---
## Semaphore
![semaphore](/contents/Operating_System/img/semaphore.png)
![semaphore_](/contents/Operating_System/img/semaphore_.jpg)

- signal mechanism을 가진 하나 이상의 스레드가 critical section에 접근 가능하도록 함
- spinlock. mutex가 critical section에 진입할 수 있는 스레드 개수는 1로 고정되어 있지만. semaphore는 동시에 진입한 스레드의 개수를 1이상으로도 설정할 수 있음
- **반드시 정해진 순서로 작업이 일어나야 하는 상황에서 사용 가능**

#### 간이 코드
```c++
class Semaphore{
  int value = 1;
  int guard = 0;
}

Semaphore::wait(){
  while (test_and_set(&guard));
  if (value == 0){
    ...현재 스레드를 큐에 넣음
    guard = 0;; & go to sleep
  } else{
    value -= 1;
    guard = 0;
  }
}

Semaphore::signal(){
  while (test_and_set(&guard));
  if (큐에 하나라도 대기중이라면){
    그 중에 하나를 깨워서 준비
  } else{
    value += 1;
  }
  guard = 0;
}

semaphore->wait();
...critical section
semaphore->signal();
```
&rarr; value는 진입할 수 있는 스레드의 수에 따라 달라질 수 있음

### Mutex VS Binary Semaphore
- Mutex는 **락을 가진 스레드에서만 락 해제 가능**
- Semaphore는 **wait()을 실행하는 스레드와 signal()을 실행하는 스레드가 다를 수 있음**

- Mutex는 priority inheritance 속성을 가지지만 Semaphore는 해당 속성을 가지지 않음

&rarr; ***상호 배제만 필요한 경우에는 뮤텍스, 작업 간 실행 순서 동기화가 필요한 경우에는 세마포어가 적합***
