#include <stdio.h>
#include <stdio.h>
#include <string.h>

/// @brief 배열 arr을 오름차순으로 정렬 (삽입정렬)
/// @param arr
/// @param n
void inPlaceInsertionSort(int *arr, int n)
{
  for (int pass = 1; pass < n; pass++)
  {
    int save = arr[pass];
    int j = pass - 1;
    while ((j >= 0) && (arr[j] > save))
    {
      arr[j + 1] = arr[j];
      j--;
    }
    arr[j + 1] = save;
  }
}

int main()
{
  int n;

  scanf("%d", &n);
  int *arr = (int *)calloc(n, sizeof(int));

  for (int i = 0; i < n; i++)
  {
    scanf("%d", &arr[i]);
  }

  inPlaceInsertionSort(arr, n);

  for (int i = 0; i < n; i++)
  {
    printf(" %d", arr[i]);
  }

  return 0;
}