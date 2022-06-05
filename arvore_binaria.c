#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
  int id;

  struct Node *left;
  struct Node *right;
} Node;

Node *root = NULL;
int len = 0;

Node *searchNode(int id, Node *aux)
{
  if (aux == NULL)
    return NULL;

  if (aux->id == id)
    return aux;
  else if (aux->id > id)
  {
    if (aux->left != NULL)
      return searchNode(id, aux->left);
    else
      return aux;
  }
  else if (aux->id < id)
  {
    if (aux->right != NULL)
      return searchNode(id, aux->right);
    else
      return aux;
  }

  return NULL;
}

void addNode(int id)
{
  Node *aux = searchNode(id, root);

  if (aux != NULL && aux->id == id)
    printf("Não foi possivel fazer a insercao\n");
  else
  {
    Node *novo = malloc(sizeof(Node));
    novo->id = id;
    novo->right = NULL;
    novo->left = NULL;

    if (aux == NULL)
      root = novo;
    else
    {
      if (aux->id > id)
        aux->left = novo;
      else
        aux->right = novo;
    }
  }
}
Node *searchDad(int id)
{
  Node *aux = root;
  while (aux->right != NULL && aux->left != NULL)
  {
    if (aux->right != NULL && aux->right->id == id ||
        aux->left != NULL && aux->left->id == id)
      return aux;

    if (id > aux->id)
      aux = aux->right;
    else
      aux = aux->left;
  }

  return aux;
}
Node *gotoHigher(Node *start)
{
  Node *aux = start;
  while (aux->left != NULL)
    aux = aux->left;

  return aux;
}
void removeNode(int id, Node *aux)
{
  Node *toRemove = searchNode(id, aux);
  Node *dad = searchDad(id);

  if (toRemove->right == NULL && toRemove->left == NULL)
  {
    if (dad->right == toRemove)
      dad->right = NULL;
    else
      dad->left = NULL;
  }
  else if (toRemove->right == NULL && toRemove->left != NULL ||
   toRemove->left == NULL && toRemove->right != NULL)
  {
    Node *child = toRemove->right != NULL ? toRemove->right : toRemove->left;

    if (dad->left == toRemove)
      dad->left = child;
    else
      dad->right = child;
  }
  else if (toRemove->right != NULL && toRemove->left != NULL)
  {
    Node *higher = gotoHigher(toRemove->right);

    if (dad->left == toRemove)
      dad->left = higher;
    else
      dad->right = higher;

    higher->right = toRemove->right != higher ? toRemove->right : NULL;
    higher->left = toRemove->left != higher ? toRemove->left : NULL;
  }

  free(toRemove);
}

void printPreOrder(Node *aux)
{
  printf("%d\n", aux->id);

  if (aux->left != NULL)
    printPreOrder(aux->left);
  if (aux->right != NULL)
    printPreOrder(aux->right);
}

void PrintInOrder(Node *aux)
{
  if (aux->left != NULL)
    PrintInOrder(aux->left);

  printf("%d\n", aux->id);

  if (aux->right != NULL)
    PrintInOrder(aux->right);
}

void PrintPosOrder(Node *aux)
{
  if (aux->left != NULL)
    PrintPosOrder(aux->left);
  if (aux->right != NULL)
    PrintPosOrder(aux->right);

  printf("%d\n", aux->id);
}

int main()
{
  addNode(10);
  addNode(5);
  addNode(3);
  addNode(8);
  addNode(13);
  addNode(11);

  removeNode(3, root);

  PrintInOrder(root);
  return 0;
}
