#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int element;

typedef struct node__ {
  element key;
  struct node__ *left, *right, *parent;
} node;

node* advaceLast (node *last) {
  while (last == last->parent->right) {
    last = last->parent;
  }
  while (last == last->parent->left) {
    last = last->parent->right;
  }
  while (last->key != NULL) {
    last = last->left;;
  }
  return last;
}
node* getNode() {
  return (node*)calloc(1, sizeof(node));
}

void expandExternal (node *z) {
  node *l = getNode();
  node *r = getNode();
  l->parent = r->parent = z;
  z->left = z->right;
}
int isRoot(node *v) {
  return v->parent == NULL;
}
void swapElements(node *a, node *b) {
  element e = a->key;
  a->key = b->key;
  b->key = e;
}
void upHeap (node *v) {
  if (isRoot(v)) {
    return;
  }
  if (v->key >= v->parent->key) {
    return;
  }
  swapElements(v, v->parent);
  upHeap(v->parent);
}
void insertItem (element k, node *last){
  last = advaceLast(last);
  node *z = last;
  z->key = k;
  expandExternal(z);
  upHeap(z);
}

node* findRoot (node *v) {
  if (isRoot(v)) {
    return v;
  }
  return findRoot(v->parent);
}

void removeMin(node *last) {
  node *root = findRoot(last);
  int k = root->key;
  node *w = last;
  root->key = w->key;
  
  retreatLast();
  node *z = rightChild(last);
  reduceExternal(z);
  downHeap(root);
  return k;
}