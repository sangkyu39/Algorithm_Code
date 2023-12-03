#include <stdio.h>
#include <stdlib.h>
typedef struct __Queue
{
  int arr[101];
  int head, tail;
} Queue;

typedef struct __Edge
{
  int to;
  struct __Edge *next;
} Edge;

// 선언시 null로 초기화 됨
int N, M;
int in[100];
char vertices[100];
Edge *edges[100];
Queue q;

// O(n) -> 최대 100번
int getIndex(char ch)
{
  for (int i = 0; i < N; i++)
  {
    if (vertices[i] == ch)
      return i;
  }
}

Edge *getEdge(int to)
{
  Edge *ret = (Edge *)calloc(1, sizeof(Edge));
  ret->to = to;
  return ret;
}

// n < 100, m < 1000
// isEmpty(), push(), pop() - Queue 사용시  사용 함수

const int FAIL = -1, SUCCESS = 1e8;

int qIsEmpty()
{
  if (q.head == q.tail)
    return SUCCESS;
  return FAIL;
}

int qPush(int elem)
{
  q.arr[q.tail] = elem;
  q.tail = (q.tail + 1) % 101;

  return SUCCESS;
}

int qPop()
{
  int ret = q.arr[q.head];
  q.head = (q.head + 1) % 101;

  return ret;
}

int main()
{
  scanf("%d", &N);
  getchar();

  for (int i = 0; i < N; i++)
  {
    scanf("%c", vertices[i]);
    getchar();
  }

  scanf("%d", &M);
  getchar();

  char cfrom, cto;

  // 1000 * 2  *  100 (시간복잡도) 1초 == 1억번
  for (int i = 0, from, to; i < M; i++)
  {
    scanf("%c %c", &cfrom, &cto);
    from = getIndex(cfrom);
    to = getIndex(cto);

    Edge *tmp = getEdge(to);
    tmp->next = edges[from];
    edges[from] = tmp;

    in[to]++;
  }

  for (int i = 0; i < N; i++)
  {
    if (in[i] == 0)
      qPush(i);
  }
  int output[100], outIdx = 0;

  while (qIsEmpty() != SUCCESS)
  {
    int now = qPop();
    output[outIdx++] = now;

    Edge *cur = edges[now];
    while (cur != NULL)
    {
      in[cur->to]--;
      if (in[cur->to] == 0)
        qPush(cur->to);
      cur = cur->next;
    }
  }

  if (outIdx == N)
  {
    for (int i = 0; i < N; i++)
    {
      printf(" %c", vertices[output[i]]);
    }
  }
  else
  {
    puts("0");
  }
}