#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int H[100], n = 0;

void swap(int *x, int *y);
void inPlaceHeapSort();
void printArray();
void downHeap(int idx, int last);
void rBuildHeap(int idx);
void buildHeap();

int main()
{
  scanf("%d", &n);

  for (int i = 1; i <= n; i++)
  {
    scanf("%d", &H[i]);
  }
  inPlaceHeapSort();
  printArray();

  return 0;
}

void swap(int *x, int *y)
{
  int tmp = *x;
  *x = *y;
  *y = tmp;
}

void inPlaceHeapSort()
{
  rBuildHeap(1);
  for (int i = n; i > 1; i--)
  {
    swap(&H[1], &H[i]);
    downHeap(1, i - 1);
  }
}

void rBuildHeap(int idx)
{
  if (idx > n)
  {
    return;
  }
  rBuildHeap(2 * idx);
  rBuildHeap(2 * idx + 1);
  downHeap(idx, n);
}

void downHeap(int idx, int last)
{
  int left = idx * 2;
  int right = idx * 2 + 1;

  if (left > last)
  {
    return;
  }
  int biggerIdx = left;

  if (right <= last)
  {
    biggerIdx = (H[right] > H[left]) ? right : left;
  }

  if (H[biggerIdx] > H[idx])
  {
    swap(&H[biggerIdx], &H[idx]);
    downHeap(biggerIdx, last);
  }
}

void printArray()
{
  for (int i = 1; i <= n; i++)
  {
    printf(" %d", H[i]);
  }
}