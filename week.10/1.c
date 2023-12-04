// 인접리스트 구조

#include <stdio.h>
#include <stdlib.h>

/* 그래프 상세 구현 과정

1. 그래프를 다음 필드로 구성되는 구조체로 정의
- vertices : 정점 레코드의 배열 [0:n-1]
- edges : 간선 레코드의 배열 [0:n-1]

2. 정점을 다음 필드로 구성되는 레코드로 정의
- name : 식별자

3. 간선을 다음 필드로 구성되는 레코드로 정의
- name : 식별자
- endpoints : 정점 인덱스 1, 정점 인덱스 2의 집합

4-1 (인접리스트의 경우) : 정점 레코드에 다음 필드를 추가한다.
- incidentEdges : 간선 인덱스의 헤더연결리스트 (작업 효율을 위해 헤더 노드를 추가)
4-2 (인접행렬의 경우) : 그래프 레코드에 다음 필드를 추가한다.
- adjacencyMatrix : 간선 인덱스의 2D 배열 (간선이 존재하지 않으면 -1 을 저장함)

*/

// 정점 리스트
typedef struct __Vertices
{
  int name;
  struct __Vertices *next;       // 모든 정점과 연결
  struct __Incidence *incidence; // 부착 리스트를 통해 해당 노드의 간선에 대한 정보 저장
} Vertices;

// 부착 리스트 (각 정점의 부착 간선을 간선 노드에 대한 참조들의 리스트)
typedef struct __Incidence
{
  struct __Edge *edge;
  struct __Incidence *next; // 해당 정점에 들어있는 간선만 연결
} Incidence;

// 간선 리스트
typedef struct __Edge
{
  int weight;
  struct __Vertices *v1;
  struct __Vertices *v2;
  struct __Edge *next; // 모든 간선과 연결
} Edge;

typedef struct __Graph
{
  Vertices *head;
} Graph;

typedef struct __EdgeList
{
  Edge *head;
} EdgeList;

void makeVerticesList(Graph *graph);
Vertices *makeVertices(char name);

void makeEdgeList(EdgeList *edgeList);
Edge *makeEdge(Edge *edge, int weight, int name1, int name2);

Vertices *findVertices(Graph *graph);

int main()
{
  char cmd;
}

Vertices *findVertices(Graph *graph, int name)
{
  Vertices *vertices = graph->head;

  while (vertices)
  {
    if (vertices->name == name)
      return vertices;
    vertices = vertices->next;
  }

  return 0;
}

Vertices *makeVertices(int name)
{
  Vertices *vertices = (Vertices *)calloc(1, sizeof(Vertices));
  vertices->name = name;
  return vertices;
}

void makeVerticesList(Graph *graph)
{
  Vertices *vertices = graph->head;
  for (int i = 1; i < 7; i++)
  {
    vertices = makeVertices(i);
    vertices = vertices->next;
  }
}

Edge *makeEdge(Edge *edge, int weight, int name1, int name2)
{
  Edge *edge = (Edge *)calloc(1, sizeof(Edge));
  edge->weight = weight;
}
void makeEdgeList(EdgeList *edgeList)
{
  Edge *edge = edgeList->head;
}