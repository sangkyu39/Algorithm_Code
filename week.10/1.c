// 인접리스트 구조

#include <stdio.h>
#include <stdlib.h>

/* 그래프 상세 구현 과정

1. 그래프를 다음 필드로 구성되는 구조체로 정의
- vertex : 정점 레코드의 배열 [0:n-1]
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
typedef struct __Vertex
{
  int name;
  struct __Vertex *next;     // 모든 정점과 연결
  struct __Incidence *iHead; // 부착 리스트를 통해 해당 노드의 간선에 대한 정보 저장
} Vertex;

// 부착 리스트 (각 정점의 부착 간선을 간선 노드에 대한 참조들의 리스트)
typedef struct __Incidence
{
  struct __Edge *edge;
  struct __Incidence *next; // 해당 정점에 들어있는 간선만 연결
} Incidence;

// 간선 리스트
typedef struct __Edge
{
  int weight, v1, v2;
  struct __Edge *next; // 모든 간선과 연결
} Edge;

typedef struct __Graph
{
  Vertex *vHead;
  Edge *eHead;
} Graph;

int diffrentV(Edge *e, int name);
// Vertex List 만들기
Vertex *getVertex(int name);
void insertVertex(Graph *graph, int name);
// Edge List 만들기
Edge *getEdge(int w, int v1, int v2);
void insertEdge(Graph *graph, int w, int v1, int v2);
// Incidence 만들기
Incidence *getIncidence(Edge *e);
void insertIncidence(Vertex *v, Edge *e);

void print(Graph *graph, int name);
Vertex *findVertex(Graph *graph, int name);
void updateEdge(Graph *graph, int w, int v1, int v2);
void removeIncidence(Vertex *v, Edge *edge);
void removeEdge(Graph *graph, int v1, int v2);
Edge *findEdge(Graph *graph, int v1, int v2);

int main()
{
  Graph *graph = (Graph *)calloc(1, sizeof(Graph));
  int info[8][3] = {{1, 1, 2}, {1, 1, 3}, {1, 1, 4}, {2, 1, 6}, {1, 2, 3}, {4, 3, 5}, {4, 5, 5}, {3, 5, 6}};
  char cmd;
  int name, w, v1, v2;
  for (int i = 1; i < 7; i++)
  {
    insertVertex(graph, i);
  }

  for (int i = 0; i < 8; i++)
  {
    insertEdge(graph, info[i][0], info[i][1], info[i][2]);
  }

  while (1)
  {
    scanf("%c", &cmd);
    if (cmd == 'a')
    {
      scanf("%d", &name);
      print(graph, name);
    }
    else if (cmd == 'm')
    {
      scanf("%d %d %d", &v1, &v2, &w);
      updateEdge(graph, w, v1, v2);
    }
    else if (cmd == 'q')
      break;
  }
}

Vertex *findVertex(Graph *graph, int name)
{
  Vertex *v = graph->vHead;
  while (v && v->name != name)
  {
    v = v->next;
  }
  return v;
}

void print(Graph *graph, int name)
{
  Vertex *v = findVertex(graph, name);

  if (v == NULL)
  {
    printf("-1\n");
    return;
  }
  Incidence *inc = v->iHead;
  while (inc)
  {
    Edge *e = inc->edge;
    printf(" %d %d", diffrentV(e, name), e->weight);
    inc = inc->next;
  }
  printf("\n");
}
Vertex *getVertex(int name)
{
  Vertex *vertex = (Vertex *)calloc(1, sizeof(Vertex));
  vertex->name = name;
  return vertex;
}

void insertVertex(Graph *graph, int name)
{
  Vertex *newV = getVertex(name);
  Vertex *prevV = graph->vHead;

  if (prevV == NULL)
  {
    graph->vHead = newV;
  }
  else
  {
    while (prevV->next)
      prevV = prevV->next;
    prevV->next = newV;
  }
}

Edge *getEdge(int w, int v1, int v2)
{
  Edge *edge = (Edge *)calloc(1, sizeof(Edge));
  edge->weight = w;
  edge->v1 = v1;
  edge->v2 = v2;

  return edge;
}

void insertEdge(Graph *graph, int w, int v1, int v2)
{
  Edge *newE = getEdge(w, v1, v2);
  Edge *prevE = graph->eHead;

  if (prevE == NULL)
  {
    graph->eHead = newE;
  }
  else
  {
    while (prevE->next)
      prevE = prevE->next;
    prevE->next = newE;
  }
  insertIncidence(findVertex(graph, v1), newE);
  if (v1 != v2)
    insertIncidence(findVertex(graph, v2), newE);
}

Incidence *getIncidence(Edge *e)
{
  Incidence *incidence = (Incidence *)calloc(1, sizeof(Incidence));
  incidence->edge = e;
  return incidence;
}

int diffrentV(Edge *e, int name)
{
  return (e->v1 == name) ? e->v2 : e->v1;
}

void insertIncidence(Vertex *v, Edge *e)
{
  Incidence *newInc = getIncidence(e);
  Incidence *prevInc = v->iHead;
  int incName = diffrentV(e, v->name);

  if (prevInc == NULL)
  {
    v->iHead = newInc;
  }
  else
  {
    Edge *prevE = prevInc->edge;
    // 가장 처음에 들어가야 하는 경우
    if (incName < diffrentV(prevE, v->name))
    {
      newInc->next = prevInc;
      v->iHead = newInc;
    }
    // 중간에 들어가는 경우
    else
    {
      while (prevInc->next)
      {
        prevE = prevInc->next->edge;
        if (incName < diffrentV(prevE, v->name))
          break;
        prevInc = prevInc->next;
      }
      newInc->next = prevInc->next;
      prevInc->next = newInc;
    }
  }
}

Edge *findEdge(Graph *graph, int v1, int v2)
{
  Edge *e = graph->eHead;
  while (e)
  {
    if ((e->v1 == v1 && e->v2 == v2) || (e->v1 == v2 && e->v2 == v1))
    {
      break;
    }
    e = e->next;
  }
  return e;
}

void removeEdge(Graph *graph, int v1, int v2)
{
  Edge *delE = findEdge(graph, v1, v2);
  Edge *prevE = graph->eHead;
  if (delE == prevE)
  {
    graph->eHead = delE->next;
  }
  while (prevE->next)
  {
    if (prevE->next == delE)
    {
      prevE->next = delE->next;
      break;
    }
    prevE = prevE->next;
  }
  removeIncidence(findVertex(graph, v1), delE);
  if (v1 != v2)
    removeIncidence(findVertex(graph, v2), delE);
}

void removeIncidence(Vertex *v, Edge *edge)
{
  Incidence *inc = v->iHead;
  if (inc->edge == edge)
  {
    v->iHead = inc->next;
    return 0;
  }
  while (inc->next)
  {
    if (inc->next->edge == edge)
    {
      break;
    }
    inc = inc->next;
  }
  Incidence *delInc = inc->next;
  inc->next = delInc->next;

  free(delInc);
}
void updateEdge(Graph *graph, int w, int v1, int v2)
{
  if (findVertex(graph, v1) == NULL || findVertex(graph, v2) == NULL)
  {
    printf("-1\n");
    return;
  }
  Edge *e = findEdge(graph, v1, v2);
  // edge 생성
  if (e == NULL)
  {
    insertEdge(graph, w, v1, v2);
  }
  // edge 삭제
  else if (w == 0)
  {
    removeEdge(graph, v1, v2);
  }
  // edge 수정
  else
  {
    e->weight = w;
  }
}