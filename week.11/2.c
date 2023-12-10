#include <stdio.h>
#include <stdlib.h>

typedef enum __Label
{
  Fresh,
  Visited,
  Tree,
  Cross
} Label;

typedef struct __Vertex
{
  int name;
  Label label;
  struct __Vertex *next;
} Vertex;

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

Edge ***matrix;
Vertex **L;
int n, m;
int opposite(Edge *e, int name);

Vertex *findVertex(Graph *graph, int name);
Vertex *getVertex(int name);
void insertVertex(Graph *graph, int name);

Edge *getEdge();
void insertEdge(Graph *graph, int v1, int v2);

void BFS(Graph *graph, int name);

int main()
{
  Graph *graph = (Graph *)calloc(1, sizeof(Graph));
  char cmd;
  int s, v1, v2;
  scanf("%d %d %d", &n, &m, &s);

  for (int i = 1; i <= n; i++)
  {
    insertVertex(graph, i);
  }

  L = (Vertex **)calloc(n, sizeof(Vertex *));
  matrix = (Edge ***)calloc(n + 1, sizeof(Edge **));

  for (int i = 0; i <= n; i++)
  {
    matrix[i] = (Edge **)calloc(n + 1, sizeof(Edge *));
  }

  for (int i = 0; i < m; i++)
  {
    scanf("%d %d", &v1, &v2);
    insertEdge(graph, v1, v2);
  }

  BFS(graph, s);
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
  matrix[v1][v2] = newE;
  matrix[v2][v1] = newE;
}

int opposite(Edge *e, int name)
{
  return (e->v1 == name) ? e->v2 : e->v1;
}

void BFS(Graph *graph, int name)
{
  int i = 0;
  L[i] = findVertex(graph, name);
  L[i]->label = Visited;
  int level = 0;

  for (; L[i] != NULL; i++)
  {
    Vertex *v = L[i];
    printf("%d\n", v->name);
    for (int j = 1; j <= n; j++)
    {
      Edge *e = matrix[v->name][j];
      if (e == NULL)
        continue;

      if (e->label == Fresh)
      {
        Vertex *w = findVertex(graph, opposite(e, v->name));
        if (w->label == Fresh)
        {
          e->label = Tree;
          w->label = Visited;
          L[++level] = w;
        }
        else
        {
          e->label = Cross;
        }
      }
    }
  }
}