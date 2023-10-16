#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define swap(a, b) \
  do               \
  {                \
    int tmp = a;   \
    a = b;         \
    b = tmp;       \
  } while (0)

int H[100], cnt = 0;

// 삽입식 힙 생성시 필요 함수
void insertItem(int key);
int removeMax();
void upHeap(int idx);
void downHeap(int idx);
void printHeap();

int main()
{
  char cmd;
  int key = 0;

  while (1)
  {
    scanf("%c", &cmd);

    // finish
    if (cmd == 'q')
    {
      break;
    }
    // 키 삽입
    else if (cmd == 'i')
    {
      scanf("%d", &key);
      getchar();
      insertItem(key);
      printf("0\n"); //
    }
    // 키 삭제
    else if (cmd == 'd')
    {
      printf("%d\n", removeMax());
    }
    // 인쇄
    else if (cmd == 'p')
    {
      printHeap();
    }
  }
}

/// @brief 키 삽입
/// @param key
void insertItem(int key)
{
  // 키 개수 증가 및 해당 위치 키 삽입 ( H[0]은 비워둠 )
  cnt += 1;
  H[cnt] = key;
  upHeap(cnt); // 삽입한 키 위치 정렬
}

/// @brief 해당 함수에 처음 들어온 key를 정렬된 위치로 이동 시킴
/* 부모 노드와 비교해서 이동 */
/// @param idx
void upHeap(int idx)
{
  // 루트노드에 접근한 경우 종료
  if (idx == 1)
  {
    return;
  }
  // 자신의 부모 노드가 자신보다 작은 경우 바꾸기
  else if (H[idx] > H[idx / 2])
  {
    swap(H[idx], H[idx / 2]);
    upHeap(idx / 2); // 변경 후 다시 정렬
  }
}

/// @brief 루트 노드의 값을 반환 (가장 큰 값)
/// @return
int removeMax()
{
  int key = H[1];
  H[1] = H[cnt--]; // last node 값을 루트 노드와 변경
  downHeap(1);     // 바뀐 last node 값 정렬
  return key;
}

/// @brief 해당 함수에 처음 들어온 keey를 정렬된 위치로 이동 시킴
/* 자식 노드와 비교해서 이동 */
/// @param idx
void downHeap(int idx)
{
  int left = idx * 2;
  int right = idx * 2 + 1;

  // 자식 노드가 없는 경우
  if (left > cnt)
    return;

  int biggerIdx = left;

  // 오른쪽 자식 노드가 있는 경우 -> 값이 더 큰 자식 노드 선택
  if (right <= cnt)
    biggerIdx = (H[right] > H[left]) ? right : left;

  // 자신의 자식 노드가 자신보다 큰 경우 바꾸기
  if (H[biggerIdx] > H[idx])
  {
    swap(H[biggerIdx], H[idx]);
    downHeap(biggerIdx); // 변경 후 다시 정렬
  }
}

void printHeap()
{
  for (int i = 0; i < cnt; i++)
    printf("%d ", H[i]);
  printf("\n");
}