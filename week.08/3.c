#include <stdio.h>
#include <stdlib.h>

int *arr, m;

int insertItem(int key, int q);
int findElement(int key, int q);
void print();

int main()
{
  int key, n, q;
  char cmd;
  scanf("%d %d %d", &m, &n, &q);
  getchar();

  arr = (int *)calloc(m, sizeof(int));

  while (1)
  {
    scanf("%c", &cmd);
    if (cmd == 'e')
    {
      print();
      break;
    }
    else if (cmd == 'p')
      print();
    else
    {
      scanf("%d", &key);
      if (cmd == 'i')
      {
        printf("%d\n", insertItem(key, q));
      }
      else if (cmd == 's')
      {
        int idx = findElement(key, q);
        printf("%d\n", idx);
        if (idx != -1)
        {
          printf("%d\n", arr[idx]);
        }
      }
    }
    getchar();
  }

  return 0;
}
int findElement(int key, int q)
{
  int v;
  for (int i = 0; i < m; i++)
  {
    v = (key % m + i * (q - key * q)) % m;
    if (arr[v] == key)
      return v;
  }
  return -1;
}

int insertItem(int key, int q)
{
  int v;
  for (int i = 0; i < m; i++)
  {
    v = (key % m + i * (q - (key % q))) % m;
    if (arr[v] == 0)
    {
      arr[v] = key;
      return v;
    }
    printf("C");
  }
  return 0;
}

void print()
{
  for (int i = 0; i < m; i++)
  {
    printf(" %d", arr[i]);
  }
  printf("\n");
}