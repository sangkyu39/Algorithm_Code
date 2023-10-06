#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap (int *x, int *y){
  int tmp = *x;
  *x = *y;
  *y = tmp;
}

int main() {
  int n;
  int *arr;
  scanf("%d",&n);
  
  arr = (int *)calloc(n, sizeof(int));

  for (int i = 0;i < n;i++){
    scanf("%d",&arr[i]);
  }

  int *max = arr;
  for (int i = 0;i < n;i++){
    max = arr + i;
    for (int j = i;j > 0;j--){
      if (arr[j - 1] > arr[j]){
        swap(arr + j, arr + j - 1);
      }
    }
    
  }

  for (int i = 0;i < n;i++){
    printf(" %d",arr[i]);
  }
  
}