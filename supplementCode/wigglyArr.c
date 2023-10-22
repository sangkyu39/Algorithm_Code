#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 - 파형 배열 -
 홀수번째 인덱스의 값이 양 옆의 짝수 번째 인덱스 값보다 작도록 정렬
*/

int arr[100], n = 0;

#define swap(a, b) \
  do               \
  {                \
    int tmp = (a); \
    (a) = (b);     \
    (b) = tmp;     \
  } while (0)

void wiggly()
{
  for (int i = 1; i < n; i += 2)
  {
    if (i - 1 >= 0 && arr[i] > arr[i - 1])
    {
      swap(arr[i], arr[i - 1]);
    }
    else if (i + 1 < n && arr[i] > arr[i + 1])
    {
      swap(arr[i], arr[i + 1]);
    }
  }
}

int main()
{
  scanf("%d", &n);

  for (int i = 0; i < n; i++)
  {
    scanf("%d", &arr[i]);
  }
  wiggly();

  for (int i = 0; i < n; i++)
  {
    printf("%d ", arr[i]);
  }

  return 0;
}