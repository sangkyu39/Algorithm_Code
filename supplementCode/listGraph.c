#include <stdio.h>
#include <stdlib.h>

#define elem int

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
  struct __Vertex *next;
  struct __Incidence *incHead;
} Vertex;

typedef struct __Incidence
{
  struct __Edge *edge;
  struct __Incidence *next;
} Incidence;

typedef struct __Edge
{
  int v1, v2;
  struct __Edge *next;
} Edge;

typedef struct __Graph
{
  Vertex *vHead;
  Edge *eHead;
} Graph;

Graph *graph;

void insertVertex(elem name);
void insertEdge(int w, elem v1, elem v2);
void insertIncidence(Vertex *v, Edge *e);

elem opposite(Edge *e, elem name);
Vertex *findVertex(elem name);

int main()
{
  graph = (Graph *)calloc(1, sizeof(Graph));
}

Vertex *findVertex(elem name)
{
  Vertex *v = graph->vHead;
  while (v)
  {
    if (v->name == name)
      break;
    v = v->next;
  }
  return v;
}

elem opposite(Edge *e, elem name)
{
  return (e->v1 == name) ? e->v2 : e->v1;
}

void insertVertex(elem name)
{
  Vertex *newV = (Vertex *)calloc(1, sizeof(Vertex));
  newV->name = name;
  Vertex *prevV = graph->vHead;

  if (prevV)
    graph->vHead = newV;
  else
  {
    while (prevV->next)
      prevV->next;
    prevV->next = newV;
  }
}

void insertEdge(int w, elem v1, elem v2)
{
  Edge *newE = (Edge *)calloc(1, sizeof(Edge));
  newE->v1 = v1;
  newE->v2 = v2;
  Edge *prevE = graph->eHead;

  if (prevE)
    graph->eHead = newE;
  else
  {
    while (prevE->next)
      prevE->next;
    prevE->next = newE;
  }
  insertIncidence(findVertex(v1), newE);
  if (v1 != v2)
    insertIncidence(findVertex(v2), newE);
}

void insertIncidence(Vertex *v, Edge *e)
{
  Incidence *newInc = (Incidence *)calloc(1, sizeof(Incidence));
  newInc->edge = e;
  Incidence *prevInc = v->incHead;

  elem incName = opposite(e, v->name);

  if (prevInc)
    v->incHead = newInc;
  else
  {
    // 부착노드 정렬 순서에 따라서 조건 추가
    // 오름차순인 경우
    Edge *prevE = prevInc->edge;
    if (incName < opposite(prevE, v->name))
    {
      newInc->next = prevInc;
      v->incHead = newInc;
    }
    else
    {
      while (prevInc->next)
      {
        prevE = prevInc->edge;
        if (incName < opposite(prevE, v->name))
          break;
        prevInc = prevInc->next;
      }
      newInc->next = prevInc->next;
      prevInc->next = newInc;
    }
  }
}