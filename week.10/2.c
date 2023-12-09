#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int matrix[7][7];

// Edge List 만들기
void insertEdge(int w, int v1, int v2);

void updateEdge(int w, int v1, int v2);
void print(int name);
int isVertex(int name);

int main()
{
  int info[8][3] = {{1, 1, 2}, {1, 1, 3}, {1, 1, 4}, {2, 1, 6}, {1, 2, 3}, {4, 3, 5}, {4, 5, 5}, {3, 5, 6}};
  char cmd;
  int name, w, v1, v2;

  for (int i = 0; i < 8; i++)
  {
    insertEdge(info[i][0], info[i][1], info[i][2]);
  }

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
      updateEdge(w, v1, v2);
    }
    else if (cmd == 'q')
      break;
  }

  return 0;
}

void insertEdge(int w, int v1, int v2)
{
  matrix[v1][v2] = w;
  if (v1 != v2)
    matrix[v2][v1] = w;
}

void print(int name)
{
  if (!isVertex(name))
  {
    printf("-1\n");
    return;
  }

  for (int i = 0; i < 7; i++)
  {
    if (matrix[name][i] != 0)
    {
      printf("%d %d ", i, matrix[name][i]);
    }
  }
  printf("\n");
}

int isVertex(int name)
{
  if (name <= 0 || name >= 7)
    return 0;
  return 1;
}

void updateEdge(int w, int v1, int v2)
{
  if (isVertex(v1) && isVertex(v2))
  {
    matrix[v1][v2] = w;
    if (v1 != v2)
      matrix[v2][v1] = w;
  }
  else
    printf("-1\n");
}