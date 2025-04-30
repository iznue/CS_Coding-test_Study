## 문제 설명

> Leo는 카펫을 사러 갔다가 아래 그림과 같이 중앙에는 노란색으로 칠해져 있고 테두리 1줄은 갈색으로 칠해져 있는 격자 모양 카펫을 봤습니다.
>
> Leo는 집으로 돌아와서 아까 본 카펫의 노란색과 갈색으로 색칠된 격자의 개수는 기억했지만, 전체 카펫의 크기는 기억하지 못했습니다.
> 
> Leo가 본 카펫에서 갈색 격자의 수 brown, 노란색 격자의 수 yellow가 매개변수로 주어질 때 카펫의 가로, 세로 크기를 순서대로 배열에 담아 return 하도록 solution 함수를 작성해주세요.

### 제한 사항
- 갈색 격자의 수 brown은 8 이상 5,000 이하인 자연수입니다.
- 노란색 격자의 수 yellow는 1 이상 2,000,000 이하인 자연수입니다.
- 카펫의 가로 길이는 세로 길이와 같거나, 세로 길이보다 깁니다.

#### 입출력 예

|brown|yellow|return|
|---|---|---|
|10|2|[4, 3]|
|8|1|[3, 3]|
|24|24|[8, 6]|

---
## 문제 풀이
1. brown + yellow의 약수 구하기
2. (width-2) * (height-2) = yellow
     - 테두리 1줄이 갈색으로 둘러져있으므로
     - 가장 작은 width는 yellow가 1인 경우이므로 3부터 반복문 범위를 시작함
3. return 시 가로 > 세로


***Code***
``` python
def solution(brown, yellow):
    answer = []
    carpet = brown + yellow
    
    for width in range(3, carpet+1):
        if ((width-2) * ((carpet // width) - 2) == yellow):
            answer.append(carpet // width)
            answer.append(width)
            break
    
    return answer
```


***Err Code***
``` python
from math import sqrt

def solution(brown, yellow):
    carpet = brown + yellow
    
    yaksu = []
    for c in range(1, int(sqrt(carpet))+1): # int(carpet**(1,2))+1
        if carpet % c == 0:
            yaksu.append(c)
            if c**2 != carpet:
                yaksu.append(carpet // c)
        
    yaksu.sort()
    garo_idx = len(yaksu)//2
    
    if len(yaksu) % 2 == 0:
        return yaksu[garo_idx], yaksu[garo_idx-1]
    else:
        return yaksu[garo_idx], yaksu[garo_idx]
```
- 처음에는 이 방식으로 풀이 했었는데 6,7 테스트 케이스에서 실패가 떴음
- 테두리 계산 시 어떻게 배치되는지 고려하지 않아서 생긴 문제인듯