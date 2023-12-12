#include <stdio.h>
#include <stdlib.h>

typedef struct __Vertex
{
  char name;
  int num;
  int indegree;
  struct __Vertex *next;
  struct __Incidence *iHead;
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

typedef struct __Queue
{
  struct __Queue *next;
  Vertex *v;
} Queue;

int *topOrder; // n + 1 size

typedef struct __Queue
{
  struct __Queue *next;
} Queue;

int opposite(Edge *e, int name);
// Vertex List 만들기
Vertex *getVertex(int name);
void insertVertex(Graph *graph, int name);
// Edge List 만들기
Edge *getEdge(int w, int v1, int v2);
void insertEdge(Graph *graph, int w, int v1, int v2);
// Incidence 만들기
Incidence *getIncidence(Edge *e);
void insertIncidence(Vertex *v, Edge *e);
Vertex *findVertex(Graph *graph, int name);

void buildGraph(Graph *graph);
void topologicalSort();

int main()
{
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

int opposite(Edge *e, int name)
{
  return (e->v1 == name) ? e->v2 : e->v1;
}

void insertIncidence(Vertex *v, Edge *e)
{
  Incidence *newInc = getIncidence(e);
  Incidence *prevInc = v->iHead;
  int incName = opposite(e, v->name);

  if (prevInc == NULL)
  {
    v->iHead = newInc;
  }
  else
  {
    Edge *prevE = prevInc->edge;
    // 가장 처음에 들어가야 하는 경우
    if (incName < opposite(prevE, v->name))
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
        if (incName < opposite(prevE, v->name))
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
