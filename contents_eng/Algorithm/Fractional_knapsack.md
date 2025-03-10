# Fractional Knapsack

---
### 문제 상황
- 크기가 w인 가방과 n개의 물건을 가지고 있으며, 각 물건은 하나씩 존재함
- 각 물건 i는 크기 wi와 가치 vi를 가짐
- 이 가방에 물건을 담으려 할 때, 가방에 담을 수 있는 물건들의 가치의 합이 최대가 되도록 하려면 어떤 물건들을 선택해야하는가?

&rarr; 문제 상황은 0/1 knapsack과 같지만 물건을 이진선택 하는 것이 아니라, **물건의 일부도 넣을 수 있음**

### 해결 방법
- ***(가치 / 무게)의 비율이 높은 순으로 넣어줌***
- 만약 물품의 무게가 무게의 최대치보다 크면 (물품의 비율) * (최대치까지 남은 무게)를 구해 답에 더함

1. 가치 / 무게의 비율을 구함
2. V / W가 높은 것부터 차례대로 가방에 넣음

&rarr; 최적화 문제이므로 눈 앞에 있는 최대 이익을 locally optimal하게 고르는 greedy 알고리즘을 이용 (항상 optimal 보장은 X)

### 구현
```python
def fractional_knapsack(capacity, items):
    # 가치 대비 무게 비율을 기준으로 정렬 (내림차순)
    items.sort(key=lambda x: x[1] / x[0], reverse=True)

    total_value = 0.0  # 배낭에 담은 총 가치
    for weight, value in items:
        if capacity >= weight:  # 전체 아이템을 담을 수 있으면 전부 담기
            capacity -= weight
            total_value += value
        else:  # 일부만 담아야 하는 경우
            total_value += value * (capacity / weight)
            break  # 배낭이 꽉 차면 종료

    return total_value

items = [(10, 60), (20, 100), (30, 120)]  # (무게, 가치)
capacity = 50
print("최대 가치:", fractional_knapsack(capacity, items))
```

```c++
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Item {
    double weight, value;
};

// 비교 함수 (가치 대비 무게 비율 기준 정렬)
bool cmp(Item a, Item b) {
    return (a.value / a.weight) > (b.value / b.weight);
}

double fractionalKnapsack(int capacity, vector<Item>& items) {
    sort(items.begin(), items.end(), cmp);  // 내림차순 정렬

    double totalValue = 0.0;
    for (auto& item : items) {
        if (capacity >= item.weight) {  // 전체 아이템을 담을 수 있으면 전부 담기
            capacity -= item.weight;
            totalValue += item.value;
        } else {  // 일부만 담아야 하는 경우
            totalValue += item.value * (capacity / item.weight);
            break;
        }
    }
    return totalValue;
}

int main() {
    vector<Item> items = {{10, 60}, {20, 100}, {30, 120}};
    int capacity = 50;

    cout << "최대 가치: " << fractionalKnapsack(capacity, items) << endl;
    return 0;
}
```
