#include <stdio.h>
#include <stdlib.h>

typedef struct __Edge
{
  int number;
  int weight;
  struct __Edge *next;
} Edge;

typedef struct __Vertex
{
  Edge *edge;
} Vertex;

Vertex vertex[7];

void addVertex(int number1, int number2, int weight);
void insertEdge(int stand, int number, int weight);
void initVertex();

void print(int stand);
void update(int number1, int number2, int weight);

Edge *makeEdge(int number, int weight)
{
  Edge *edge = (Edge *)calloc(1, sizeof(Edge));
  edge->number = number;
  edge->weight = weight;
  return edge;
}

int main()
{
  char cmd;
  int number, number1, number2, weight;

  initVertex();

  while (1)
  {
    scanf("%c", &cmd);
    if (cmd == 'a')
    {
      scanf("%d", &number);
      print(number);
    }
    else if (cmd == 'm')
    {
      scanf("%d %d %d", &number, &number1, &number2);
      updateVertex(number1, number2, weight);
    }
    else if (cmd == 'q')
    {
      break;
    }
  }
}

void print(int stand)
{
  Edge *edge = vertex[stand].edge;

  while (edge)
  {
    printf(" %d %d", edge->number, edge->weight);
    edge = edge->next;
  }
  printf("\n");
}
void insertEdge(int stand, int number, int weight)
{
  Edge *edge = makeEdge(number, weight);

  Edge *next = vertex[stand].edge;

  while (next != NULL)
  {
    if (next->number >= number || next->next == NULL)
    {
      edge->next = next->next;
      next->next = edge;
      return;
    }
    next = next->next;
  }
  edge->next = next;
  vertex[stand].edge = edge;
}

void updateEdge(int stand, int number, int weight)
{
  Edge *next = vertex[stand].edge;

  while (next->next != NULL)
  {
    if (next->next->number == number)
      break;
  }
  if (next->number == number)
  {
    if (weight == 0)
    {
      next->next = next->next->next;
    }
    next->weight = weight;
  }
}

void updateVertex(int number1, int number2, int weight)
{
  updateEdge(number1, number2, weight);
  updateEdge(number2, number1, weight);
}

void addVertex(int number1, int number2, int weight)
{
  insertEdge(number1, number2, weight);

  if (number1 == number2)
    return;

  insertEdge(number2, number1, weight);
}

void initVertex()
{
  addVertex(1, 2, 1);
  addVertex(1, 3, 1);
  addVertex(1, 4, 1);
  addVertex(1, 6, 2);
  addVertex(2, 3, 1);
  addVertex(3, 5, 4);
  addVertex(5, 5, 4);
  addVertex(5, 6, 3);
}