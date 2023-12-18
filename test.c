#include <stdio.h>
#include <stdlib.h>

typedef struct __Node
{
  int key, height;
  struct __Node *parent, *left, *right;
} Node;

Node *root;
int isExternal(Node *node)
{
  return !(node->left || node->right);
}

int isInternal(Node *node)
{
  return (node->left || node->right);
}

Node *treeSearch(Node *node, int key);
void insertItem(int key);
void expandExternal(Node *node, int key);
int findElement(int key);

void print();
void preOrder();

int removeElement(int key);
Node *redeucExternal(Node *child);
Node *inOrderSucc(Node *node);
Node *findSibling(Node *node);

void searchAndFixAfterRemoval(Node *node);

void searchAndFixAfterInsertion(Node *node);
int updateHeight(Node *node);
int isBalanced(Node *node);
Node *restructure(Node *x, Node *y, Node *z);
void setABC(Node *x, Node *y, Node *z, Node *ABC[3], Node *subT[4]);

int main()
{
  root = (Node *)calloc(1, sizeof(Node));

  char cmd;
  int key;

  while (1)
  {
    scanf("%c", &cmd);

    if (cmd == 'i')
    {
      scanf("%d", &key);
      insertItem(key);
    }
    else if (cmd == 's')
    {
      scanf("%d", &key);
      if (key == findElement(key))
        printf("%d\n", key);
      else
        printf("X\n");
    }
    else if (cmd == 'd')
    {
      scanf("%d", &key);
      if (key == removeElement(key))
        printf("%d\n", key);
      else
        printf("X\n");
    }
    else if (cmd == 'p')
    {
      print();
    }
    else if (cmd == 'q')
      break;
    getchar();
  }
  return 0;
}

// print Node
void print()
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

int findElement(int key)
{
  Node *node = treeSearch(root, key);
  if (isExternal(node))
    return key - 1;
  else
    return key;
}
Node *treeSearch(Node *node, int key)
{
  if (isExternal(node))
    return node;
  if (node->key == key)
    return node;
  else if (node->key < key)
    return treeSearch(node->right, key);
  else
    return treeSearch(node->left, key);
}

void insertItem(int key)
{
  Node *node = treeSearch(root, key);
  if (isInternal(node))
    return;
  expandExternal(node, key);
  searchAndFixAfterInsertion(node);
}

void expandExternal(Node *node, int key)
{
  node->key = key;
  node->height = 1;
  node->left = (Node *)calloc(1, sizeof(Node));
  node->left->parent = node;
  node->right = (Node *)calloc(1, sizeof(Node));
  node->right->parent = node;
}

void searchAndFixAfterInsertion(Node *node)
{
  if (node->parent == NULL)
    return;
  Node *z = node->parent, *y, *x;

  while (updateHeight(z) && isBalanced(z))
  {
    if (z->parent == NULL)
      return;
    z = z->parent;
  }

  if (isBalanced(z))
  {
    return;
  }

  y = (z->left->height > z->right->height) ? z->left : z->right;
  x = (y->left->height > y->right->height) ? y->left : y->right;

  Node *mid = restructure(x, y, z);
  if (mid->parent == NULL)
    root = mid;
}

int isBalanced(Node *node)
{
  int diff = node->left->height - node->right->height;
  if (-1 <= diff && diff <= 1)
    return 1;
  else
    return 0;
}

int updateHeight(Node *node)
{
  int leftH = node->left->height;
  int rightH = node->right->height;
  int newH = (leftH > rightH) ? leftH + 1 : rightH + 1;
  if (newH != node->height)
  {
    node->height = newH;
    return 1;
  }
  else
  {
    return 0;
  }
}

Node *restructure(Node *x, Node *y, Node *z)
{
  Node *subT[4], *ABC[3];
  setABC(x, y, z, subT, ABC);
  Node *mid = ABC[1], *left = ABC[0], *right = ABC[2];
  Node *zParent = z->parent;
  mid->parent = zParent;

  if (zParent == NULL)
    mid->parent = NULL;
  else if (zParent->left == z)
  {
    zParent->left = mid;
  }
  else if (zParent->right == z)
  {
    zParent->right = mid;
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
  else
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

int removeElement(int key)
{
  Node *node = treeSearch(root, key);
  if (isExternal(node))
    return key - 1;
  Node *child = node->left;
  Node *sChild;
  if (isInternal(child))
    child = node->right;
  if (isExternal(child))
    sChild = redeucExternal(child);
  else
  {
    Node *new = inOrderSucc(node);
    node->key = new->key;
    child = new->left;
    sChild = redeucExternal(new);
  }
  searchAndFixAfterRemoval(sChild);
  return key;
}

Node *inOrderSucc(Node *node)
{
  node = node->right;
  while (isInternal(node->left))
  {
    node = node->left;
  }
  return node;
}

Node *findSibling(Node *node)
{
  if (node == root)
  {
    return NULL;
  }
  else
  {
    return (node->parent->left == node) ? node->parent->right : node->parent->left;
  }
}

Node *redeucExternal(Node *child)
{
  Node *parent = child->parent;
  Node *sChild = findSibling(child);
  if (parent == root)
  {
    root = sChild;
    if (sChild)
      sChild->parent = NULL;
  }
  else
  {
    sChild->parent = parent->parent;
    if (parent = parent->parent->left)
    {
      parent->parent->left = sChild;
    }
    else
    {
      parent->parent->right = sChild;
    }
  }
}

void searchAndFixAfterRemoval(Node *node)
{
  if (node == root)
    return;
  Node *z = node->parent;
  while (updateHeight(z) && isBalanced(z))
  {
    if (z->parent == NULL)
    {
      return;
    }
    z = z->parent;
  }

  if (isBalanced(z))
  {
    return;
  }
  Node *y, *x;

  y = (z->left->height > z->right->height) ? z->left : z->right;
  x = (y->left->height > y->right->height) ? y->left : y->right;

  Node *mid = restructure(x, y, z);
  if (mid->parent == NULL)
    root = mid;
  else
    searchAndFixAfterRemoval(mid);
}