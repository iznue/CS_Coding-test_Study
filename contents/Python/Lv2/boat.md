## 문제 설명

> 무인도에 갇힌 사람들을 구명보트를 이용하여 구출하려고 합니다. 구명보트는 작아서 한 번에 최대 2명씩 밖에 탈 수 없고, 무게 제한도 있습니다.
>
> 예를 들어, 사람들의 몸무게가 [70kg, 50kg, 80kg, 50kg]이고 구명보트의 무게 제한이 100kg이라면 2번째 사람과 4번째 사람은 같이 탈 수 있지만 1번째 사람과 3번째 사람의 무게의 합은 150kg이므로 구명보트의 무게 제한을 초과하여 같이 탈 수 없습니다.
>
> 구명보트를 최대한 적게 사용하여 모든 사람을 구출하려고 합니다.
>
> 사람들의 몸무게를 담은 배열 people과 구명보트의 무게 제한 limit가 매개변수로 주어질 때, 모든 사람을 구출하기 위해 필요한 구명보트 개수의 최솟값을 return 하도록 solution 함수를 작성해주세요.


### 제한 사항
- 무인도에 갇힌 사람은 1명 이상 50,000명 이하입니다.
- 각 사람의 몸무게는 40kg 이상 240kg 이하입니다.
- 구명보트의 무게 제한은 40kg 이상 240kg 이하입니다.
- 구명보트의 무게 제한은 항상 사람들의 몸무게 중 최댓값보다 크게 주어지므로 사람들을 구출할 수 없는 경우는 없습니다.


#### 입출력 예

|people|limit|return|
|---|---|---|
|[70, 50, 80, 50]|100|3|
|[70, 80, 50]|100|3|

---
## 문제 풀이
- greedy 알고리즘으로 현재 상황에서 당장 좋은 것만 고르기

1. 가장 몸무게가 많이 나가는 순으로 정렬
2. 가장 작은 몸무게 + 가장 큰 몸무게 <= limit인 경우 보트에 태우고 people에서 제외 (보트에 최대 2명만 탈 수 있으므로)
3. limit을 안 넘는 경우 가장 몸무게가 큰 사람만 보트에 태우고 people에서 제외
4. people에 2명만 남을때까지 2-3 과정 반복
5. 최종적으로 몸무게 합이 limit을 넘는 경우 각각 보트에 태우고, 그렇지 않으면 함께 보트에 태움

***Code***
``` python
from collections import deque

def solution(people, limit):
    answer = 0
    people = deque(sorted(people, reverse=True))
    kg = people[-1]
    while len(people) > 2:
        if people[0] + kg <= limit:
            answer += 1
            people.popleft()
            people.pop()
            kg = people[-1]
        else:
            answer += 1
            people.popleft()
    return answer+1 if sum(people) <= limit else answer + 2
```
- 가장 앞, 뒤 요소를 계속 사용해야하기에 deque로 구현함


***Err Code***
``` python
from collections import deque

def solution(people, limit):
    answer = 0
    
    people = deque(sorted(people, reverse=True))
    
    boat = []
    hap = people[-1]
    kg = 0
    while len(people) > 1:
        for p in list(people)[:-1]:
            if p + hap < limit:
                hap += p
            elif p + hap == limit:
                answer += 1
                people.pop()
                hap = list(people)[-1]
                people.popleft()
                break
            else:
                boat.append(p)
                hap = list(people)[-1]
                people.popleft()
                break
    return answer + len(boat) + len(people)
```
- 처음에는 최대 2명까지라는 문제 조건을 고려하지 않고 풀어서 몇가지 테스트 케이스에서 실행 오류 + 런타임 에러가 발생함