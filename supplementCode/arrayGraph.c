#include <stdio.h>
#include <stdlib.h>

#define elem char

// #define expressGraph
// #define graphTraversal
#define directedGraph

typedef enum __Label
{
  Fresh,
  Visited
} Label;

typedef struct __Vertex
{
  elem name;
  int degree;
  Label label;
} Vertex;

typedef struct __Graph
{
  Vertex *vertices; // 정점 배열 (name, degree, label)
  int **edges;      // 간선 배열 (w)
} Graph;

// 전역변수
Graph graph;
int n, m;
int *topOrder;

void initGraph();
void updateEdge(elem v1, elem v2, int w);
int findIdx(elem name);
void print(elem name);

void rDFS(elem name);
void BFS(elem name);

void topologicalSort();
int main()
{
  printf("input n, m :");
  scanf("%d %d", &n, &m);
  getchar();

  initGraph(graph, n, m);
  printf("Graph setted\n");

// 그래프 표현
#ifdef expressGraph
  char cmd;
  elem name, v1, v2;
  int w;

  while (1)
  {
    scanf("%c", &cmd);
    if (cmd == 'a')
    {
      scanf("%d", &name);
      print(name);
    }
    else if (cmd == 'm')
    {
      scanf("%d %d %d", &v1, &v2, &w);
      updateEdge(v1, v2, w);
    }
    else if (cmd == 'q')
      break;
  }
#endif

// 그래프 순회
#ifdef graphTraversal
  int start;
  printf("Start : ");
  scanf("%d", &start);
  // printf("rDFS\n");
  // rDFS(start);
  printf("BFS\n");
  BFS(start);
#endif

// 방향 그래프
#ifdef directedGraph
  topologicalSort();

  if (topOrder[0] == 0)
    printf("0\n");
  else
  {
    for (int i = 1; i <= n; i++)
      printf(" %c", graph.vertices[topOrder[i]].name);
    printf("\n");
  }
#endif

  return 0;
}

/// @brief 정점과 간선 수를 입력 받아 초기화
/// @param graph
/// @param n 정점 수
/// @param m 간선 수
void initGraph()
{
  elem name, v1, v2;

  Vertex *Varr = graph.vertices = (Vertex *)calloc(n + 1, sizeof(Vertex));
  int **Earr = graph.edges = (int **)calloc(n + 1, sizeof(int *));

  for (int i = 0; i < n + 1; i++)
  {
    Earr[i] = (int *)calloc(m + 1, sizeof(int));
  }
  printf("input Vertex\n");
  // 정점 넣기
  for (int i = 1; i < n + 1; i++)
  {
    scanf("%c", &name);
    getchar();
    Varr[i].name = name;
  }
  printf("input Edge\n");
  // 간선 넣기
  for (int i = 0; i < m; i++)
  {
    int w = 1;
    scanf("%c %c", &v1, &v2);
    getchar();
    updateEdge(v1, v2, w);
    Varr[findIdx(v2)].degree++;
  }
}

void updateEdge(elem v1, elem v2, int w)
{
  int v1Idx = findIdx(v1);
  int v2Idx = findIdx(v2);
  graph.edges[v1Idx][v2Idx] = w;
  graph.edges[v2Idx][v1Idx] = w;
}

int findIdx(elem name)
{
  for (int i = 1; i < n + 1; i++)
  {
    if (graph.vertices[i].name == name)
      return i;
  }
  return 0;
}

void print(elem name)
{
  int vIdx = findIdx(name);
  if (vIdx == 0)
  {
    printf("-1\n");
    return;
  }

  for (int i = 1; i < n + 1; i++)
  {
    if (graph.edges[vIdx][i] != 0)
      printf(" %d %d", graph.vertices[i].name, graph.edges[vIdx][i]);
  }
  printf("\n");
}

void rDFS(elem name)
{
  Vertex *Varr = graph.vertices;
  int **Earr = graph.edges;
  int vIdx = findIdx(name);

  printf("%d\n", name);
  Varr[vIdx].label = Visited;

  for (int i = 1; i < n + 1; i++)
  {
    if (Earr[vIdx][i] != 0 && Varr[i].label == Fresh)
    {
      rDFS(Varr[i].name);
    }
  }
}

void BFS(elem name)
{
  Vertex *Varr = graph.vertices;
  int **Earr = graph.edges;
  // 정점의 idx가 들어가는 배열
  int *L = (int *)calloc(n, sizeof(int));
  int idx = 0, top = 1;
  int vIdx = findIdx(name);
  L[idx] = vIdx;
  Varr[vIdx].label = Visited;

  for (; L[idx] != 0; idx++)
  {
    vIdx = L[idx];
    printf("%d\n", Varr[vIdx].name);
    for (int j = 1; j < n + 1; j++)
    {
      if (Earr[vIdx][j] != 0 && Varr[j].label == Fresh)
      {
        Varr[j].label = Visited;
        L[top++] = j;
      }
    }
  }
}

void topologicalSort()
{
  int *Q = (int *)calloc(n + 1, sizeof(int));
  Vertex *Varr = graph.vertices;
  int **Earr = graph.edges;

  int rear = 0, head = 0, top = 1;
  topOrder = (int *)calloc(n, sizeof(int));

  for (int i = 1; i < n + 1; i++)
  {
    if (Varr[i].degree == 0)
      Q[rear++] = i;
  }
  while (head != rear)
  {
    int vIdx = Q[head++];
    topOrder[top++] = vIdx;
    for (int i = 1; i < n + 1; i++)
    {
      if (Earr[vIdx][i] != 0)
      {
        Varr[i].degree--;
        if (Varr[i].degree == 0)
          Q[rear++] = i;
      }
    }
  }
  if (top <= n)
    topOrder[0] = 0;
  else
    topOrder[0] = -1;
}