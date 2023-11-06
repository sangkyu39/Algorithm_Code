#include <stdio.h>
#include <stdlib.h>

int *arr, m;

int insertItem(int key);
int findElement(int key);
int main()
{
  int key, n;
  char cmd;
  scanf("%d %d", &m, &n);
  getchar();

  arr = (int *)calloc(m, sizeof(int));

  while (1)
  {
    scanf("%c", &cmd);
    if (cmd == 'e')
      break;
    else
    {
      scanf("%d", &key);
      if (cmd == 'i')
      {
        printf("%d\n", insertItem(key));
      }
      else if (cmd == 's')
      {
        int idx = findElement(key);
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
int findElement(int key)
{
  int v;
  for (int i = 0; i < m; i++)
  {
    v = (key % m + i) % m;
    if (arr[v] == key)
      return v;
  }
  return -1;
}

int insertItem(int key)
{
  int v;
  for (int i = 0; i < m; i++)
  {
    v = (key % m + i) % m;
    if (arr[v] == 0)
    {
      arr[v] = key;
      return v;
    }
    printf("C");
  }
  return 0;
}
