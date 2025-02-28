import sys

input = sys.stdin.readline

def bellman_ford(start):
    weights[start] = 0
    for i in range(V):
        for src, dst, weight in graph:
            W = weights[src] + weight
            if weights[src] != INF and weights[dst] > W:
                weights[dst] = W
                if i == V -1:
                    return False # negative cycle exists
    return True # there is no cycle

V, E = map(int, input().split())
graph = []
for _ in range(E):
    src, dst, weight = map(int, input().split())
    graph.append([src, dst, weight])

INF = float('inf')
weights = [INF] * (V+1)

if bellman_ford(1): # 출발 노드를 인자 값으로 넣어줄 것
    for i in range(2, V+1): # 출발 노드인 1을 제외하고 다른 모든 노드로 가기 위한 최단 거리 출력
        print (weights[i], end = ' ')
else:
    print ("There is negative cycle.") # 음의 사이클이 존재할 경우