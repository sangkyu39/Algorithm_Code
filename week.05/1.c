#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct __Node
{
  int data;
  struct __Node *next;
} Node;

typedef struct __List
{
  Node *head;
  int size;
} List;

Node *getNode()
{
  return (Node *)calloc(1, sizeof(Node));
}

void push(List *list, int data);
int pop(List *list);
void init(List *list, Node *head, int size);
int get(List *list);
void print(List *list);

List *mergeSort(List *list);
void partition(List *list1, List *list2, List *list);
List *merge(List *list1, List *list2);

int main()
{
  List *list = (List *)calloc(1, sizeof(List));
  init(list, NULL, 0);

  int cnt;

  scanf("%d", &cnt);

  for (int i = 0; i < cnt; i++)
  {
    int data;
    scanf("%d", &data);
    push(list, data);
  }

  list = mergeSort(list);
  print(list);

  return 0;
}

void init(List *list, Node *node, int size)
{
  list->head = node;
  list->size = size;
}

void print(List *list)
{
  for (Node *node = list->head; node; node = node->next)
  {
    printf("%d ", node->data);
  }
  printf("\n");
}

void push(List *list, int data)
{
  Node *node = getNode();
  node->data = data;

  list->size += 1;
  if (!list->head)
  {
    list->head = node;
  }
  else
  {
    Node *back = list->head;
    while (back->next != NULL)
    {
      back = back->next;
    }
    back->next = node;
  }
}

int get(List *list)
{
  if (list->head)
  {
    return list->head->data;
  }
  return -1;
}

int pop(List *list)
{
  Node *node = list->head;
  if (node == NULL)
  {
    return 0;
  }
  int data = node->data;
  list->size -= 1;

  list->head = node->next;
  free(node);

  return data;
}

void partition(List *list1, List *list2, List *list)
{
  Node *node = list->head;
  int k = list->size / 2;

  init(list1, list->head, k);

  for (int i = 0; i < k - 1; i++)
  {
    node = node->next;
  }

  init(list2, node->next, list->size - k);
  node->next = NULL;
}
/* list1,과 list2에 함수 내부에서 할당하는 경우 해당 함수의 주소로써 사용한 것이 아닌 변수로써 사용한 것임으로 오류 발생*/
List *mergeSort(List *list)
{

  if (list->size > 1)
  {
    List *list1, *list2;
    list1 = (List *)calloc(1, sizeof(List));
    list2 = (List *)calloc(1, sizeof(List));
    partition(list1, list2, list);
    list1 = mergeSort(list1);
    list2 = mergeSort(list2);
    list = merge(list1, list2);
  }
  return list;
}

List *merge(List *list1, List *list2)
{
  List *list = (List *)calloc(1, sizeof(List));
  init(list, NULL, 0);

  while (list1->size && list2->size)
  {
    if (get(list1) <= get(list2))
    {
      push(list, pop(list1));
    }
    else
    {
      push(list, pop(list2));
    }
  }

  while (list1->size)
  {
    push(list, pop(list1));
  }
  while (list2->size)
  {
    push(list, pop(list2));
  }
  return list;
}
