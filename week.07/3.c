#include <stdio.h>
#include <stdlib.h>

typedef struct __Node
{
  int key, height;
  struct __Node *left, *right, *parent;
} Node;

Node *getNode(Node *parent)
{
  Node *node = (Node *)calloc(1, sizeof(Node));
  node->parent = parent;
  return node;
}
int isExternal(Node *node)
{
  return (node->left == NULL && node->right == NULL);
}
int isInternal(Node *node)
{
  return (node->left || node->right);
}

// insert Node
Node *treeSearch(Node *node, int key);
void insertItem(Node **root, int key);
void expandExternal(Node *node, int key);
int findElement(Node *root, int key);
// print Node
void print(Node *root);
void preOrder(Node *node);

// remove Node
int removeElement(Node **root, int key);
Node *reduceExternal(Node **root, Node *child);
Node *inOrderSucc(Node *node);
Node *findSibling(Node *node);
void searchAndFixAfterRemoval(Node **root, Node *node);

// AVL Tree
void searchAndFixAfterInsertion(Node **root, Node *node);
int updateHeight(Node *node);
int isBalanced(Node *node);
Node *findHighChild(Node *node);
Node *restructure(Node *x, Node *y, Node *z);
void setABC(Node *x, Node *y, Node *z, Node *subT[4], Node *ABC[3]);

int main()
{
  Node *root = getNode(NULL);
  char cmd;
  int key;

  while (1)
  {
    scanf("%c", &cmd);

    if (cmd == 'i')
    {
      scanf("%d", &key);
      insertItem(&root, key);
    }
    else if (cmd == 's')
    {
      scanf("%d", &key);
      if (key == findElement(root, key))
        printf("%d\n", key);
      else
        printf("X\n");
    }
    else if (cmd == 'd')
    {
      scanf("%d", &key);
      if (key == removeElement(&root, key))
        printf("%d\n", key);
      else
        printf("X\n");
    }
    else if (cmd == 'p')
    {
      print(root);
    }
    else if (cmd == 'q')
      break;
    getchar();
  }
  return 0;
}

Node *treeSearch(Node *node, int key)
{
  if (isExternal(node))
    return node;
  if (key == node->key)
    return node;
  else if (key < node->key)
    return treeSearch(node->left, key);
  else if (key > node->key)
    return treeSearch(node->right, key);
}
int findElement(Node *root, int key)
{
  Node *node = treeSearch(root, key);
  if (isExternal(node))
    return key - 1;
  else
    return node->key;
}

void insertItem(Node **root, int key)
{
  Node *node = treeSearch(*root, key);
  if (isInternal(node))
    return;
  expandExternal(node, key);
  searchAndFixAfterInsertion(root, node);
}
void expandExternal(Node *node, int key)
{
  node->key = key;
  node->height = 1;
  node->left = getNode(node);
  node->right = getNode(node);
}
void searchAndFixAfterInsertion(Node **root, Node *node)
{
  if (node->parent == NULL)
    return;
  Node *x = NULL, *y = NULL;
  Node *z = node->parent;
  // 노드 높이 추가 및 균형확인
  while (updateHeight(z) && isBalanced(z))
  {
    if (z->parent == NULL)
      return;
    z = z->parent;
  }
  // 정상적으로 균형잡혀있는 경우
  if (isBalanced(z))
    return;
  // 왼쪽 자식의 높이가 더 큰 경우
  if (z->left->height > z->right->height)
    y = z->left;
  // 오른쪽 자식의 높이가 더 큰 경우
  else
    y = z->right;

  // 왼쪽 자식의 높이가 더 큰 경우
  if (y->left->height > y->right->height)
    x = y->left;
  else
    // 오른쪽 자식의 높이가 더 큰 경우
    x = y->right;
  /*
  z - 불균형인 두 자식 노드의 부모 노드
  y - 두 자식 노드 중 더 커서 불균형인 노드
  x - 불균형의 원인이 되는 노드의 부모 노드
  z -> y -> x 순서로 자식노드로 내려감
  */
  Node *mid = restructure(x, y, z);
  if (mid->parent == NULL)
  {
    (*root) = mid;
  }
  return;
}
// 추가된 노드만큼 높이 1 추가
int updateHeight(Node *node)
{
  int leftHeight = node->left->height;
  int rightHeight = node->right->height;
  // 자식 노드 중 더 큰 높이에 1을 더함
  int newHeight = (leftHeight > rightHeight) ? leftHeight + 1 : rightHeight + 1;
  // 높이 주의!!!!
  if (newHeight != node->height)
  {
    node->height = newHeight;
    return 1;
  }
  else
    return 0;
}
// 두 자식 노드의 높이차가 2 이상인 경우 불균형
int isBalanced(Node *node)
{
  int diff = node->left->height - node->right->height;
  if (diff >= -1 && diff <= 1)
    return 1;
  else
    return 0;
}
Node *restructure(Node *x, Node *y, Node *z)
{
  Node *subT[4], *ABC[3];
  setABC(x, y, z, subT, ABC);
  Node *mid = ABC[1], *left = ABC[0], *right = ABC[2];
  Node *zParent = z->parent;

  if (zParent == NULL)
    mid->parent = NULL;
  else if (zParent->left == z)
  {
    zParent->left = mid;
    mid->parent = zParent;
  }
  else if (zParent->right == z)
  {
    zParent->right = mid;
    mid->parent = zParent;
  }

  left->left = subT[0];
  left->right = subT[1];
  subT[0]->parent = subT[1]->parent = left;
  updateHeight(left);

  right->left = subT[2];
  right->right = subT[3];
  subT[2]->parent = subT[3]->parent = right;
  updateHeight(right);

  mid->left = left;
  mid->right = right;
  left->parent = right->parent = mid;
  updateHeight(mid);

  return mid;
}

void setABC(Node *x, Node *y, Node *z, Node *subT[4], Node *ABC[3])
{
  // z < y < x
  if (z->key < y->key && y->key < x->key)
  {
    ABC[0] = z;
    ABC[1] = y;
    ABC[2] = x;
    subT[0] = z->left;
    subT[1] = y->left;
    subT[2] = x->left;
    subT[3] = x->right;
  }
  // z < x < y
  else if (z->key < x->key && x->key < y->key)
  {
    ABC[0] = z;
    ABC[1] = x;
    ABC[2] = y;
    subT[0] = z->left;
    subT[1] = x->left;
    subT[2] = x->right;
    subT[3] = y->right;
  }
  // x < y < z
  else if (x->key < y->key && y->key < z->key)
  {
    ABC[0] = x;
    ABC[1] = y;
    ABC[2] = z;
    subT[0] = x->left;
    subT[1] = x->right;
    subT[2] = y->right;
    subT[3] = z->right;
  }
  // y < x < z
  else if (y->key < x->key && x->key < z->key)
  {
    ABC[0] = y;
    ABC[1] = x;
    ABC[2] = z;
    subT[0] = y->left;
    subT[1] = x->left;
    subT[2] = x->right;
    subT[3] = z->right;
  }
}

// print Node
void print(Node *root)
{
  preOrder(root);
  printf("\n");
}
void preOrder(Node *node)
{
  if (isExternal(node))
    return;
  printf(" %d", node->key);
  preOrder(node->left);
  preOrder(node->right);
}

int removeElement(Node **root, int key)
{
  Node *node = treeSearch(*root, key);

  if (isExternal(node))
    return key - 1;

  Node *child = node->left;
  Node *siblingChild;

  if (isInternal(child))
    child = node->right;
  if (isExternal(child))
    siblingChild = reduceExternal(root, child);
  else
  {
    Node *y = inOrderSucc(node);
    child = y->left;
    node->key = y->key;
    siblingChild = reduceExternal(root, child);
  }
  searchAndFixAfterRemoval(root, siblingChild->parent);
  return key;
}

Node *reduceExternal(Node **root, Node *child)
{
  Node *parent = child->parent;
  Node *siblingChild = findSibling(child);
  if (parent->parent == NULL)
  {
    *root = siblingChild;
    if (siblingChild)
      siblingChild->parent = NULL;
  }
  else
  {
    siblingChild->parent = parent->parent;
    if (parent->parent->left == parent)
      parent->parent->left = siblingChild;
    else
      parent->parent->right = siblingChild;
  }
  return siblingChild;
}

Node *inOrderSucc(Node *node)
{
  node = node->right;

  while (isInternal(node->left))
    node = node->left;
  return node;
}

Node *findSibling(Node *node)
{
  if (node->parent == NULL)
    return NULL;
  if (node->parent->left == node)
    return node->parent->right;
  else
    return node->parent->left;
}

void searchAndFixAfterRemoval(Node **root, Node *node)
{
  Node *x, *y, *z = node;

  while (updateHeight(z) && isBalanced(z))
  {
    if (z->parent == NULL)
      return;
    z = z->parent;
  }
  if (isBalanced(z))
    return;
  // 왼쪽 자식의 높이가 더 큰 경우
  if (z->left->height > z->right->height)
    y = z->left;
  // 오른쪽 자식의 높이가 더 큰 경우
  else
    y = z->right;

  // 왼쪽 자식의 높이가 더 큰 경우
  if (y->left->height > y->right->height)
    x = y->left;
  else if (y->left->height < y->right->height)
    // 오른쪽 자식의 높이가 더 큰 경우
    x = y->right;
  else if (z->left == y)
    x = y->left;
  else
    x = y->right;
  Node *mid = restructure(x, y, z);
  if (mid->parent == NULL)
  {
    *root = mid;
    return;
  }
  searchAndFixAfterRemoval(root, mid->parent);
}