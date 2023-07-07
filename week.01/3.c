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
  for (int i = n - 1;i >= 0;i--){
    max = arr + i;
    int j;
    for (j = 0;j < i;j++){
      if (*max < arr[j]){
        max = arr + j;
      }
    }
    swap(max, arr + i);
    
  }

  for (int i = 0;i < n;i++){
    printf(" %d",arr[i]);
  }
  
}