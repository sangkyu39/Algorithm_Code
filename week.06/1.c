#include <stdio.h>
#include <stdlib.h>

int *arr;

int rFindElement(int key, int left, int right);

int main()
{
  int size, key;

  scanf("%d %d", &size, &key);

  arr = (int*)calloc(size, sizeof(int));
  
  for(int i = 0;i < size;i++) {
    scanf("%d", &arr[i]); 
  }

  int index = rFindElement(key, 0, size - 1);
  
  printf(" %d", index);

  free(arr);

  return 0;
}

int rFindElement(int key, int left, int right){
  if(left > right)
    return right;
  int mid = (left + right) / 2;
  
  if(arr[mid] == key)
    return mid;
  else if (arr[mid] < key)
    return rFindElement(key, mid + 1, right);
  else if (arr[mid] > key)
    return rFindElement(key, left, mid - 1);
}