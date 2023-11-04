#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int arr[100], tmp[100], cnt;

void merge(int left, int m, int right);
void rMergeSort(int left, int right);

void print()
{
  for (int i = 0; i < cnt; i++)
  {
    printf("%d ", arr[i]);
  }
  printf("\n");
}

int main()
{
  scanf("%d", &cnt);

  for (int i = 0; i < cnt; i++)
  {
    scanf("%d", &arr[i]);
  }
  rMergeSort(0, cnt - 1);

  print();

  return 0;
}

void rMergeSort(int left, int right)
{
  if (left < right)
  {
    int mid = (left + right) / 2;
    rMergeSort(left, mid);
    rMergeSort(mid + 1, right);
    merge(left, mid, right);
  }
}

void merge(int left, int mid, int right)
{
  int i, k;
  i = k = left;
  int j = mid + 1;

  while (i <= mid && j <= right)
  {
    if (arr[i] <= arr[j])
    {
      tmp[k++] = arr[i++];
    }
    else
    {
      tmp[k++] = arr[j++];
    }
  }
  while (i <= mid)
  {
    tmp[k++] = arr[i++];
  }
  while (j <= right)
  {
    tmp[k++] = arr[j++];
  }
  for (k = left; k <= right; k++)
  {
    arr[k] = tmp[k];
  }
  return;
}