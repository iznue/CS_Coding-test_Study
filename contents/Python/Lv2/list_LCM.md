## 문제 설명

> 두 수의 최소공배수(Least Common Multiple)란 입력된 두 수의 배수 중 공통이 되는 가장 작은 숫자를 의미합니다.
> 예를 들어 2와 7의 최소공배수는 14가 됩니다.
>
> 정의를 확장해서, n개의 수의 최소공배수는 n 개의 수들의 배수 중 공통이 되는 가장 작은 숫자가 됩니다.
>
> n개의 숫자를 담은 배열 arr이 입력되었을 때 이 수들의 최소공배수를 반환하는 함수, solution을 완성해 주세요.

### 제한 사항
- arr은 길이 1이상, 15이하인 배열입니다.
- arr의 원소는 100 이하인 자연수입니다.

#### 입출력 예

|arr|result|
|---|---|
|[2,6,8,14]|168|
|[1,2,3]|6|

---
## 문제 풀이
- 최소공배수 = 두 자연수 곱 / 최대공약수

***Code***
``` python
import math

def lcm(a, b):
    return a * b // math.gcd(a, b)

def solution(arr):
    n = arr[0]
    for i in arr[1:]:
        n = lcm(n, i)
        # print(n)
    return n
```

***Err Code***
``` python
def solution(arr):
    min_a = 1
    for a in arr:
        # print(arr)
        for b in range(len(arr)):
            # print(a, arr[b])
            if arr[b] % a == 0:
                arr[b] = int(arr[b] / a)
        min_a *= a
    
    return min_a
```
- 처음에는 gcd를 사용하지 않고 구현해보려 했음
1. arr 배열의 첫 원소부터 요소들을 나눔 &rarr; 나누어 떨어지는 경우 몫을 해당 요소에 대체 & 최소공배수에 곱함
2. 마지막 요소까지 반복한 후 최종적으로 남은 arr의 요소들을 곱해줌