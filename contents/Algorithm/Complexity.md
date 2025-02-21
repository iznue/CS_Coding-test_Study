# 시간복잡도 & 공간복잡도
--- 
## 시간복잡도 

![시간복잡도1](./img/time_complexity.png)

![시간복잡도2](./img/time_complexity2.png)

> #### 시간복잡도를 구하는 요령
> - 하나의 루프를 사용해 단일 요소 집합을 반복하는 경우 : 0(n)
> - 컬렉션의 절반 이상을 반복하는 경우 : 0(n/2) &rarr; 0(n)
> - 두 개의 다른 루프를 사용해 개별 콜렉션을 반복하는 경우 : 0(n+m) &rarr; 0(n)
> - 두 개의 중첩 루프를 사용해 단일 콜렉션을 반복하는 경우 : 0(n<sup>2</sup>)
> - 두 개의 중첩 루프를 사용해 다른 콜렉션을 반복하는 경우 : 0(n*m) &rarr; 0(n<sup>2</sup>)
> - 컬렉션 정렬을 사용하는 경우 : 0(n*log(n))

&rarr; 최악의 경우에 대한 시간복잡도 계산
> - n의 범위가 500인 경우 시간 복잡도가 0(n<sup>3</sup>) 알고리즘 설계 시 문제 해결 가능
> - n의 범위가 2000인 경우 시간 복잡도가 0(n<sup>2</sup>) 알고리즘 설계 시 문제 해결 가능
> - n의 범위가 100,000인 경우 시간 복잡도가 0(nlog n) 알고리즘 설계 시 문제 해결 가능
> - n의 범위가 10,000,000인 경우 시간 복잡도가 0(n) 알고리즘 설계 시 문제 해결 가능

![data_structure_time_complexity](./img/data_structure_time_complexity.png)

![sort_algorithm_time_complexity](./img/sort_algorithm_time_complexity.png)

### 예제

---
## 공간복잡도

### 예제