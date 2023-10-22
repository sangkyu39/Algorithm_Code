#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *arr, size;

#define swap(a, b) \
  do               \
  {                \
    int tmp = a;   \
    a = b;         \
    b = tmp;       \
  } while (0)

// 퀵 정렬 필요 함수
void inPlaceQuickSort(int left, int right);
int findPivot(int left, int right);
int inPlacePartition(int left, int right, int pivotIdx);

void print()
{
  for (int i = 0; i < size; i++)
  {
    printf("%d ", arr[i]);
  }
  printf("\n");
}

int main()
{
  scanf("%d", &size);

  arr = (int *)calloc(size, sizeof(int));

  for (int i = 0; i < size; i++)
  {
    scanf("%d", &arr[i]);
  }

  inPlaceQuickSort(0, size - 1);

  print();

  return 0;
}

int findPivot(int left, int right)
{
  // 랜덤 범위 주의
  return rand() % (right - left + 1) + left;
}

void inPlaceQuickSort(int left, int right)
{
  if (left >= right)
  {
    return;
  }
  int pivotIdx = findPivot(left, right);
  pivotIdx = inPlacePartition(left, right, pivotIdx);
  inPlaceQuickSort(left, pivotIdx - 1);
  inPlaceQuickSort(pivotIdx + 1, right);
}

int inPlacePartition(int left, int right, int pivotIdx)
{
  int pivot = arr[pivotIdx];
  swap(arr[pivotIdx], arr[right]);
  pivotIdx = right;
  // 오른쪽 1 감소 주의
  right -= 1;

  while (left <= right)
  {
    while (left <= right && arr[left] <= pivot)
    {
      left++;
    }
    while (left <= right && arr[right] >= pivot)
    {
      right--;
    }
    if (left < right)
    {
      swap(arr[left], arr[right]);
    }
  }
  swap(arr[left], arr[pivotIdx]);

  return left;
}