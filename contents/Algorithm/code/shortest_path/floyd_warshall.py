import sys

input = sys.stdin.readline

V, E = map(int, input().split())
INF = float('inf')
graph = [[INF] * (V+1) for _ in range(V+1)]

for _ in range(E):
    src, dst, weight = map(int, input().split())
    graph[src][dst] = weight

for k in range(1, V+1): # via
    graph[k][k] = 0
    for i in range(1, V+1): # src
        for j in range(1, V+1): # dst
            graph[i][j] = min(graph[i][j], graph[i][k]+graph[k][j])

for i in range(1, V+1):
    for j in range(1, V+1):
        print (graph[i][j], end= ' ')
    print()