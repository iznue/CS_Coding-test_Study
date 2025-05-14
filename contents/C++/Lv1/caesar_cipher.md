## 문제 설명

> 어떤 문장의 각 알파벳을 일정한 거리만큼 밀어서 다른 알파벳으로 바꾸는 암호화 방식을 시저 암호라고 합니다.
> 
> 예를 들어 "AB"는 1만큼 밀면 "BC"가 되고, 3만큼 밀면 "DE"가 됩니다. "z"는 1만큼 밀면 "a"가 됩니다.
> 
> 문자열 s와 거리 n을 입력받아 s를 n만큼 민 암호문을 만드는 함수, solution을 완성해 보세요.

### 제한 사항
- 공백은 아무리 밀어도 공백입니다.
- s는 알파벳 소문자, 대문자, 공백으로만 이루어져 있습니다.
- s의 길이는 8000이하입니다.
- n은 1 이상, 25이하인 자연수입니다.


#### 입출력 예

|s|n|result|
|---|---|---|
|"AB"|1|"BC"|
|"z"|1|"a"|
|"a B z"|4|"e F d"|

---
## 문제 풀이
- 고려할 점 : 1. 공백인 경우 / 2. 대소문자 / 3. z를 넘는 경우 a부터 시작하도록

***Code***
``` c++
#include <string>
#include <vector>
#include <iostream>
#include <cctype>
#include <algorithm>

using namespace std;

char trans_s(int s){
    string alpha = "abcdefghijklmnopqrstuvwxyz";
    
    if (s > 74) return alpha[s - 75]; // z를 넘는 경우
    else return char(s + '0');
}

string solution(string s, int n) {
    string answer = "";
    
    for(auto &s_s : s){
        if(isupper(s_s)){ // 대문자인 경우
            int new_s = tolower(s_s) - '0' + n;
            answer += toupper(trans_s(new_s));
        } else if(islower(s_s)){ // 소문자인 경우
            int new_s = s_s - '0' + n;
            answer += trans_s(new_s);
        } else{
            answer += ' '; // 공백 처리
        }
    }
    return answer;
}

```
