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
  char name;
  Label label;
  int topoNum;
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
  char v1, v2;
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
  Vertex *vertex;
} Queue;

char *topOrder; // n + 1 size
int n, m, topoN;

typedef struct __QueueType
{
  Queue *front, *rear;
} QueueType;

int opposite(Edge *e, char name);
// Vertex List 만들기
Vertex *getVertex(char name);
void insertVertex(Graph *graph, char name);
// Edge List 만들기
Edge *getEdge(char v1, char v2);
void insertEdge(Graph *graph, char v1, char v2);
// Incidence 만들기
Incidence *getIncidence(Edge *e);
void insertIncidence(Vertex *v, Edge *e);
Vertex *findVertex(Graph *graph, char name);

void rtopologicalSort(Graph *graph, int name);
void buildGraph(Graph *graph);

int main()
{
  Graph *graph = (Graph *)calloc(1, sizeof(Graph));

  buildGraph(graph);

  rtopologicalSort(graph, graph->vHead->name);

  if (topoN != 0)
    printf("0\n");
  else
  {
    for (int i = 1; i <= n; i++)
      printf(" %c", topOrder[i]);
    printf("\n");
  }

  return 0;
}

void buildGraph(Graph *graph)
{

  char v1, v2;

  scanf("%d", &n);
  getchar();
  topoN = n;

  for (int i = 0; i < n; i++)
  {
    char name;
    scanf("%c", &name);
    getchar();
    insertVertex(graph, name);
  }
  topOrder = (char *)calloc(n + 1, sizeof(char));

  scanf("%d", &m);
  getchar();
  for (int i = 0; i < m; i++)
  {
    scanf("%c %c", &v1, &v2);
    getchar();
    insertEdge(graph, v1, v2);
  }
}
Vertex *findVertex(Graph *graph, char name)
{
  Vertex *v = graph->vHead;
  while (v && v->name != name)
  {
    v = v->next;
  }
  return v;
}

Vertex *getVertex(char name)
{
  Vertex *vertex = (Vertex *)calloc(1, sizeof(Vertex));
  vertex->name = name;
  return vertex;
}

void insertVertex(Graph *graph, char name)
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

Edge *getEdge(char v1, char v2)
{
  Edge *edge = (Edge *)calloc(1, sizeof(Edge));
  edge->v1 = v1;
  edge->v2 = v2;

  return edge;
}

void insertEdge(Graph *graph, char v1, char v2)
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
      prevE = prevE->next;
    prevE->next = newE;
  }
  insertIncidence(findVertex(graph, v1), newE);
}

Incidence *getIncidence(Edge *e)
{
  Incidence *incidence = (Incidence *)calloc(1, sizeof(Incidence));
  incidence->edge = e;
  return incidence;
}

int opposite(Edge *e, char name)
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
    newInc->next = prevInc;
    v->iHead = newInc;
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

void rTopologicalSort(Graph *graph, int name)
{
  Vertex *v = findVertex(graph, name);
  v->label = Visited;
  Incidence *inc = v->iHead;

  while (inc)
  {
    Edge *e = inc->edge;
    Vertex *w = findVertex(graph, opposite(e, name));
    if (w->label == Fresh)
      rTopologicalSort(graph, w->name);
    else if (w->topoNum == 0)
    {
      return;
    }
  }
  v->topoNum = topoN--;
  topOrder[topoN] = name;
}