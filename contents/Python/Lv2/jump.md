## 문제 설명

> 효진이는 멀리 뛰기를 연습하고 있습니다. 효진이는 한번에 1칸, 또는 2칸을 뛸 수 있습니다.
> 
> 칸이 총 4개 있을 때, 효진이는 (1칸, 1칸, 1칸, 1칸) (1칸, 2칸, 1칸) (1칸, 1칸, 2칸) (2칸, 1칸, 1칸) (2칸, 2칸)의 5가지 방법으로 맨 끝 칸에 도달할 수 있습니다.
>
> 멀리뛰기에 사용될 칸의 수 n이 주어질 때, 효진이가 끝에 도달하는 방법이 몇 가지인지 알아내, 여기에 1234567를 나눈 나머지를 리턴하는 함수, solution을 완성하세요.
>
> 예를 들어 4가 입력된다면, 5를 return하면 됩니다.

### 제한 사항
- n은 1 이상, 2000 이하인 정수입니다.

#### 입출력 예

|n|result|
|---|---|
|4|5|
|3|3|

---
## 문제 풀이
- DP 동적계획법 적용 &rarr; 이전 칸에 도달하는 방법에 의존되어 특정 칸에 도달함
- n번째 칸에 도달하려면 n-1번째 칸에서 1칸을 더 뛰거나, n-2번째 칸에서 2칸을 더 뛰어야 함
- dp[i]에 i번째 칸에 도달하는 방법의 수 기록

&rarr; 점화식 : dp[n] = dp[n-1] + dp[n-2]

***Code***
``` python
def solution(n):
    dp = [0] * (n+1)
    
    dp[0] = 1
    dp[1] = 1 # 1번째 칸 : 1칸 뛰기
    
    for i in range(2, n+1):
        dp[i] = (dp[i-1] + dp[i-2])
        # print(dp[i], dp[i-1], dp[i-2])
        
    return dp[n] % 1234567
```

***Err Code***
``` python
from itertools import permutations

def solution(n):
    jump = divmod(n, 2)
    kan = [2] * jump[0] + [1] * n
    
    kyungwoo = []
    
    for i in range(1, n+1):
        result = list(permutations(kan, i))
        for r in result:
            if r not in kyungwoo and sum(r) == n:
                kyungwoo.append(r)

    return len(kyungwoo) % 1234567
```
- 처음에는 순열을 이용하려 했음
> 1. n이 1 또는 0이 될 때까지 2만큼 계속 빼기
> 2. kan 리스트에 저장
> 3. kan 리스트에 저장된 2의 수 만큼 1추가하기 (2배)
> 4. 중복 순열로 경우의 수 따지기 &rarr; 기존에 없던 조합이면서 합이 n이 되는 경우만 answer에 추가

- 이중 반복문을 써서 실행 시간초과가 발생함