#include <stdio.h>
#include <stdlib.h>

int *arr;

int findElement(int key, int size);

int main()
{
  int size, key;

  scanf("%d %d", &size, &key);

  arr = (int*)calloc(size, sizeof(int));
  
  for(int i = 0;i < size;i++) {
    scanf("%d", &arr[i]); 
  }

  int index = findElement(key, size);
  
  printf(" %d", index);

  free(arr);

  return 0;
}

int findElement(int key, int size){
  int left = 0, right = size - 1;
  
  while (left <= right) {
    int mid = (left + right) / 2;

    if (arr[mid] == key)
      return mid;
    else if (arr[mid] < key) {
      left = mid + 1;
    }
    else if (arr[mid] > key) {
      right = mid - 1;
    }
  }
  return left;
}