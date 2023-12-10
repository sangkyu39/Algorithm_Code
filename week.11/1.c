#include <stdio.h>
#include <stdlib.h>

typedef enum __Label
{
  Fresh,
  Visited,
  Tree,
  Back
} Label;

typedef struct __Vertex
{
  int name;
  Label label;
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
  Label label;
  int v1, v2;
  struct __Edge *next;
} Edge;

typedef struct __Graph
{
  Vertex *vHead;
  Edge *eHead;
} Graph;

int opposite(Edge *e, int name);

Vertex *findVertex(Graph *graph, int name);
Vertex *getVertex(int name);
void insertVertex(Graph *graph, int name);

Edge *getEdge();
void insertEdge(Graph *graph, int v1, int v2);

void insertIncidence(Vertex *v, Edge *newE);
Incidence *getIncidence(Edge *e);

void rDFS(Graph *graph, int name);

int main()
{
  Graph *graph = (Graph *)calloc(1, sizeof(Graph));
  char cmd;
  int n, m, s, v1, v2;
  scanf("%d %d %d", &n, &m, &s);

  for (int i = 1; i <= n; i++)
  {
    insertVertex(graph, i);
  }

  for (int i = 0; i < m; i++)
  {
    scanf("%d %d", &v1, &v2);
    insertEdge(graph, v1, v2);
  }

  rDFS(graph, s);

  return 0;
}

Vertex *getVertex(int name)
{
  Vertex *v = (Vertex *)calloc(1, sizeof(Vertex));
  v->name = name;
  v->label = Fresh;
  return v;
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
    {
      prevV = prevV->next;
    }
    prevV->next = newV;
  }
}

Vertex *findVertex(Graph *graph, int name)
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

Edge *getEdge(int v1, int v2)
{
  Edge *e = (Edge *)calloc(1, sizeof(Edge));
  e->v1 = v1;
  e->v2 = v2;
  e->label = Fresh;

  return e;
}

void insertEdge(Graph *graph, int v1, int v2)
{
  Edge *newE = getEdge(v1, v2);
  Edge *prevE = graph->eHead;

  if (prevE == NULL)
  {
    graph->eHead = newE;
  }
  else
  {
    while (prevE->next)
    {
      prevE = prevE->next;
    }
    prevE->next = newE;
  }
  insertIncidence(findVertex(graph, v1), newE);
  if (v1 != v2)
    insertIncidence(findVertex(graph, v2), newE);
}

int opposite(Edge *e, int name)
{
  return (e->v1 == name) ? e->v2 : e->v1;
}

Incidence *getIncidence(Edge *e)
{
  Incidence *inc = (Incidence *)calloc(1, sizeof(Incidence));
  inc->edge = e;
  return inc;
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

void rDFS(Graph *graph, int name)
{
  Vertex *v = findVertex(graph, name);
  printf("%d\n", name);
  v->label = Visited;
  Incidence *inc = v->iHead;

  while (inc)
  {
    Edge *e = inc->edge;
    if (e->label == Fresh)
    {
      Vertex *w = findVertex(graph, opposite(e, name));
      if (w->label == Fresh)
      {
        e->label = Tree;
        rDFS(graph, w->name);
      }
      else
        e->label = Back;
    }
    inc = inc->next;
  }
}