#include <stdio.h>
#include <stdlib.h>

typedef struct __Bucket
{
  int key;
  struct __Bucket *next;
} Bucket;

Bucket **bucketArr;
int m;

Bucket *getBucket(int key);
void printElement();
void insertItem(int key);
int findElement(int key);
int removeElement(int key);
int main()
{
  int key;
  char cmd;
  scanf("%d", &m);
  getchar();

  bucketArr = (Bucket **)calloc(m, sizeof(Bucket *));

  while (1)
  {
    scanf("%c", &cmd);
    if (cmd == 'e')
      break;
    else if (cmd == 'p')
      printElement();
    else
    {
      scanf("%d", &key);
      if (cmd == 'i')
      {
        insertItem(key);
      }
      else if (cmd == 's')
      {
        printf("%d\n", findElement(key));
      }
      else if (cmd == 'd')
      {
        printf("%d\n", removeElement(key));
      }
    }
    getchar();
  }

  return 0;
}

Bucket *getBucket(int key)
{
  Bucket *bucket = (Bucket *)calloc(1, sizeof(Bucket));
  bucket->key = key;
  return bucket;
}

int findElement(int key)
{
  int cnt = 1;
  int v = key % m;
  Bucket *bucket = bucketArr[v];
  while (bucket)
  {
    if (bucket->key == key)
      return cnt;
    bucket = bucket->next;
    cnt++;
  }
  return 0;
}

void insertItem(int key)
{
  int v = key % m;
  Bucket *bucket = getBucket(key);
  bucket->next = bucketArr[v];
  bucketArr[v] = bucket;
  return;
}

int removeElement(int key)
{
  int v = key % m;
  int cnt = 1;
  Bucket *bucket = bucketArr[v];
  Bucket *prev;
  while (bucket)
  {
    if (bucket->key == key)
    {
      if (cnt == 1)
        bucketArr[v] = bucket->next;
      else
        prev->next = bucket->next;
      return cnt;
    }
    prev = bucket;
    bucket = bucket->next;
    cnt++;
  }
  return 0;
}

void printElement()
{
  Bucket *bucket;
  for (int i = 0; i < m; i++)
  {
    bucket = bucketArr[i];
    while (bucket)
    {
      printf(" %d", bucket->key);
      bucket = bucket->next;
    }
  }
  return;
}