#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define swap(a, b) \
  do               \
  {                \
    int tmp = (a); \
    (a) = (b);     \
    (b) = tmp;     \
  } while (0)

typedef struct __Edge
{
  int left;
  int right;
} Edge;

void inPlaceQuickSort(int *arr, int left, int right);
int findPivot(int left, int right);
Edge inPlacePartition(int *arr, int left, int right, int pivotIdx);

void print(int *arr, int n)
{
  for (int i = 0; i < n; i++)
  {
    printf("%d ", arr[i]);
  }
  printf("\n");
}

int main()
{
  int *arr, size;
  scanf("%d", &size);

  arr = (int *)calloc(size, sizeof(int));

  for (int i = 0; i < size; i++)
  {
    scanf("%d", &arr[i]);
  }

  inPlaceQuickSort(arr, 0, size - 1);
  print(arr, size);
  return 0;
}

int findPivot(int left, int right)
{
  // left와 right 사이 랜덤 값
  return rand() % (right - left + 1) + left;
}

void inPlaceQuickSort(int *arr, int left, int right)
{
  if (left >= right)
  {
    return;
  }
  int pivotIdx = findPivot(left, right);

  Edge edge = inPlacePartition(arr, left, right, pivotIdx);
  inPlaceQuickSort(arr, left, edge.left - 1);
  inPlaceQuickSort(arr, edge.right + 1, right);
}

Edge inPlacePartition(int *arr, int left, int right, int pivotIdx)
{
  int pivot = arr[pivotIdx];
  swap(arr[pivotIdx], arr[right]);

  Edge edge;
  edge.left = left;
  edge.right = right - 1;

  while (edge.left <= edge.right)
  {
    while (edge.left <= edge.right && arr[edge.left] <= pivot)
    {
      edge.left++;
    }
    while (edge.left <= edge.right && arr[edge.right] >= pivot)
    {
      edge.right--;
    }
    if (edge.left < edge.right)
    {
      swap(arr[edge.left], arr[edge.right]);
    }
  }
  swap(arr[edge.left], arr[right]);
  return edge;
}