#include <stdio.h>
#include <stdlib.h>

#define swap(a, b) do{int tmp = a; a = b; b = a;} while(0)

int n;
int heap[100];

int getMin();
void downHeap(int idx);

int main()
{
  scanf("%d", &n);

  for (int i = 0; i < n; i++)
  {
    scanf("%d", &heap[i]);
  }
  
  for (int i = n / 2;i >= 1;--i)
  {
    downHeap(i);
  }

  while (n > 0) {
    printf("%d ", getMin());
  }
}

void downHeap(int idx)
{
  int left = idx * 2;
  int right = idx * 2 + 1;

  if (left > n)
    return;
  
  int biggerIdx = left;

  if (right <= n){
    biggerIdx = (heap[right] > heap[left]) ? right : left;
  }

  if (heap[biggerIdx] > heap[idx]){
    swap(heap[idx], heap[biggerIdx]);
    downHeap(biggerIdx);
  }
}

int getMin() {
  int ret = heap[1];

  heap[1] = heap[n--];
  downHeap(1);

  return ret;
}
