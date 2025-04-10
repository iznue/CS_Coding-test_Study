# 0/1 Knapsack

---
### 문제 상황
- 크기가 w인 가방과 n개의 물건을 가지고 있으며, 각 물건은 하나씩 존재함
- 각 물건 i는 크기 wi와 가치 vi를 가짐
- 이 가방에 물건을 담으려 할 때, 가방에 담을 수 있는 물건들의 가치의 합이 최대가 되도록 하려면 어떤 물건들을 선택해야하는가?
    - (단, 가방에 담지 못하는 물건이 있을 수 있음)
 
### 해결 방법
- dp[n][W] (n: 물건의 개수, W: 가방의 크기) 를 선언
- dp[i][j]는 1 ~ i까지의 물건을 고려했을 때 크기가 j인 가방에 넣을 수 있는 최대 가치의 합을 저장 

1. 물건들을 크기에 따라 정렬
2. dp[i][j] 는 물건 1부터 i까지 고려했을 때, 크기가 j인 가방에 넣을 수 있는 물건들의 최대가치 합으로 정의
3. 각 물건의 선택여부에 따라 작은 부분으로 나눔
    - 3-1) 물건 i를 선택하지 않는 경우, dp[i][j] = dp[i-1][j]와 같음 (크기의 변화가 없으므로)
    - 3-2) 물건 i를 선택한 경우 dp[i][j] = dp[i-1][j-Wi] + vi와 같음
    - 이것은 물건 i를 제외한 이전 물건들 중 크기가 j-wi인 가방에 넣을 수 있는 최대 가치 합에 물건 i의 가치 vi를 더한 값과 같음
4. 최종적으로 dp[n][W]가 가방에 넣을 수 있는 물건들의 최대가치 합이 된다.

### Brute-force or Greedy로 풀 수 없는 이유
- **Brute-force의 경우**
    - n개의 물건이 있다면 각 물건마다 선택하거나 선택하지 않는 두 가지 경우가 있으므로 총 2<sup>2</sup>의 조합이 발생함
    - 물건의 수가 증가할 수록 경우의 수가 기하급수적으로 증가하므로 시간 복잡도가 0(2<sup>2</sup>)이 됨

    &rarr; 물건의 개수가 많아지면 현실적으로 해결 불가능

- **Greedy의 경우**
    - 1. 가치가 가장 높은 물건부터 선택
      2. 무게가 가장 가벼운 물건부터 선택
      3. 무게당 가치가 가장 높은 물건부터 선택

    &rarr; 최적해를 보장하지 않음

&rarr; ***DP 방식은 문제를 작은 하위로 나누고, 각 하위 문제의 결과를 저장해 재사용함으로써 중복 계산을 피하므로 해당 문제에 적합***

### 구현

```python
def knapsack(W, wt, val, n):  # W: 배낭의 무게한도, wt: 각 보석의 무게, val: 각 보석의 가격, n: 보석의 수
    K = [[0 for x in range(W+1)] for x in range(n+1)]  # DP를 위한 2차원 리스트 초기화
    for i in range(n+1):
        for w in range(W+1):  # 각 칸을 돌면서
            if i==0 or w==0:  # 0번째 행/열은 0으로 세팅
                K[i][w] = 0
            elif wt[i-1] <= w:
                K[i][w] = max(val[i-1]+K[i-1][w-wt[i-1]], K[i-1][w])  # max 함수 사용하여 큰 것 선택
            else:
                K[i][w] = K[i-1][w]
    return K[n][W]
```
