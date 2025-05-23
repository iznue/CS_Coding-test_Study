## 문제 설명

> 1부터 n까지 번호가 붙어있는 n명의 사람이 영어 끝말잇기를 하고 있습니다. 영어 끝말잇기는 다음과 같은 규칙으로 진행됩니다.

    1번부터 번호 순서대로 한 사람씩 차례대로 단어를 말합니다.
    마지막 사람이 단어를 말한 다음에는 다시 1번부터 시작합니다.
    앞사람이 말한 단어의 마지막 문자로 시작하는 단어를 말해야 합니다.
    이전에 등장했던 단어는 사용할 수 없습니다.
    한 글자인 단어는 인정되지 않습니다.

다음은 3명이 끝말잇기를 하는 상황을 나타냅니다.

tank → kick → know → wheel → land → dream → mother → robot → tank

위 끝말잇기는 다음과 같이 진행됩니다.

    1번 사람이 자신의 첫 번째 차례에 tank를 말합니다.
    2번 사람이 자신의 첫 번째 차례에 kick을 말합니다.
    3번 사람이 자신의 첫 번째 차례에 know를 말합니다.
    1번 사람이 자신의 두 번째 차례에 wheel을 말합니다.
    (계속 진행)

끝말잇기를 계속 진행해 나가다 보면, 3번 사람이 자신의 세 번째 차례에 말한 tank 라는 단어는 이전에 등장했던 단어이므로 탈락하게 됩니다.

사람의 수 n과 사람들이 순서대로 말한 단어 words 가 매개변수로 주어질 때, 가장 먼저 탈락하는 사람의 번호와 그 사람이 자신의 몇 번째 차례에 탈락하는지를 구해서 return 하도록 solution 함수를 완성해주세요.


### 제한 사항
- 끝말잇기에 참여하는 사람의 수 n은 2 이상 10 이하의 자연수입니다.
- words는 끝말잇기에 사용한 단어들이 순서대로 들어있는 배열이며, 길이는 n 이상 100 이하입니다.
- 단어의 길이는 2 이상 50 이하입니다.
- 모든 단어는 알파벳 소문자로만 이루어져 있습니다.
- 끝말잇기에 사용되는 단어의 뜻(의미)은 신경 쓰지 않으셔도 됩니다.
- 정답은 [ 번호, 차례 ] 형태로 return 해주세요.
- 만약 주어진 단어들로 탈락자가 생기지 않는다면, [0, 0]을 return 해주세요.


#### 입출력 예

|n|words|result|
|---|---|---|
|3|["tank", "kick", "know", "wheel", "land", "dream", "mother", "robot", "tank"]|[3,3]|
|5|["hello", "observe", "effect", "take", "either", "recognize", "encourage", "ensure", "establish", "hang", "gather", "refer", "reference", "estimate", "executive"]|[0,0]|
|2|["hello", "one", "even", "never", "now", "world", "draw"]|[1,3]|

---
## 문제 풀이

***Code***
``` python
# divmod 몫 : 차례 (나머지가 0이 아닌 경우 : 차례 + 1)
# divmod 나머지 : 번호 (나머지가 0인 경우 : n)
def return_a(i, n):
    a = list(divmod(i, n))
    if a[1] != 0:
        a[0] += 1
    else:
        a[1] = n
    return [a[1], a[0]]
    
def solution(n, words):
    answer = [0, 0]
    l_relay = []
    for i, w in enumerate(words):
        if w not in l_relay:
            l_relay.append(w)
            # 앞의 마지막 글자와 현재 첫 글자가 같지 않은 경우
            if i != 0 and words[i-1][-1] != w[0]:
                return return_a(i+1, n)
                break
        else:
            # l_relay에 이미 존재하는 단어인 경우
            return return_a(i+1, n)
            break       
    return answer
```
