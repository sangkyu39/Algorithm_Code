#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void swap (int *x, int *y) { 
  int tmp = *x;
  *x = *y;
  *y = tmp;
}

/// @brief a[left] ~ a[right]를 힙으로 만드는 함수 
/// @param a  배열
/// @param left 
/// @param right 
void downHeap (int a[], int left, int right) {
  int tmp = a[left];
  int child;
  int parent;

  for (parent = left; parent < (right + 1) /  2;parent = child) {
    int cl = parent * 2 + 1;
    int cr = cl + 1;
    child = (cr <= right && a[cr] > a[cl]) ? cr : cl;
    
    if (tmp >= a[child]) {
      break;
    }
    a[parent] = a[child];
  }
  a[parent] = tmp;
}

void heapSort (int *a, int n) {
  for (int i = (n - 1) / 2;i >= 0;i--) {
    downHeap(a, i, n - 1);
  }
  for (int i = n - 1;i > 0;i--) {
    swap(a, a + i);
    downHeap(a, 0, i - 1);
  }
}

int main() {
  int *x;
  int cnt;

  printf("Heap Sort\n");
  printf("Count :");
  scanf("%d", &cnt);
  x = calloc(cnt, sizeof(int));

  for (int i = 0;i < cnt;i++) {
    printf("x[%d] :", i);
    scanf("%d", x + i);
  }

  heapSort(x, cnt);
  printf("Sorted\n");
  for (int i = 0 ;i < cnt;i++) {
    printf("x[%d] = %d\n",i, x[i]);
  }

  free(x);

  return 0;
}