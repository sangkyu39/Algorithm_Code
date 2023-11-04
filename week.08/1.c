#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define True 1
#define False 0

typedef struct __Node
{
  int key;
  struct __Node *parent, *leftChild, *rightChild;
} Node;

Node *getNode();
// 노드 상태 확인
int isExternal(Node *node);
int isInternal(Node *node);

Node *treeSearch(Node *root, int key);
void expandExternal(Node *node, int key);

void insertItem(Node *root, int key);
int findElement(Node *root, int key);

int removeElement(Node **root, int key);
void reduceExternal(Node **root, Node *child);
Node *inOrderSucc(Node *node);

// 출력
void print(Node *root);
void preOrder(Node *node);

int main()
{
  Node *root = getNode(NULL);
  char op;
  int key;

  while (1)
  {
    scanf("%c", &op);
    if (op == 'q')
      break;
    else if (op == 'p')
      print(root);
    else
    {
      scanf("%d", &key);

      if (op == 's')
      {
        if (findElement(root, key) == key)
          printf("%d\n", key);
        else
          printf("X\n");
      }
      else if (op == 'd')
      {
        int element = removeElement(&root, key);
        if (key == element)
        {
          printf("%d\n", key);
        }
        else
          printf("X\n");
      }
      else if (op == 'i')
      {
        insertItem(root, key);
      }
    }
  }
}

Node *getNode(Node *parent)
{
  Node *node = (Node *)calloc(1, sizeof(Node));
  node->parent = parent;
  return node;
}

int isExternal(Node *node)
{
  return (node->leftChild == NULL && node->rightChild == NULL);
}

int isInternal(Node *node)
{
  return (node->leftChild || node->rightChild);
}

Node *treeSearch(Node *node, int key)
{
  if (isExternal(node))
    return node;
  if (key == node->key)
    return node;
  else if (key < node->key)
    return treeSearch(node->leftChild, key);
  else if (key > node->key)
    return treeSearch(node->rightChild, key);
}

void insertItem(Node *root, int key)
{
  Node *node = treeSearch(root, key);
  if (isInternal(node))
    return;
  expandExternal(node, key);
}

int findElement(Node *root, int key)
{
  Node *node = treeSearch(root, key);
  if (isExternal(node))
    return key - 1;
  else
    return node->key;
}

void expandExternal(Node *node, int key)
{
  node->key = key;
  node->leftChild = getNode(node);
  node->rightChild = getNode(node);
}

int removeElement(Node **root, int key)
{
  Node *node = treeSearch(*root, key);

  if (isExternal(node))
    return key - 1;

  Node *child = node->leftChild;

  if (isInternal(child))
    child = node->rightChild;

  if (isExternal(child))
    reduceExternal(root, child);
  else
  {
    Node *y = inOrderSucc(node);
    child = y->leftChild;
    node->key = y->key;
    reduceExternal(root, child);
  }

  return key;
}

Node *inOrderSucc(Node *node)
{
  node = node->rightChild;
  while (isInternal(node->leftChild))
  {
    node = node->leftChild;
  }
  return node;
}

Node *sibling(Node *node)
{
  if (node->parent == NULL)
    return NULL;
  if (node->parent->leftChild == node)
    return node->parent->rightChild;
  return node->parent->leftChild;
}

void reduceExternal(Node **root, Node *child)
{
  Node *parent = child->parent;
  Node *siblingNode = sibling(child);
  if (parent == (*root))
  {
    (*root) = siblingNode;
    siblingNode->parent = NULL;
  }
  else
  {
    Node *node = parent->parent;
    siblingNode->parent = node;
    if (parent == node->leftChild)
    {
      node->leftChild = siblingNode;
    }
    else
    {
      node->rightChild = siblingNode;
    }
  }
}

void print(Node *root)
{
  preOrder(root);
  printf("\n");
}

void preOrder(Node *node)
{
  if (isExternal(node))
  {
    return;
  }
  printf(" %d", node->key);
  preOrder(node->leftChild);
  preOrder(node->rightChild);
}