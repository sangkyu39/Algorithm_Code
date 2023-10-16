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

// 상향식 힙 생성시 필요 함수
void downHeap(int idx);
void printHeap();
void rBuildHeap(int idx);
void BuildHeap();

int main()
{

  scanf("%d", &cnt);

  for (int i = 1; i <= cnt; i++)
  {
    scanf("%d", &H[i]);
  }
  /* 리프 노드부터 루트노드 순으로 하나씩 downHeap*/
  /* downHeap은 해당 노드를 기준으로 자식노드 중에서만 위치를 찾음 */
  /* -> 아래부터 하나씩 올바른 위치에 정렬 */
  rBuildHeap(1);

  printHeap();

  return 0;
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

/// @brief 재귀적 상향식 힙생성
/// @param idx
void rBuildHeap(int idx)
{
  // 리프 노드인 경우 종료
  if (idx > cnt)
  {
    return;
  }
  // 왼쪽, 오른쪽 자식 노드 호출
  rBuildHeap(2 * idx);
  rBuildHeap(2 * idx + 1);
  downHeap(idx); // 정렬된 위치로 이동
}

/// @brief 비재귀적 상향식 힙생성
void BuildHeap()
{
  for (int i = cnt / 2; i >= 1; i--)
  {
    downHeap(i);
  }
}

void printHeap()
{
  for (int i = 0; i < cnt; i++)
    printf("%d ", H[i]);
  printf("\n");
}