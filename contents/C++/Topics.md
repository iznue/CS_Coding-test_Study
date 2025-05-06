# C++

## 1. 빌트인 데이터 타입
- 헤더 파일을 포함하지 않아도 사용할 수 있는 기본 내장 데이터 타입
- 정수형(Int), 부동소수형(Float or Double), 논리형(Bool), 문자형(Char), 배열(Array)

### 1.1 정수형
<details>
<summary>정수형 변수 선언 및 산술 연산</summary>
  
```c++
#include <iostream>

using namespace std;

int main() {
  int a = 13;
  int b = 4;
  cout << a + b << endl; // 더하기 : 17
  cout << a - b << endl; // 빼기 : 9 
  cout << a * b << endl; // 곱하기 : 52
  cout << a / b << endl; // 나누기 : 3
  cout << a % b << endl; // 모듈러 연산 : 1
  cout << -a << endl; // 부호 변환 : -13
  return 0;
}
```
</details>

<details>
<summary>정수형 비교 연산</summary>
  
```c++
#include <iostream>

using namespace std;

int main() {
  int a = 13;
  int b = 4;
  cout << (a == b) << endl; // 같은 값인지 비교 : 0
  cout << (a != b) << endl; // 다른 값인지 비교 : 1
  cout << (a > b) << endl; // 대소 비교(왼쪽이 더 큰지) : 1
  cout << (a < b) << endl; // 대소 비교(오른쪽이 더 큰지) : 0
  cout << (a >= b) << endl; // 왼쪽이 더 크거나 같은지 비교 : 1
  cout << (a <= b) << endl; // 오른쪽이 더 크거나 같은지 비교 : 0
  return 0;
}
```
- 참이면 1, 거짓이면 0 반환

</details>

<details>
<summary>정수형 비트 연산</summary>

```c++
#include <iostream>

using namespace std;

int main() {
  int a = 13;
  int b = 4;
  cout << (a & b) << endl; // and 연산 : 4
  cout << (a | b) << endl; // or 연산 : 13
  return 0;
}
```

![and_or](/contents/C++/img/and_or.png)
- 각 변수를 2진수로 표현했을 때 각 순서에 맞는 비트 값끼리 연산 수행

</details>

### 1.2 부동소수형

<details>
<summary>부동소수형 사칙 연산</summary>

```c++
#include <iostream>

using namespace std;

int main() {
  double d = 2.5;
  float f = 1.5f;

  cout << sizeof(d) << endl; // double형 데이터 크기 (byte) : 8
  cout << sizeof(f) << endl; // float형 데이터 크기 (byte) : 4
  cout << d << " " << f << endl; // 2.5 1.5
  cout << d + f << endl; // 4
  cout << d - f << endl; // 1
  cout << d * f << endl; // 3.75
  cout << d / f << endl; // 1.66667
  return 0;
}
```
- Float과 Double의 차이 ? : 유효한 소수점 자릿수
    - double : 8byte / float : 4byte
    - double의 유효한 소수점 자릿수가 더 많음
    - double은 15자리 / float은 7자리

</details>

<details>
<summary>형변환</summary>

```c++
#include <iostream>

using namespace std;

int main() {
  int i = 65;
  float f = 5.2f

  // 암시적 형 변환
  double d = i + f;
  cout << d << endl; // 70.2

  // 명시적 형 변환 double ➝ int
  cout << static_cast<int>(d) << endl; // 70
  // 명시적 형 변환 int ➝ char
  cout << static_cast<char>(i) << endl; // 'A'
  return 0;
}
```
- c++은 변수 선언 시 타입이 정해짐 &rarr; 구현 중 타입 변경필요 시 형변환을 해야 함
- Implicit Conversion : 타입이 서로 다른 변수간 연산을 해 발생하는 암시적 형 변환
    - 변수 메모리 크기가 큰 쪽으로 타입 변환
    - 예) 정수형과 부동소수형 연산시 결과는 부동소수형
- Explicit Conversion : 사용자가 임의로 변경하는 명시적 형 변환

</details>

### 1.3 문자열
- `getline(cin, s)` : 앞, 뒤 개행 문자들도 다 읽어옴
- `str.find(str2)`로 못찾는 경우 **string::npos를 반환하지만 -1을 반환한다 생각해도 됨**
- `str.find(str2, index)` : index부터 탐색
- `str.erase(index, size)` : 삭제 시작할 index와 크기
- `reverse(str.begin(), str.end())` : 문자열을 뒤집으며, 원본이 변경됨 (일부만 reverse도 가능)
- `atoi(str.c_str())` : 문자열로 입력된 숫자를 int로 변경 가능 (문자열인 경우 0 반환)
    - char 타입에는 적용 불가 : atoi(s[0].c_str())과 같이 사용 불가능
    - 예) str = "1D2T" &rarr; 1,2를 int로 변환하고 싶으면 : **atoi(str.substr(0,1).c_str())**

<details>
<summary>문자열 선언 및 초기화</summary>

```c++
#include <iostream>
#include <string>

using namespace std;

int main() {
  string str1; // 빈 문자열 선언
  string str2 = "Hello world!"; // 문자열 직접 초기화
  string str3(str2); // 문자열 복사
  string str4(str2, 0, 5); // 문자열 부분 복사 초기화 : "Hello"
  string str5(10, '*'); // 반복된 문자로 문자열 초기화 : '**********'
  return 0;
}
```
- 문자열은 string 표준 헤더를 추가해 사용할 수 있음
- 문자열 초기화 : 1. 대입 연산자 활용 2. 생성자로 다른 문자열을 복사 3. 특정 문자를 반복한 패턴의 문자열 생성

</details>

<details>
<summary>문자열 찾기</summary>

```c++
#include <iostream>
#include <string>

using namespace std;

int main() {
  // 문자열 초기화
  string_str = "Hello, C++ World!";

  // Hello 문자열 찾기
  size_t pos1 = str.find("Hello");
  cout << pos1 << endl; // 0

  // C 문자열 찾기
  size_t pos2 = str.find('C');
  cout << pos2 << endl; // 7

  // Hello 문자열 찾기, 시작 인덱스 지정
  size_t start_index = 2;
  size_t pos3 = str.find("Hello", start_index);
  cout << pos3 << endl; // 18446744073709551615

  // 존재하지 않는 문자열 찾기
  size_t pos4 = str.find("Python);
  cout << pos4 << endl; // 18446744073709551615

  return 0;
}
```
- 특정 문자나 문자열을 찾을 때는 `find()` 메서드를 사용함
    - **find(찾으려는 문자열)**
    - **find(찾으려는 문자열, 탐색 시작 위치)**
    - 문자열을 찾으면 해당 문자열이 시작하는 인덱스를 반환하고, 찾지 못하면 **string::npos 반환**
    - 탐색하는 문자열의 길이가 N일 때 find() 메서드는 `O(N)`으로 동작
- 18446744073709551615 출력 값 = `string::npos`
- `size_t` : 보통 **컨테이너나 문자열의 크기 및 인덱스 표현** 시 해당 타입 사용


```c++
#include <iostream>
#include <string>

using namespace std;

int main() {
  string str = "APPLE";
  str += ", World!"; // 문자열 추가
  cout << str << endl; // APPLE, World!

  // 문자열 수정
  str[7] = 'P';
  cout << str << endl; // APPLE, Porld!

  str.replace(7, 4, "Col"); // 7번째 문자부터 4개의 문자열을 'col'로 변경
  cout << str << endl; // APPLE, Cold!

  return 0;
}
```
</details>

<details>
<summary>문자열 자르기</summary>
- string 사용
  
```c++
#include <iostream>
#include <string>

using namespace std;

int main() {
    string str = "apple,banana,orange";
    size_t pos = 0;
    string token;
    
    while ((pos = str.find(',')) != string::npos) {
        token = str.substr(0, pos);
        cout << token << endl;
        str.erase(0, pos + 1);
    }
    cout << str << endl; // 마지막 토큰
}
```
- `s.substr(추출 시작 위치 인덱스, 글자 수)` : 문자 일부 추출 / **해당 부분이 erase되지 않음 !**

- stringstream 사용

```c++
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int main() {
    string str = "apple banana orange";
    stringstream ss(str);
    string token;
    
    while (ss >> token) {
        cout << token << endl;
    }
}
```

</details>

<details>
<summary>대소문자 변환</summary>

```c++
#include <iostream>
#include <string>
#include <cctype>  // for toupper, tolower

using namespace std;

int main() {
    string s = "AbCde";
    
    // 소문자로 변환
    for (char &c : s) c = tolower(c);
    cout << s << endl;  // abcde
    
    // 대문자로 변환
    for (char &c : s) c = toupper(c);
    cout << s << endl;  // ABCDE
}
```

```c++
#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>

using namespace std;

int main() {
    string s = "AbCde";

    // 소문자로
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    cout << s << endl;  // abcde

    // 대문자로
    transform(s.begin(), s.end(), s.begin(), ::toupper);
    cout << s << endl;  // ABCDE
}
```

</details>

<details>
<summary>알파벳 제외 특수문자 / 공백을 공백으로 바꾸기</summary>

```c++
#include <iostream>
#include <string>
#include <cctype>

using namespace std;

int main() {
    string s = "He!!o, Wo@rld!";
    
    for (char &c : s) {
        if (!isalpha(c)) c = ' ';
    }
    
    cout << s << endl;  // He  o  Wo rld 
}
```

```c++
#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
using namespace std;

int main() {
    string s = "He!!o, Wo@rld!";

    // 알파벳이 아닌 모든 문자를 ' '로 바꾸기
    replace_if(s.begin(), s.end(), [](char c) {
        return !isalpha(c);
    }, ' ');

    cout << s << endl;  // He  o  Wo rld 
}
```

```c++
#include <algorithm>
using namespace std;

bool wordChange(char c) {
    return c == '\'' || !isalpha(c); 
    //파라미터 속 문자가 ' 이거나 alphabet이 아닌경우 return
}

int main() {
    string line = "h{el@@lo \tmy \"namelo<<e is yeo>>>n";
    replace_if(line.begin(), line.end(), wordChange, ' ');
    cout << line << "\n";
    return 0;
}
```

</details>

### 1.4 변수형 변환

<details>
<summary>str → char</summary>

```c++
char cst[100];
string str = "hello";

strlen(cstr, str.c_str());
```
</details>

<details>
<summary>char → str</summary>

```c++
char cst[100];
char *cst = "hello";

string str = cst;
```
</details>

<details>
<summary>char → int</summary>

```c++
// int의 경우 '0' 빼기
```
</details>

<details>
<summary>str → int</summary>

```c++
string str = "100";
int num;

num = atoi(str.c_str());
```
</details>

<details>
<summary>int → str</summary>

```c++
int num = 10;
string str;

str = to_string(num);
```
</details>

---
## 2. STL (Standard Template Library)
- c++에서 제공하는 템플릿 기반 표준 라이브러리 : 함수나 클래스 구현 시 어떤 타입에서도 동작할 수 있게 하는 문법
- 특정 타입에 한정하지 않고 라이브러리 사용 가능
- 데이터를 담을 수 있는 **Container**, 데이터 처리 및 제어하는 **Algorithm**, 컨테이너에 접근 및 순회 가능한 **Iterator**

### 2.1 STL과 자주 사용하는 필수 문법

<details>
<summary>상수 레퍼런스</summary>

### Call by value
```c++
#include <iostream>

using namespace std;

void modify(int value) {
  value = 10; // 새 공간의 value 변경
  cout << "주소 : " << &value << endl; // 주소 : 0x7fff84f16e5c
  cout << "값 : " << value << endl; // 변경한 값 출력 : 10
  // 함수가 종료되면 modify() 함수의 value는 메모리에서 사라짐
}

int main() {
  int value = 5;
  cout << "주소 : " << &value << endl; // 주소 : 0x7fff84f16e5c
  cout << "값 : " << value << endl; // 값 : 5
  modify(value);
  cout << "값 : " << value << endl; // 값 : 5

  return 0;
}
```

![call_by_value](/contents/C++/img/call_by_value.png)

- 함수의 인수로 값을 전달할 때 값을 복사함 = `Call by value`
- 함수가 호출될 때마다 함수의 인수로 값이 전달되며 복사하는 비용이 듦
- 예시에서는 modify() 함수에서 value 값이 10으로 바뀌지만 main() 함수 value 변수에는 영향을 미치지 않음

### Call by reference
```c++
#include <iostream>

using namespace std;

void modify(int& value) {
  value = 10; // main()의 value 값 자체 변경
  cout << "주소 : " << &value << endl; // 주소 : 0x7fff6272fc34
  cout << "값 : " << value << endl; // 변경한 값 출력 : 10
}

int main() {
  int value = 5;
  cout << "주소 : " << &value << endl; // 주소 : 0x7fff6272fc34
  cout << "값 : " << value << endl; // 값 : 5
  modify(value);
  cout << "값 : " << value << endl; // 값 : 10

  return 0;
}
```

![call_by_reference](/contents/C++/img/call_by_reference.png)

- 실제 값이 바뀌어야 하는 경우 : 규모가 큰 객체를 함수의 인수로 넘길 때는 객체 전체를 복사하지 않고 레퍼런스를 활용해 넘김 = `Call by reference`
- `&` 문법을 사용해 변수 자체를 복사하지 않고 **참조자**를 통해 변수에 접근 및 수정

</details>

#### 참조값 전달과 주소값 전달의 공통점 / 차이점
- 참조값(레퍼런스 사용)이 아닌 주소값을 전달(포인터 사용)하여 함수 호출 시 전달된 인수를 수정하는 방식도 있음
- 공통점 : 실 인수값 변경 가능


- 차이점
    - 1. 참조값 전달 시 참조 변수와 참조대상 변수의 주소값이 일치하므로 메모리 값을 읽고 쓰기 위한 추가 문법 필요 X
    - 2. 주소값 전달 시 주소값을 전달받은 변수의 주소와 실제 변수의 주소값이 다르므로 주소 값을 받기 위한 포인터 변수를 사용해야함

&rarr; ***실인수값을 변경한다는 목적에서는 차이가 없지만 포인터 문법을 사용하는지에서 차이가 존재함***

<details>
<summary>auto 문</summary>

```c++
#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

int main() {
  auto num = 42;
  cout << num << endl // int로 추론 : 42

  auto pi = 3.15159;
  cout << pi << enld; // double로 추론 : 3.14159

  auto greeting = string("Hello, world!");
  cout << greeting << endl; // string으로 추론 : Hello, world!

  return 0;
}
```
- 타입이 복잡해지면 사용 시 실수하기 쉽고 가독성이 떨어질 수 있음 &rarr; `auto`를 사용하면 **변수 타입을 자동으로 추론**

</details>

<details>
<summary>범위 기반 반복문</summary>

```c++
#include <iostream>
#include <vector>
#include <map>
#include <set>

int main() {
  vector<int> vec = {1,2,3,4,5};
  for (int num : vec) {
    cout << num << " ";
  }
  cout << endl; // 1 2 3 4 5

  map<string, int> fruitMap = {{"apple", 1}, {"banana", 2}, {"cherry", 3}};
  for (const auto& pair : fruitMap) {
    cout << pair.first << "=" << pair.second << " ";
  }
  cout << endl; // apple = 1 banana = 2 cherry = 3

  set<string> fruitSet = {"apple", "banana", "cherry"};
  cout << "Set : ";
  for (const auto& fruit : fruitSet) {
    cout << fruit << " ";
  {
  cout << endl; // apple banana cherry
  return 0;
}
```
- 배열 또는 컨테이너의 모든 원소 순회 시 사용
- STL 컨테이너와 사용 시 값을 수정할 필요가 없으므로 auto 대신 상수 레퍼런스를 적용한 **const auto& 사용**
- 컨테이너를 반복문에서 사용하거나 함수의 인수로 넘길 때는 항상 복사 비용을 고려해야 함
- 수정 시 **레퍼런스**, 수정하지 않아야 할 때는 **상수 레퍼런스** 적용 고려

</details>

### 2.2 반복자

- iterator는 컨테이너(vector, map, set 등)의 종류와 관계없이 원소들을 순회하고 접근할 수 있게 함
- 컨테이너가 바뀌더라도 반복자로 접근하는 코드는 수정할 필요가 없음 &rarr; 유지보수 & 재사용성 향상

<details>
<summary>순방향 반복자</summary>

```c++
#include <iostream>
#include <algorithm> // find 함수를 위한 헤더
#include <vector>

using namespace std;

int main() {
  vector<int> vec = {10,20,30,40,50};

  for (auto it = vec.begin(); it != vec.end(); ++it) {
    cout << *it << " ";
  }
  cout << endl; // 10 20 30 40 50

  auto result = find(vec.begin(), vec.end(), 30);
  if (result != vec.end()) {
    cout << "Found : " << *result << endl;
  } else {
    cout << "Not found" << endl;
  }
  // 30
  return 0;
}
```

```c++
#include <iostream>
#include <map>

using namespace std;

int main() {
  map<string, int> myMap = {{"apple", 1}, {"banana", 2}, {"cherry", 3}};

  for (auto it = myMap.begin(); it != myMap.end(); ++it){
    cout << it->first << ": " << it->second << endl;
  }
/*
  apple : 1
  banana : 2
  cherry : 3
*/

  auto result = myMap.find("banana");
  if (result != myMap.end()) {
    cout << "Found: " << result->first << " -> " << result->second << endl;
  } else {
    cout << "Not found" << endl;
  {
/*
  Found : banana -> 2
*/
  return 0;
}
```

- 컨테이너의 원소를 순차적으로 순회
- 순방향 반복자는 `begin()`과 `end()`가 쌍으로 나오는 경우가 많음
    - **begin()** : 컨테이너의 첫 원소 위치
    - **end()** : 컨테이너의 마지막 원소 위치

1. 대부분 시작 위치와 끝 위치를 받고 시착 위치는 begin(), 끝 위치는 end()로 넘기는 경우가 많음
2. 특정 원소 탐색 또는 조건에 맞는 원소를 찾는 경우 해당 원소를 찾으면 위치를 반환하고, 그렇지 않으면 end()를 반환함

</details>

<details>
<summary>역방향 반복자</summary>

```c++
#include <iostream>
#include <algorithm> // find 함수를 위한 헤더
#include <vector>

using namespace std;

int main() {
  vector<int> vec = {10,20,30,40,50};

  for (auto it = vec.rbegin(); it != vec.rend(); ++it) {
    cout << *it << " ";
  }
  cout << endl; // 50 40 30 20 10

  auto result = find(vec.rbegin(), vec.rend(), 30);
  if (result != vec.rend()) {
    cout << "Found: " << *result << endl;
  } else {
    cout << "Not found" << endl;
  }
  // 30
  return 0;
}
```

- 컨테이너의 끝에서 시작으로 이동함
- 순방향 반복자와의 차이 : ++ 연산자 사용 시 역방향 반복자는 이전 원소로 위치가 바뀜
- `rbegin()` : 맨 마지막 원소의 위치 / `rend()` : 맨 처음 원소의 바로 직전 위치 

</details>

### 2.3 STL의 컨테이너
- 데이터를 저장하는 객체 : vector, set, map, priorityqueue
- 데이터를 어떤 방식으로 저장하고 접근하는지 아는게 중요
- 예) 저장된 데이터에 배열처럼 임의 접근 필요 : 벡터 선택
- 예) '키-값' 형태로 저장 필요 : 맵 선택

#### 2.3.1 Vector

- 크기가 가변적인 배열 : 동적 할당
- `front()` : 첫번째 원소 / `back()` : 마지막 원소 / `begin()` : 첫번째 위치 / `end()` : 마지막의 다음 위치
- `push_back()` : 마지막에 데이터 추가 / `pop_back()` : 마지막에서 데이터 뽑기 / `size()` : 원소 개수 / `clear()` : 비우기
- 벡터에 pair도 들어갈 수 있음 !
- `accumulate(v.begin(), v.end(), 0)` : 특정 배열 값들의 합 구하기 &rarr; 시작값을 반드시 넣어야 함

<details>
<summary>1차원 벡터의 선언 및 초기화</summary>

```c++
#include <vector>

using namespace std;

vector<int> v;
vector<int> v2 = {1,2,3,4,5};
vector<int> v3(4,3);
vector<int> v4(v3);

vector<int> v5(n); // 0으로 n개 생성
vector<int> v6(n, x); // x로 n개 원소 생성

v5.resize(n) // 기본값 0으로 벡터 사이즈를 더 키울 수 있음
```

![vector](/contents/C++/img/vector.png)

- STL은 템플릿 기반으로 구현되어 있으므로 int 대신 char, double, string, 사용자 정의형 모드 사용 가능
- v는 빈 벡터, v2는 초기화 리스트를 활용해 초기화와 동시에 원소를 넣은 벡터
- v3은 초기 벡터 크기를 4로 하고 모든 원소를 3으로 채움
- v4는 v3을 복사해 독립된 새 벡터를 생성함

</details>

<details>
<summary>2차원 벡터의 선언 및 초기화</summary>

```c++
#include <vector>
#include <iostream>

using namespace std;

vector<vector<int>> v1;

// 특정 크기로 초기화된 2차원 벡터
int rows = 3;
int cols = 4;
vector<vector<int>> v2(rows, vector<int>(cols));

// 특정 값으로 초기화된 2차원 벡터
int val = 9;
vector<vector<int>> v3(rows, vector<int>(cols, val));

// 초기화 리스트를 사용한 2차원 벡터 초기화
vector<vector<int>> v4 = {
  {1,2,3},
  {4,5,6},
  {7,8,9}
};
```

![2d_vector](/contents/C++/img/2d_vector.png)

</details>

<details>
<summary>백터의 원소 변경</summary>

```c++
#include <vector>
#include <iostream>

using namespace std;

int main() {
  vector<int> vec = {1,2,3,4,5};

  vec[2] = 10;
  return 0;
}
```

- `[]` 연산자를 활용하면 배열과 방식이 같고 시간 복잡도는 `0(1)`임

</details>

<details>
<summary>백터의 삽입과 삭제</summary>

```c++
#include <vector>
#include <iostream>

using namespace std;

int main() {
  vector<int> v = {2,3,4,5};

  // 맨 뒤에 원소 삽입
  v.push_back(6);

  // 맨 뒤의 원소 삭제
  v.pop_back();

  // 맨 앞에 원소 삽입
  v.insert(v.begin(), 1);

  // 맨 앞의 원소 삭제
  v.erase(v.begin());

  v.erase(v.begin() + index) // index 위치에 있는 데이터 삭제 가능
  v.erase(v.begin() + s, v.begin() + e) // s부터 e-1까지의 인덱스 삭제

  return 0;
}
```

- 벡터 내부는 배열로 구성됨 &rarr; 맨 뒤에서 삽입, 삭제 연산을 효율적으로 할 수 있지만 맨 앞에서 삽입, 삭제 연산은 비효율적
    - 맨 앞 원소 삽입, 삭제 시에 뒤의 원소들은 한칸씩 이동해야하므로 벡터에 데이터가 N개가 있으면 시간복잡도가 0(N)
- 맨 앞에 원소를 효율적으로 삽입, 삭제할 수 있는 자료구조 = `Dequq` : **시간복잡도 0(1)**
- 맨 뒤에 원소 삽입 : `push_back()` / 맨 뒤 원소 삭제 : `pop_back()`

</details>

#### 2.3.2 Set
- 중복을 허용하지 않고, 저장된 데이터를 자동으로 정렬(오름차순)하는 컨테이너
- `insert(k)` : 원소 k 삽입 / `begin()` : 맨 첫 원소를 가리키는 iterator 반환 / `end()` : 맨 끝 원소를 가리키는 iterator 반환
- `find(k)` : 원소 k를 가리키는 iterator 반환 / `size()` : set의 원소 수 / `empty()` : set이 비어있는지 확인

<details>
<summary>셋의 선언 및 초기화</summary>

```c++
#include <iostream>
#include <set>

using namespace std;

set<int> s1; // 빈 셋 선언
set<int> s2 = {3,1,3,2,5}; // 초기화 리스트를 사용한 셋 초기화
set<int> s3(s2); // 다른 셋을 사용한 초기화
// s2, s3는 {1,2,3,5} : 셋은 중복값을 허용하지 않고 내부 정렬 수행함
```

- 정렬 : 배열처럼 메모리에 순차적으로 저장된다는 의미가 아닌 **트리 구조를 통해 정렬 상태 유지**

</details>

<details>
<summary>셋의 원소 탐색</summary>

```c++
#include <iostream>
#include <set>

using namespace std;

int main() {
  set<int> numbers = {1,2,3,4,5}'
  int targets[] = {3,7};
  for (int target : targets) {
    auto it = numbers.find(target);

    if (it != numbers.end()) {
      cout << "원소 " << target << "를 찾았습니다. 값 : " << *it << endl;
    } else {
      cout << "원소 " << target << "를 찾지 못했습니다." << endl;
    }
  }
  return 0;
}
/*
원소 3를 찾았습니다. 값 : 3
원소 7를 찾지 못했습니다.
*/
```

- find() 메서드로 찾는 원소가 있으면 원소 위치 반환, 없으면 end 반복자 반환
- 셋의 크기가 N일 때 find()의 **시간복잡도 : 0(logN)**

</details>

<details>
<summary>셋의 삽입 삭제</summary>

```c++
#include <iostream>
#include <set>

using namespace std;

int main() {
  set<int> s = {1,3,2,1,5};

  s.insert(4);

  s.erase(2);

  auto it = s.find(4);
  if (it != s.end()) {
    s.erase(it);
  }
  return 0;
}
```

![set_insert_erase](/contents/C++/img/set_insert_erase.png)

- 셋은 모든 삽입, 삭제의 **시간복잡도 : 0(logN)** &rarr; 삽입, 삭제 후에도 정렬된 상태를 유지하므로
- 삽입 : `insert()`, 삭제 : `erase()`
    - erase() 메서드에는 삭제할 원소의 값이 올 수도 있고, 삭제할 원소의 주소가 올 수도 있음
    - erase() 메서드에 원소의 주소를 인수로 넘기는 경우 s의 원소 주소에 해당되지 않는 주소를 넘기면 프로그램이 정상 동작 X
    - find() 메서드를 활용해 특정 값이 있는지 확인할 때 end 반복자가 아닐 때만 erase() 메서드 수행

</details>

#### 2.3.3 Map
- 키와 값을 쌍으로 갖는 컨테이너
- 키와 값의 쌍 : `entry` &rarr; STL에서는 `std::pair` 타입으로 표현
- 내부는 균형 이진 탐색트리로 구성되어 있어 항상 **키 값을 기준으로 데이터가 자동 정렬(오름차순)됨**
- 키 기준 검색, 삽입, 삭제 **시간복잡도 : 0(logN)**
- 맵의 키 값은 중복되지 않고 유일함 !
- 맵은 배열과 같이 정수형 인덱스로 한정되지 않고, 키 자체를 통해 원하는 값을 찾을 수 있음
- `insert(make_pair(k, v))` : 원소를 key와 value의 pair로 삽입 / `erase(k)` : key 값 k를 갖는 원소 삭제
- `begin()` : 맨 첫 원소를 가리키는 iterator 반환 / `end()` : 맨 마지막 원소를 가리키는 iterator 반환
- `find(k)` : key 값 k에 해당하는 iterator 반환 / `size()` : map의 원소 수 / `empty()` : map이 비어있는지 확인

<details>
<summary>맵의 선언 및 초기화</summary>

```c++
#include <iostream>
#include <map>

using namespace std;

map<string, double> employeeSalaries;

map<string, double> studentGrades = {
  {"John", 3.7},
  {"Emma", 3.9},
  {"Sophia", 4.0}
};
```

</details>

<details>
<summary>맵의 특정 키 접근</summary>

```c++
#include <iostream>
#include <map>

using namespace std;

int main() {
  map<string, int> studentScores;

  studentScores["Alice"] = 95;
  studentScores["Bob"] = 88;
  studentScores["Charlie"] = 92;

  int score1 = studentScores["Alice"];
  cout << score1 << endl; // 95

  int score2 = studentScores["Rabbit"];
  cout << score2 << endl; // 0

  auto it = studentScores.find("Charlie");
  if (it != studentScores.end()) {
    int score3 = it->second;
    cout << score3 << endl; // 92
  }
  return 0;
}
```

![map](/contents/C++/img/map.png)

1. [] 연산자 활용
    - 배열과 다르게 [] 연산자를 통해 접근하려는 키가 맵에 없으면 맵에 현재 키를 추가함
    - **맵에 없는 키에 접근하려 하면 오류가 발생하지 않고 새로운 키가 만들어짐**
    - 시간 복잡도 0(logN)
2. find() 메서드 활용
    - 특정 키 검색 시 맵에 새로운 키를 추가하는게 아니라 키가 없는 상태를 유지해야 하는 경우 사용
    - 키가 맵에 있으면 해당 키의 위치를 반환하고 없으면 end 반복자 반환
    - 시간 복잡도 0(logN)
- 각 원소는 pair 객체이므로 멤버 변수로 first(키)와 second(값)를 가짐

</details>

<details>
<summary>맵의 값 변경</summary>

```c++
#include <iostream>
#include <map>

using namespace std;

int main() {
  map<string, int> myMap = {{"Apple", 1}, {"Banana", 2}, {"Cherry", 3}};

  myMap["Banana"] = 10; // "Banana" 키에 해당하는 값을 10으로 수정
  return 0;
}
```
- 벡터와 마찬가지로 [] 연산자 활용
- 인덱스가 숫자가 아닐 수도 있음

</details>

<details>
<summary>맵의 삽입 삭제</summary>

```c++
#include <iostream>
#include <map>

using namespace std;

int main() {
  map<int, string> myMap;

  myMap.insert(make_pair(1, "Apple"));
  myMap.insert({2, "Banana"});
  myMap[3] = "Cherry";

  for (const auto &pair : myMap) {
    cout << pair.first << " : " << pair.second << endl;
  }
/*
1 : Apple
2 : Banana
3 : Cherrry
*/

  myMap.erase(2);

  for (const auto &pair : myMap) {
    cout << pair.first << " : " << pair.second << endl;
  }
/*
1 : Apple
3 : Cherry
*/

  auto it = myMap.find(3);
  if (it != myMap.end()) {
    myMap.erase(it);
  }

  for (const auto &pair : myMap) {
    cout << pair.first << " : " << pair.second << endl;
  }
// 1 : Apple

  return 0;
}
```
- 원소 삽입 방법
    1. `insert()` 메서드 활용 : 인수로 pair 객체를 받는데, 이때 **make_pair()** 함수를 쓰거나 **{}** 사용
    2. `[]` 연산자 활용
    - 삽입 연산 **시간복잡도 : 0(logN)**

- 원소 삭제 방법
    - `erase()` 메서드 사용
    - 인수로 키값 혹은 키의 위치를 넣으면 해당 키 혹은 위치의 원소가 삭제됨
    - 인수로 값을 넘길 때 **시간복잡도 : 0(logN)** / 위치를 넘길 때 **시간복잡도 : 0(1)**

</details>

<details>
<summary>정렬되지 않은 셋과 맵</summary>

```c++
#include <iostream>
#include <unordered_set>

using namespace std;

int main() {
  unordered_set<int> myUnorderedSet;

  myUnorderedSet.insert(3);
  myUnorderedSet.insert(1);
  myUnorderedSet.insert(4);
  myUnorderedSet.insert(2);

  for (int num : myUnorderedSet) {
    cout << num << " ";
  }
  cout << endl;
  // 2 4 1 3
  return 0;
}
```

```c++
#include <iostream>
#include <unordered_map>

using namespace std;

int main() {
  unordered_map<string, int> myUnorderedMap;

  myUnorderedMap["apple"] = 3;
  myUnorderedMap["banana"] = 1;
  myUnorderedMap["cherry"] = 4;
  myUnorderedMap["date"] = 2;

  for (const auto& pair : myUnorderedMap) {
    cout << pair.first << ": " << pair.second << endl;
  }

  /*
    출력값
    date: 2
    cherry: 4
    banana: 1
    apple: 3
  */

  return 0;
}
```
- c++ STL의 셋과 맵은 내부 구조가 이진 탐색 트리여서 정렬 상태를 유지함
- 자동 정렬이 무조건 좋은 것은 아님 &rarr; 성능 저하를 일으킬 수 있음
- `unordered_set` / `unordered_map` : 내부 구조가 해시 기반이므로 데이터를 자동 정렬하지 않음
    - 삽입, 삭제, 탐색의 **시간복잡도 : 0(1)**
    - 기존 정렬되는 셋, 맵의 0(logN)에 비해 빠름
- 정렬되지 않은 셋 사용 : **#include <unordered_set>** / 정렬되지 않은 맵 사용 : **#include <unordered_map>**

</details>

#### 2.3.4 Pair
- 두가지 자료형을 하나의 쌍으로 묶을 수 있게 함
- vector나 algorithm 헤더 파일에 포함됨
- **첫번째 데이터는 first, 두번째 데이터는 second로 접근**
- **p = make_pair(f,s)**로 한번에 대입 가능

<details>
<summary>pair</summary>

```c++
#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

int main(int argc, const char * argv[]) {
    pair<int, char> p;
    
    scanf("%d %c", &p.first, &p.second);
    printf("%d %c\n", p.first, p.second);
    
    p.first = 1;
    p.second = 'a';
    printf("%d %c\n", p.first, p.second);
    
    p=make_pair(3, 'b');
    printf("%d %c\n", p.first, p.second);
    
}
```

</details>

#### 2.3.5 Queue
- FIFO 자료구조 : BFS에 유용함
- Queue 헤더 파일을 추가해 사용
- `push()` : 마지막에 데이터 추가 / `pop()` : 맨 앞에서 데이터 뽑기 / `front()` : 첫번째 원소 / `back()` : 마지막 원소
- `size()` : queue의 크기 / `empty()` : queue가 비어있는지 확인

<details>
<summary>queue</summary>

```c++
#include <iostream>
#include <cstdio>
#include <queue>

using namespace std;

int main(int argc, const char * argv[]) {
    queue<int> q1;
    queue<pair<int, char>> q2;

    int a, b;
    int n;
    char c, d;
    
    q1.push(1);
    q1.push(2);
    q1.push(3);
    q1.push(4);
    q1.push(5);
    q1.push(6);
    a = q1.front();
    b = q1.back();
    n = q1.size();
    
    for(int i=0; i<n; i++){
        printf("%d ", q1.front()); q1.pop();
        // 1 2 3 4 5 6
    }
    printf("\n");
    
    printf("front: %d, back: %d\n", a, b); // front: 1, back: 6
    q2.push(make_pair(1, 'a'));
    q2.push(make_pair(2, 'b'));
    q2.push(make_pair(3, 'c'));
    q2.push(make_pair(4, 'd'));
    q2.push(make_pair(5, 'e'));
    
    a = q2.front().first;
    c = q2.front().second;
    b = q2.back().first;
    d = q2.back().second;
    n = q2.size();
    for(int i=0; i<n; i++){
        printf("<%d %c> ", q2.front().first, q2.front().second);
        q2.pop();
        // <1 a> <2 b> <3 c> <4 d> <5 e>
    }
    printf("\n");
    printf("front: <%d %c>, back: <%d %c>\n", a, c, b, d);
    // front: <1 a>, back: <5 e>
}
```

</details>

#### 2.3.6 Stack
- LIFO 자료구조 (Last in First out)
- stack 헤더 파일을 추가해 사용
- `push()` : top에 데이터 추가 / `pop()` : top에서 데이터 뽑기 / `top()` : top에 있는 원소 
- `size()` : stack의 크기 / `empty()` : stack이 비어있는지 확인

<details>
<summary>stack</summary>

```c++
#include <iostream>
#include <cstdio>
#include <stack>

using namespace std;

int main(int argc, const char * argv[]) {
    stack<int> s1;
    stack<pair<int, char>> s2;

    int a, b;
    int n;
    char c, d;
    
    s1.push(1); s1.push(2); s1.push(3);
    s1.push(4); s1.push(5); s1.push(6);
    
    a = s1.top();
    n = s1.size();
    
    for(int i=0; i<n; i++){
        printf("%d ", s1.top()); s1.pop();
        // 6 5 4 3 2 1
    }
    printf("\n"); printf("top: %d\n", a); // top: 6
    
    s2.push(make_pair(1, 'a'));
    s2.push(make_pair(2, 'b'));
    s2.push(make_pair(3, 'c'));
    s2.push(make_pair(4, 'd'));
    s2.push(make_pair(5, 'e'));
    
    a = s2.top().first;
    c = s2.top().second;
    n = s2.size();
    for(int i=0; i<n; i++){
        printf("<%d %c> ", s2.top().first, s2.top().second);
        s2.pop();
        // <5 e> <4 d> <3 c> <2 b> <1 a>
    }
    printf("\n");
    printf("top: <%d %c>\n", a, c); // top: <5 e>
}
```

</details>

#### 2.3.7 Priority Queue
- `push()` : top에 데이터 추가 / `pop()` : top에서 데이터 뽑기 / `top()` : top에 있는 원소
- `size()` : priority queue의 크기 / `empty()` : priority queue가 비어있는지 확인

<details>
<summary>priority queue</summary>

```c++
#include <iostream>
#include <cstdio>
#include <queue>

using namespace std;

int main(int argc, const char * argv[]) {
    priority_queue<int, vector<int>, less<int>> q;
    int n;
    q.push(3); q.push(2);
    q.push(5); q.push(4);
    q.push(1); q.push(6);
    
    printf("top: %d\n", q.top()); // top: 6
    n = q.size();
    
    for(int i=0; i<n; i++){
        printf("%d ", q.top());
        q.pop();
        // 6 5 4 3 2 1
    }
    printf("\n");
}
```

</details>

### 2.4 STL의 알고리즘 

#### 2.4.1 Count

<details>
<summary>count() 함수</summary>

```c++
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
  vector<int> v = {1,4,3,4,5,4,5};

  int ret = count(v.begin(), v.end(), 5);

  cout << ret << endl; // 2
  return 0;
}
```
- count() 함수의 인자 : 시작 반복자, 끝 반복자, 확인할 값
- **시간복잡도 : 0(N)** : 범위로 지정한 원소의 개수가 N개인 경우

</details>

#### 2.4.2 Sort (정렬)

<details>
<summary>sort() 함수</summary>

```c++
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
  std::vector<int> v = {4,2,5,3,1};

  sort(v.begin(), v.end()); // 오름차순 정렬 : 1 2 3 4 5

  sort(v.rbegin(), v.rend()); // 내림차순 정렬 : 5 4 3 2 1

  return 0;
}
```

```c++
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Point {
  int x, y;
  Point(int x, int y) : x(x), y(y) {}
};

// 사용자 정의 비교 함수
bool compare(const Point &a, const Point &b) {
  if (a.x == b.x) {
    return a.y < b.y; // x 좌표가 같으면 y 좌표가 작은 순서대로 정렬
  }
  return a.x < b.x; // x 좌표가 작은 순서대로 정렬
}

int main() {
  vector<Point> points = {{3, 4}, {1, 2}, {3, 1}, {2, 5}};

  // points 벡터를 사용자 정의 기준으로 정렬
  sort(points.begin(), points.end(), compare);

  // 정렬된 벡터 출력
  for (const Point &p : points) {
    cout << "(" << p.x << ", " << p.y << ") ";
  }
  cout << endl;
  // 출력값 : (1, 2), (2, 5), (3, 1), (3, 4)

  return 0;
}
```
- sort(시작 반복자, 끝 반복자)
- sort(시작 반복자, 끝 반복자, 비교 함수)
- 인수를 2개 받을 때는 범위 내 원소들을 **오름차순 정렬**
- 인수를 3개 받을 때는 **비교 함수 기준 정렬**
- 사용자가 정의한 타입의 원소를 정렬하려면 sort() 함수를 활용해야 함 : **시간복잡도 : 0(NlogN)**

</details>

#### 2.4.3 Next_permutation (순열)

<details>
<summary>next_permutation() 함수</summary>

```c++
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  vector<int> v = {1, 2, 3};
  // 모든 가능한 순열 출력
  do {
    for (int i : v) {
      cout << i << " ";
    }
    cout << endl;
  } while (next_permutation(v.begin(), v.end()));
  return 0;
}
/*
출력값:
1 2 3
1 3 2
2 1 3
2 3 1
3 1 2
3 2 1
*/
```
- 가능한 모든 순열 생성 : 인수는 시작 반복자와 끝 반복자를 받음
- 사전 순으로 생성하며, 실제 범위 내 원소들의 위치가 변경됨
- 가능한 순열이 있으면 true, 더 이상 가능한 순열이 없으면 false 반환
- 가능함 모든 순열 생성 시 주로 사용하며 while 내에서 함수를 호출하는 패턴이 많음
- **시간복잡도 : 0(N*N!)**
- 가능한 모든 순열을 생성하려면 **데이터가 사전 순으로 정렬된 상태여야만 함 !**

</details>

#### 2.4.4 Unique (중복 정리)

<details>
<summary>unique() 함수</summary>

```c++
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
vector<int> v = {1, 2, 2, 3, 3, 3, 4, 4, 5, 5, 5};

// unique 함수를 사용하여 중복 요소 제거
auto newEnd = unique(v.begin(), v.end());

// 중복되지 않는 요소들만 출력
for (auto it = v.begin(); it != newEnd; ++it) {
  cout << *it << " ";
}
cout << endl;
// 1 2 3 4 5

// 벡터의 크기 출력
cout << v.size() << endl; // 11

// 전체 원소 출력
for (auto it = v.begin(); it != v.end(); ++it) {
  cout << *it << " ";
}
cout << endl;
// 1 2 3 4 5 3 4 4 5 5 5

  return 0;
}
```

![unique](/contents/C++/img/unique.png)

- 컨테이너 내 중복 원소들을 뒤로 밀어내고 중복되지 않은 원소들만 남겨 새로운 범위의 끝 반복자 반환
- 인수는 시작 반복자와 끝 반복자를 받음
- 데이터 개수가 N개 일 때 **시간복잡도 : 0(N)**

</details>

#### 2.4.5 Binary Search (이진 탐색)

<details>
<summary>binary_search() 함수</summary>

```c++
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  vector<int> v = {1, 2, 3, 4, 5};

  cout << binary_search(v.begin(), v.end(), 3) << endl; // 1
  cout << binary_search(v.begin(), v.end(), 7) << endl; // 0

  return 0;
}
```

- 컨테이너에서 주어진 범위 내 원소에 이진 탐색 수행
- 인수는 시작 반복자, 끝 반복자, 찾을 값을 받음
- 탐색 수행 후 원소가 있으면 true 없으면 false 반환
- 데이터의 개수가 N개 일 때 **시간복잡도 : 0(logN)**
- 이진 탐색 특성 상 원소가 정렬되어 있어야 정상 동작 : 데이터가 정렬되어 있고, 원소를 자주 탐색해야 할 때 배열 탐색보다 유용

</details>

#### 2.4.6 Max, Min (최대, 최소)

<details>
<summary>max_element(), min_element() 함수</summary>

```c++
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
  vector<int> v = {1, 3, 5, 7, 2, 4, 6};

  auto maxIt = max_element(v.begin(), v.end());
  auto minIt = min_element(v.begin(), v.end());

  cout << *maxIt << endl; // 7
  cout << *minIt << endl; // 1

  return 0;
}
```

- 인수로 시작 반복자와 끝 반복자를 받음
- 데이터의 개수가 N개일 때 **시간복잡도 : 0(N)**

</details>

---
## 3. 함수

<details>
<summary>함수 정의</summary>
  
```c++
// 정수형을 반환하는 func1 함수
int func1(param1, param2..., paramN) {
  // 함수의 실행 코드
  // …
  // …
  return result; // 반환값
}
```
- 반환하는 값이 없다면 반환 타입에 void 사용

</details>

<details>
<summary>함수 호출</summary>
  
```c++
#include <iostream>

using namespace std;

// 두 수를 더하는 함수
int add(int num1, int num2) {
  return num1 + num2;
}

int main() {
  int a = 5;
  int b = 10;

  // add 함수를 호출하여 결과 출력
  cout << add(a, b) << endl; // 15
  return 0;
}
```

</details>

---
## 4. ETC

<details>
<summary>조기 반환</summary>
  
```c++
#include <iostream>

using namespace std;

// 주어진 수량과 가격에 따라 총 가격을 계산하는 함수
double total_price(int quantity, double price) {
  double total = quantity * price; // total 계산
  if (total > 100) { // total이 100보다 크면
    return total * 0.9; // 조기 반환
  }

  return total;
}
...생략...(수많은 작업들)
int main() {
  cout << total_price(4, 50) << endl;
  return 0;
}
```
- 코드 실행 과정이 함수 끝까지 도달하기 전에 반환

</details>

<details>
<summary>보호 구문</summary>
  
```c++
#include <iostream>
#include <vector>

using namespace std

// 벡터의 값을 모두 더해서 N으로 나눈 값을 반환하는 함수
double get_avg(const vector<int>& arr, int N) {
  // 벡터가 비어 있는 경우
  if (arr.empty()) {
    return -1;
}

// N이 0인 경우
if (N == 0) {
  return -1;
}
  int sum = 0;
  for (int num : arr) {
    sum += num;
  }

  return sum / N;
}
```
- 본격적인 로직 진행 전 예외 처리 코드 추가

</details>

<details>
<summary>입출력</summary>

- `iostream` : 입출력 담당 라이브러리 **cin, cout 등**

- C에서 사용하던 `scanf()`, `printf()`를 사용하는 것이 더 효율적임
    - endl을 사용하면 출력 버퍼를 비우는 시간까지 소요되므로
- c의 입출력 사용을 위해서는 **<stdio.h> or <cstdio> 헤더 추가**

</details>

<details>
<summary>초기화 함수</summary>

- 배열 내의 모든 값을 동일하게 초기화

- `fill(시작 iterator, 끝 iterator, 초기화 값)`

```c++
int a[10][10];
int b[8][8];

fill(&a[0][0], &a[0][0] + 10 * 10, 2);
fill(&b[0][0], &b[7][8], 100);
```

- `memset(배열 이름, 0 or -1, 배열 사이즈)`

```c++
int a[10];
int a2[10][10];

memset(a, -1, sizeof(a));
memset(a2, 0, sizeof(a2));
```

</details>
