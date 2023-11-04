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

void init(List *list, Node *head, int size);
void push(List *list, int data);
int pop(List *list);
int peek(List *list);
void print(List *list);

void mergeSort(List *list);
void merge(List *list, List *list2);
void mgPartition(List *list, List *list2, int size);

Node *getNode();

int main()
{
  List list;
  int size = 0;
  scanf("%d", &size);
  init(&list, NULL, 0);

  for (int i = 0; i < size; i++)
  {
    int data;
    scanf("%d", &data);
    push(&list, data);
  }

  mergeSort(&list);

  print(&list);
}

void print(List *list)
{
  Node *node = list->head;
  for (int i = 0; i < list->size; i++)
  {
    printf("%d ", node->data);
    node = node->next;
  }
  printf("\n");
}

Node *getNode()
{
  return (Node *)calloc(1, sizeof(Node));
}

void init(List *list, Node *head, int size)
{
  list->head = head;
  list->size = size;
}

void push(List *list, int data)
{
  Node *node = getNode();
  node->data = data;

  list->size += 1;

  if (list->head == NULL)
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

int pop(List *list)
{
  int data = list->head->data;
  list->head = list->head->next;
  list->size -= 1;
  return data;
}

int peek(List *list)
{
  return list->head->data;
}

void mergeSort(List *list)
{
  // mergeSort 함수 재귀 조건 주의 <2개 이상 들어있을 때만 재귀>
  if (list->size > 1)
  {
    List list2;
    mgPartition(list, &list2, list->size);
    mergeSort(list);
    mergeSort(&list2);
    merge(list, &list2);
  }
}

void merge(List *list1, List *list2)
{
  List list;
  init(&list, NULL, 0);
  while (list1->size && list2->size)
  {
    if (peek(list1) < peek(list2))
    {
      push(&list, pop(list1));
    }
    else
    {
      push(&list, pop(list2));
    }
  }
  while (list1->size)
  {
    push(&list, pop(list1));
  }
  while (list2->size)
  {
    push(&list, pop(list2));
  }
  list1->head = list.head;
  list1->size = list.size;
}

void mgPartition(List *list, List *list2, int size)
{
  int k = size / 2;
  list->size = k;

  Node *back = list->head;

  for (int i = 0; i < k - 1; i++)
  {
    back = back->next;
  }

  init(list2, back->next, size - k);
  back->next = NULL;
}