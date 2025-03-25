# Python

---
## 자주 사용하는 메서드

<details>
<summary>Table of Contents</summary>

- [Built-in Functions](#1-내장-함수-built-in-functions)
- [Itertools](#2-itertools-반복-가능한-데이터-처리-라이브러리)
- [Heapq](#3-heapq-힙-자료구조)
- [Bisect](#4-bisect-이진-탐색)
- [Collections](#5-collections-유용한-자료구조-제공)
- [Math](#6-math)
- [Set](#7-set-집합)
- [Dictionary](#8-dictionary)
- [List](#9-list)
- [Bit operation](#10-비트-연산)
- [List application](#11-리스트-변형)
- [Re](#12-re-모듈-정규-표현식)
- [Match](#13-match)
- [Decimal](#14-진법-변환)
- [Input](#15-입력-받기)
- [Output](#16-출력-하기)
- [Deepcopy](#17-깊은-복사)

</details>

### 1. 내장 함수 (Built-in Functions)

#### 1.1 기본 함수
- ***sum(iterable)*** : iterable 객체 (리스트, 튜플 등)의 모든 원소 합 반환
```python
result = sum([1,2,3,4,5])
print(result) # >>> 15
```

- ***min(a, b, c ...)*** : 가장 작은 값 반환
```python
result = min(7,3,5,2)
print(result) # >>> 2
```

- ***max(a, b, c ...)*** : 가장 큰 값 반환
```python
result = max(7,3,5,2)
print(result) # >>> 7
```

- ***abs(x)*** : 절댓값 반환
```python
print(abs(-7)) # >>> 7
```

- ***round(x, n)*** : 반올림 (소수점 n자리까지)
```python
print(round(3.14159, 2)) # >>> 3.14
```
  
- ***divmod(a, b)*** : (몫, 나머지) 반환
```python
print(divmod(10, 3)) # >>> (3, 1)
```

- ***eval(expression)*** : 문자열 형식의 수식을 계산한 결과 반환
```python
result = eval("(3 + 5) * 7")
print(result) # >>> 56
```

- ***pow(x, y, mod)*** : x의 y 제곱 반환 (mod는 선택)
```python
print(pow(2, 3))  # >>> 8
print(pow(2, 3, 5))  # >>> 3 (2^3 % 5)
```

- ***any(iterable)*** : 하나라도 참이면 True
- ***all(iterable)*** : 모두 참이면 True
```python
print(any([0, 1, 0]))  # >>> True
print(all([0, 1, 0]))  # >>> False
print(all([1, 1, 1]))  # >>> True
```

#### 1.2 정렬 함수
- ***sorted(iterable, key, reverse)*** : 정렬된 결과 반환 (원본 변경 없음)
```python
result = sorted([9,1,8,5,4])
print(result) # >>> [1,4,5,8,9]

result = sorted([('홍길동', 35), ('이순신', 75), ('아무개', 50)], key=lambda x: x[1], reverse=True)
print(result)  # >>> [('이순신', 75), ('아무개', 50), ('홍길동', 35)]
```

- ***sort()*** : 리스트 객체 내부 값을 정렬 (원본 변경됨)
```python
data = [9,1,8,5,4]
data.sort()
print(data) # >>> [1,4,5,8,9]
```

#### 1.3 문자열 처리 함수
- ***str.upper()*** : 대문자로 변환
- ***str.lower()*** : 소문자로 변환
- ***str.isupper() / str.islower()*** : 대문자/소문자인지 확인
- ***str.swapcase()*** : 소문자는 대문자, 대문자는 소문자로 바꿈
- ***str.capitalize()*** : 첫문자만 대문자로 변경하고 나머지 문자열은 모두 소문자로 변환
- ***str.title()*** : 각 단어의 앞 문자를 대문자로 변경하고 다른 문자들은 소문자로 변환

- ***str.isdigit()*** : 숫자로만 구성된 문자열인지 확인

- ***str.startswith(prefix) / str.endswith(suffix)*** : 접두사/접미사 확인

- ***str.find(substring, start, end)*** : 특정 문자 위치 찾기 (없으면 -1 반환), 문자가 여러개이면 처음 찾은 인덱스 반환
- ***str.rfind(substring, start, end)*** : 특정 문자 위치 찾기 (없으면 -1 반환), **문자가 여러개이면 맨 마지막 인덱스 반환**

- ***str.zfill(width)*** : 0으로 길이 채우기
- ***str.rjust(width, fillchar)*** : 지정 문자로 길이 채우기 (오른쪽부터)
- ***str.ljust(width, fillchar)*** : 지정 문자로 길이 채우기 (왼쪽부터) 

- ***str.count(substring, start, end)*** : 문자열 내부에서 특정 문자가 등장하는 횟수

- ***str.lstrip()*** : 기존 문자열에 있는 왼쪽 공백을 제거한 문자열 반환
- ***str.rstrip()*** : 기존 문자열에 있는 오른쪽 공백을 제거한 문자열 반환
- ***str.strip()*** : 기존 문자열의 양쪽 공백을 제거한 문자열 반환

- ***str.replace(old, new, count)*** : 기존 문자에 있는 old를 new로 변경해 반환, count 지정을 하는 경우 일부만 변경

- ***str.join()*** : 리스트 요소를 문자열로 합칠 때 사용

- ***ord(c) / chr(n)*** : 문자 &rarr; 아스키코드 변환 / 아스키코드 &rarr; 문자 변환

- ***isalpha() / isalnum()*** : 문자(알파벳)인지 확인 / 문자 + 숫자로 구성된 문자열인지 확인

```python
text = "hello World"
print(text.upper())        # >>> HELLO WORLD
print(text.lower())        # >>> hello world
print(text.isupper())      # >>> False
print(text.swapcase())     # >>> HELLO wORLD
print(text.capitalize())   # >>> Hello world
print(text.title())        # >>> Hello World

print("12345".isdigit())   # >>> True
print("Python".startswith("Py"))  # >>> True

s = "blockdmask"
print(s.find('k')) # >>> 4
print(s.rfind('k')) # >>> 9
print(s.find('k', 3, 6)) # >>> 4

print("hello".zfill(10))   # >>> 00000hello
print("hello".rjust(10, o)) # >>> helloooooo
print("hello".ljust(10, h)) # >>> hhhhhhello

print(s.count('k')) # >>> 2
print(s.count('k', 3, 6)) # >>> 1

t = " Hi my Name is "
print(t.lstrip()) # >>> "Hi my Name is "
print(t.rstrip()) # >>> " Hi my Name is"
print(t.strip()) # >>> "Hi my Name is"

print(s.replace('k', 'o')) # >>> "blocodmaso"
print(s.replace('k', 'o', 1)) # >>> "blocodmask"

w = ['Hello', 'World']
print(' '.join(w)) # >>> "Hello World"

print(ord('A')) # >>> 65
print(chr(65))  # >>> 'A'

print("hello".isalpha())   # >>> True
print("hello123".isalpha())   # >>> False
print("hello123".isalnum())   # >>> True
```

---
### 2. itertools (반복 가능한 데이터 처리 라이브러리)
#### 2.1 순열 (permutations)
- 주어진 리스트에서 r개의 데이터를 선택해 나열하는 모든 경우의 수
```python
from itertools import permutations

data = ['A', 'B', 'C']
result = list(permutations(data, 2))
print(result)  # >>> [('A', 'B'), ('A', 'C'), ('B', 'A'), ('B', 'C'), ('C', 'A'), ('C', 'B')]
```

#### 2.2 조합 (combinations)
- 주어진 리스트에서 r개의 데이터를 선택하는 모든 경우의 수 (순서 고려 X)
```python
from itertools import combinations

result = list(combinations(data, 2))
print(result)  # >>> [('A', 'B'), ('A', 'C'), ('B', 'C')]
```

#### 2.3 중복 순열 (product)
- 중복을 허용한 순열
```python
from itertools import product

result = list(product(data, repeat=2))
print(result)  # >>> [('A', 'A'), ('A', 'B'), ('A', 'C'), ('B', 'A'), ('B', 'B'), ('B', 'C'), ('C', 'A'), ('C', 'B'), ('C', 'C')]
```

#### 2.4 중복 조합 (combinations_with_replacement)
- 중복을 허용한 조합
```python
from itertools import combinations_with_replacement

result = list(combinations_with_replacement(data, 2))
print(result)  # >>> [('A', 'A'), ('A', 'B'), ('A', 'C'), ('B', 'B'), ('B', 'C'), ('C', 'C')]
```

#### 2.5 map(function, iterable)
- 모든 요소에 함수 적용

#### 2.6 filter(function, iterable)
- 조건에 맞는 요소만 반환

#### 2.7 lambda
- 익명 함수 (한줄로 표현)

```python
nums = [1, 2, 3, 4]

squared = list(map(lambda x: x**2, nums))  # [1, 4, 9, 16]

even_nums = list(filter(lambda x: x % 2 == 0, nums))  # [2, 4]
```

- ***lambda로 숫자 나누기***
```python
n_score = list(map(lambda x: x / m * 100, score))
```

#### 2.8 enumerate()
- 리스트 요소와 인덱스를 함께 반환
```python
data = ['a', 'b', 'c']
for i, val in enumerate(data):
    print(i, val)
# >>> 0 a
# >>> 1 b
# >>> 2 c
```

#### 2.9 zip()
- 여러 리스트를 병렬로 묶어서 반환
```python
a = [1, 2, 3]
b = ['one', 'two', 'three']
for num, word in zip(a, b):
    print(num, word)
# >>> 1 one
# >>> 2 two
# >>> 3 three
```

#### 2.10 range()
- range(start, stop, step) : 숫자 범위 생성
```python
print(list(range(5)))  # >>> [0, 1, 2, 3, 4]
print(list(range(1, 10, 2)))  # >>> [1, 3, 5, 7, 9]
```

---
### 3. heapq (힙 자료구조)
- heap 기능 제공, 우선순위 큐 구현 가능
- python의 겨우 **최소 힙**을 기본적으로 사용

- ***heapq.heappush()*** : 힙에 원소 삽입
- ***heapq.heappop()*** : 힙에서 원소 꺼내기

#### 3.1 힙 정렬
```python
import heapq

def heapsort(iterable):
    h = []
    result = []
    
    for value in iterable:
        heapq.heappush(h, value)
    
    for i in range(len(h)):
        result.append(heapq.heappop(h))
    
    return result

result = heapsort([5, 3, 8, 1, 2])
print(result)  # >>> [1, 2, 3, 5, 8]
```

#### 3.2 최대 힙 (내림차순)
```python
def max_heapsort(iterable):
    h = []
    result = []
    
    for value in iterable:
        heapq.heappush(h, -value)
    
    for i in range(len(h)):
        result.append(-heapq.heappop(h))
    
    return result

result = max_heapsort([5, 3, 8, 1, 2])
print(result)  # >>> [8, 5, 3, 2, 1]
```

---
### 4. bisect (이진 탐색)
- ***bisect_left(iterable, value)*** : 정렬된 순서를 유지하며 리스트에 value를 삽입할 가장 왼쪽 인덱스 구하기
- ***bisect_right(iterable, value)*** : 정렬된 순서를 유지하며 리스트에 value를 삽입할 가장 오른쪽 인덱스 구하기

#### 4.1 특정 값의 삽입 위치 찾기
```python
from bisect import bisect_left, bisect_right

a = [1, 2, 4, 4, 8]
x = 4

print(bisect_left(a, x))  # >>> 2
print(bisect_right(a, x))  # >>> 4
```

#### 4.2 특정 범위에 속하는 원소 개수 찾기
```python
def count_by_range(a, left, right):
    return bisect_right(a, right) - bisect_left(a, left)

a = [1, 2, 3, 3, 3, 4, 4, 8, 9]
print(count_by_range(a, 3, 4)) # >>> 5
```

---
### 5. collections (유용한 자료구조 제공)
#### 5.1 deque
- 리스트와 다르게 인덱싱, 슬라이싱 등의 기능은 사용 불가 / 보통 python에서는 deque를 사용해 큐 구현
- 연속적으로 나열된 데이터의 시작 또는 끝 부분에 데이터 삽입 or 삭제 시에 효과적
- ***popleft()*** : 첫번째 원소 제거
- ***pop()*** : 마지막 원소 제거
- ***appendleft(x)*** : 첫번째 인덱스에 원소 x를 삽입
- ***append(x)*** : 마지막 인덱스에 원소 x를 삽입
```python
from collections import deque

data = deque([2, 3, 4])
data.appendleft(1)
data.append(5)

print(list(data)) # >>> [1, 2, 3, 4, 5]
```

#### 5.2 Counter (빈도수 계산)
- 리스트와 같은 iterable 객체가 주어졌을 때, 해당 객체 내부의 원소가 몇번 등장했는지 알려줌
```python
from collections import Counter

counter = Counter(['red', 'blue', 'red', 'green', 'blue', 'blue'])
print(dict(counter)) # >>> {'red': 2, 'blue': 3, 'green': 1}
```

---
### 6. math
- ***factorial(x)*** : x! 값 반환
```python
import math
print(math.factorial(5)) # >>> 120
```

- ***sqrt(x)*** : x의 제곱근 반환
```python
print(math.sqrt(7)) # >>> 2.6457
```

- ***gcd(a, b)*** : a & b의 최대공약수 반환
```python
print(math.gcd(21, 14)) # >>> 7
```

- ***lcm(a, b)*** : a & b의 최소공배수 반환
```python
print(math.lcm(3, 7)) # >>> 21
```

- ***pi, 자연상수 e***
```python
print(math.pi)  # >>> 3.141592653589793
print(math.e)   # >>> 2.718281828459045
```

- ***ceil(x)*** : 올림
```python
print(math.ceil(4.2))   # >>> 5
```

- ***floor(x)*** : 내림
```python
print(math.floor(4.9))  # >>> 4
```

- ***trunc(x)*** : 소수점 버림
```python
print(math.trunc(4.9))  # >>> 4
```

---
### 7. Set (집합)
- ***add(x) / remove(x)*** : 집합에 요소 추가 / 요소 제거 (없으면 오류 발생)
```python
s = {1, 2, 3}

s.add(4)  # {1, 2, 3, 4}
s.remove(2)  # {1, 3, 4}
```

- ***difference(set)*** : 차집합 (A-B)
- ***intersection(set)*** : 교집합 (A ∩ B)
- ***union(set)*** : 합집합 (A ∪ B)

```python
a = {1, 2, 3, 4}
b = {3, 4, 5, 6}

print(a.difference(b))  # >>> {1, 2}
print(a.intersection(b))  # >>> {3, 4}
print(a.union(b))  # >>> {1, 2, 3, 4, 5, 6}
```

- ***중복 제거*** : 리스트를 집합으로 변환해 중복 제거 가능
```python
nums = [1, 2, 2, 3, 4, 4, 5]
unique_nums = list(set(nums))  # [1, 2, 3, 4, 5]
```

---
### 8. Dictionary
- ***get(key, default)*** : 키가 없으면 기본값 반환

- ***keys()*** : 키 목록

- ***values()*** : 값 목록

- ***items()*** : (키, 값) 쌍 목록

```python
d = {'name': 'Alice', 'age': 25}

print(d.get('name'))  # >>> Alice
print(d.get('gender', 'Unknown'))  # >>> Unknown
print(list(d.keys()))  # >>> ['name', 'age']
print(list(d.values()))  # >>> ['Alice', 25]
print(list(d.items()))  # >>> [('name', 'Alice'), ('age', 25)]
```

- ***defaultdict()*** : key가 존재하지 않는 경우 자동으로 키를 생성하여 연산 수행 &rarr; 에러 X
```python
from collections import defaultdict
dic = defaultdict(list)

N = int(input())

for i in range(N):
    deadline, cup = map(int, input().split())
    dic[deadline].append(cup)
```

--- 
### 9. List
- ***list.append(n)*** : list에 원소 추가
- ***list.remove(n)*** : list의 원소 제거
- ***del list[index]*** : 제거하고 싶은 리스트 원소의 인덱스를 작성해 제거
- ***list.index(n)*** : list 원소의 인덱스 반환
- ***list.reverse()*** : list의 원소 뒤집기
- ***list 반복하기 &rarr; range() 이용*** : 리스트의 길이만큼 반복
```python
for i in range(len(arr)):
	print(i)
```

---
### 10. 비트 연산
```python
a, b = 5, 3  # (5: 101, 3: 011)

print(a & b)  # >>> 1  (AND)
print(a | b)  # >>> 7  (OR)
print(a ^ b)  # >>> 6  (XOR)
print(a << 1)  # >>> 10 (왼쪽 시프트)
print(a >> 1)  # >>> 2  (오른쪽 시프트)
```

---
### 11. 리스트 변형
#### 11.1 2차원 리스트 90도 회전
```python
matrix = [[1, 2, 3], [4, 5, 6], [7, 8, 9]]
rotated = list(zip(*matrix[::-1]))
print(rotated)  
# >>> [(7, 4, 1), (8, 5, 2), (9, 6, 3)]
```

#### 11.2 deque 회전 
```python
from collections import deque

dq = deque([1, 2, 3, 4, 5])
dq.rotate(2)  # 오른쪽으로 2칸 회전
print(list(dq))  # >>> [4, 5, 1, 2, 3]
```

--- 
### 12. re 모듈 (정규 표현식)
- ***re.search(pattern, string)*** : 문자열 어디서든 패턴과 처음 일치하는 부분을 찾음
```python
import re

text = "My number is 12345 and yours is 67890."
match = re.search(r'\d+', text)

print(match.group())  # >>> '12345' (처음 매칭된 숫자)
```

- ***re.findall(pattern, string)*** : 문자열에서 패턴과 일치하는 모들 결과를 리스트로 반환
```python
text = "My number is 12345 and yours is 67890."
print(re.findall(r'\d+', text))  
# >>> ['12345', '67890']
```

- ***re.finditer(pattern, string)*** : 매칭된 부분을 Match 객체로 반환 / iterator를 반환해 for문에서 사용 가능
```python
matches = re.finditer(r'\d+', text)

for match in matches:
    print(match.group(), match.span())  
# >>> 12345 (14, 19)
# >>> 67890 (32, 37)
```

- ***re.fullmatch(pattern, string)*** : 문자열 전체가 패턴과 일치해야 매칭됨
```python
print(re.fullmatch(r'\d+', "12345"))  # >>> <re.Match object>
print(re.fullmatch(r'\d+', "123abc"))  # >>> None
```

- ***re.split(pattern, string)*** : 패턴을 기준으로 문자열을 분할해 리스트로 반환
```python
text = "apple, banana; orange|grape"
print(re.split(r'[,;|]', text))  
# >>> ['apple', ' banana', ' orange', 'grape']
```

- ***re.sub(pattern, replacement, string, count=0)*** : 패턴과 일치하는 부부 교체
```python
text = "Hello 123, welcome to 456"
print(re.sub(r'\d+', "###", text))  
# >>> 'Hello ###, welcome to ###'
```

- ***re.subn(pattern, replacement, string, count=0)*** : re.sub()과 동일하지만 (새 문자열, 교체 횟수) 튜플 반환
```python
result = re.subn(r'\d+', "###", text)
print(result)  
# >>> ('Hello ###, welcome to ###', 2)
```

- ***re.compile(pattern)*** : 정규표현식을 미리 컴파일 해 여러번 사용할 때 성능 향상
```python
pattern = re.compile(r'\d+')
print(pattern.findall(text))  
# >>> ['123', '456']
```

- ***re.purge()*** : 캐시된 정규 표현식 패턴 모두 제거
```python
re.purge()
```

- ***re.escape(string)*** : 특수 문자가 포함된 문자열을 자동으로 이스케이프 처리
```python
print(re.escape("www.example.com?query=hello+world"))
# >>> 'www\\.example\\.com\\?query=hello\\+world'
```

---
### 13. Match
- ***group()*** : 매칭된 문자열 반환
- ***start()*** : 매칭된 문자열의 시작 인덱스 반환
- ***end()*** : 매칭된 문자열의 끝 인덱스 반환
- ***span()*** : (시작, 끝) 튜플 반환
- ***groups()*** : 그룹핑된 전체 튜플 반환
- ***group(n)*** : n번째 그룹 반환
- ***groupdict()*** : 이름이 있는 그룹을 딕셔너리로 반환

```python
match = re.search(r'(\d+)-(\d+)', "Order 123-456 received")

print(match.group())   # >>> '123-456'
print(match.start())   # >>> 6
print(match.end())     # >>> 13
print(match.span())    # >>> (6, 13)
print(match.groups())  # >>> ('123', '456')
print(match.group(1))  # >>> '123'
print(match.group(2))  # >>> '456'

pattern = r'(?P<first>\d+)-(?P<second>\d+)'
match = re.search(pattern, "Order 123-456 received")

print(match.groupdict())  
# >>> {'first': '123', 'second': '456'}
```

---
### 14. 진법 변환
- ***n진수 &rarr; 10진수*** : **int(string, base) 내장 함수 지원**

```python
print(int('1010', 2))  # >>> 10
print(int('A', 16))  # >>> 10
```

- ***int() 내장함수를 사용하지 않고 n진수를 10진수로 변환하는 방법***
1. n진수의 순서를 반대로 만듦
2. n의 제곱 차수를 늘려가며 곱함
3. 누적함
```python
def convert(n, base):
    decimal = 0
    for index, value in enumerate(str(n)[::-1]):
        decimal += (3**index)*int(value)
    return decimal

print(convert(21, 3))
```

- ***10진수 &rarr; 2,8,16 진수*** : **bin(), oct(), hex() 내장 함수 지원**
```python
print(bin(10))
print(oct(10))
print(hex(10))

# Ob1010
# Oo12
# Oxa
# Ob: 2진수, Oo: 8진수, Ox: 16진수

# 앞의 진법 표시를 지우는 방법은 [2:]를 하면 가능
print(bin(10)[2:])
print(oct(10)[2:])
print(hex(10)[2:])

# 1010
# 12
# a
```

- ***10진수 &rarr; n진수*** (2진수-16진수)
```python
import string

# temp = 0123456789abcdefghijklmnopqrstuvwxyz
temp = string.digits+string.ascii_lowercase

def convert(num, base):
    q, r = divmod(num, base)
    if q == 0:
        return temp[r]
    else:
        return convert(q, base) + temp[r]

print(convert(10, 2))
print(convert(10, 2))
print(convert(10, 2))
print(convert(10, 2))

# 1010
# 101
# 22
# 20
```

- ***n진수 &rarrr; n진수***
```python
import string

temp = string.digits+string.ascii_lowercase
def convert(num, base):
    q, r = divmod(num, base)
    if q == 0:
        return temp[r]
    else:
        return convert(q, base) + temp[r]

print(convert(int('a', 16), 2))
print(convert(int('4', 5), 3))
print(convert(int('2', 3), 4))
print(convert(int('11', 2), 5))

# 1010
# 11
# 2
# 3
```

---
### 15. 입력 받기
- ****입력 속도 최적화 &rarr; sys 모듈 사용***
```python
import sys
input = sys.stdin.readline  # 빠른 입력

list.append(int(sys.stdin.readline()))

num1 = set(sys.stdin.readline().split())
```

- ***정수 입력 받기***
- input()은 기본적으로 문자열로 입력을 받음
```python
n = int(input())
```

- ***리스트 입력 받기***
```python
a = input().split()
```

- ***정수 리스트 입력 받아서 나누기***
```python
a, b = map(int, input().split())
```

- ***한 줄에 여러 정수 or 실수 입력받기***
```python
temp_list = list(map(int, input().split()))
print(temp_list)
```

- ***특정 값으로 2차원 맵 생성 &rarr; BFS, DFS 등에 주로 사용***
```python
visited = [[False for _ in range(m)] for _ in range(n)] # n: 행 개수 m: 열 개수
```

---
### 16. 출력 하기
- ***리스트 언패킹해서 출력하기***
```python
print(*list)
```

- ***end 매개 변수***
```python
print("Hello", end=", ")
print("World")
# 출력: "Hello, World"
```

- ***sep 매개 변수***
```python
print("apple", "banana", "cherry", sep=", ")
# 출력: "apple, banana, cherry"
```

- ***sorted와 key 이용하기***
```python
return sorted(strings, key=lambda x: (x[n], x))
```

- ***sort와 key 이용하기***
```python
letters.sort(key=lambda x: (x.split()[1:], x.split()[0]))
```

- ***map과 key 이용하기***
```python
max_item = max(my_list, key=lambda x: x[1])
```

- ***min과 key 이용하기***
```python
min_item = min(my_list, key=lambda x: x[0])
```

- ***tuple을 반환하는 lambda***
```python
return sorted(strings, key=lambda x: (x[n], x))
```

---
### 17. 깊은 복사
- [:]로 서로 다른 메모리 주소를 가지게 된다 &rarr; 1차원 리스트는 괜찮지만 2차원 리스트에는 큰 문제가 발생함
- [:] 연산의 경우 1차원은 깊은 복사하지만, 내부 배열은 참조를 유지함 &rarr; 내부 리스트의 원소를 복사한 곳에서 변경하면 원본 리스트에도 영향을 미침
- 이 때문에 deepcopy()를 사용함 &rarr; 리스트의 모든 차원을 새로운 메모리 위치에 복사해 독립적인 복사본을 가짐
```python
import copy

# 2차원 배열 생성
original = [[1, 2, 3], [4, 5, 6], [7, 8, 9]]

# 얕은 복사
shallow_copied = original[:]
shallow_copied[0][0] = 999
print("얕은 복사 후 원본 배열:", original)  # 변경됨!

# 깊은 복사
deep_copied = copy.deepcopy(original)
deep_copied[0][0] = 111
print("깊은 복사 후 원본 배열:", original)  # 변경되지 않음!
print("깊은 복사된 배열:", deep_copied)

# 얕은 복사 후 원본 배열: [[999, 2, 3], [4, 5, 6], [7, 8, 9]]
# 깊은 복사 후 원본 배열: [[1, 2, 3], [4, 5, 6], [7, 8, 9]]
# 깊은 복사된 배열: [[111, 2, 3], [4, 5, 6], [7, 8, 9]]
```
