#include <stdio.h>
#include <stdlib.h>

typedef struct __Vertex
{
  int name;
  struct __Vertex *next;
  struct __Incidence *iHead;
} Vertex;

typedef struct __Edge
{
  int w, v1, v2;
  struct __Edge *next;
} Edge;

typedef struct __Incidence
{
  Edge *e;
  struct __Incidence *next;
} Incidence;

typedef struct __Graph
{
  Vertex *vHead;
  Edge *eHead;
} Graph;

void insertVertex(Graph *graph, int name);
void insertEdge(Graph *graph, int w, int v1, int v2);
void insertIncidence(Edge *e, Vertex *v);

int main()
{
}

void insertVertex(Graph *graph, int name)
{
  Vertex *v = (Vertex *)calloc(1, sizeof(Vertex));
  v->name = name;
  Vertex *prevV = graph->vHead;
  if (prevV == NULL)
    graph->vHead;
  else
  {
    while (prevV)
      prevV = prevV->next;
    prevV->next = v;
  }
}

void insertEdge(Graph *graph, int w, int v1, int v2)
{
  Edge *e = (Edge *)calloc(1, sizeof(Edge));
  e->v1 = v1;
  e->v2 = v2;
  e->w = w;

  Edge *prevE = graph->eHead;
  if (prevE == NULL)
    graph->eHead = e;
  else
  {
    while (prevE)
      prevE = prevE->next;
    prevE->next = e;
  }
}