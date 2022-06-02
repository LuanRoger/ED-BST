#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int id;

  struct Node *esq;
  struct Node *dir;
} Node;

Node *root = NULL;
int len = 0;

Node* searchNode(int id, Node* aux){
    if(aux != NULL){   
        if(aux->id == id){
            return aux;
        }else if(aux->id > id){
            if(aux->esq != NULL){
                return searchNode(id, aux->esq);
            }else{
                return aux;
            }
        }else if(aux->id < id){
            if(aux->dir != NULL){
                return searchNode(id, aux->dir);
            
            }else{
                return aux;
            }
        }
    }else{
        return NULL;
    }
}

void addNode(int id) {
    Node *aux = searchNode(id, root); 
    
    if(aux != NULL && aux->id == id){
        printf("Não foi possivel fazer a insercao\n");
    }else{
        Node* novo = malloc(sizeof(Node));
        novo->id = id;
        novo->dir = NULL;
        novo->esq = NULL;

        if(aux == NULL){
            root = novo;

        }else{
            if(aux->id > id){
                aux->esq = novo;

            }else{
                aux->dir = novo;
            }
        }
    }
}
Node* searchDad(int id) {
  Node *aux = root;
  while (aux->dir != NULL && aux->esq != NULL)
  {
    if(aux->dir != NULL && aux->dir->id == id ||
     aux->esq != NULL && aux->esq->id == id)
      return aux;

    if(id > aux->id)
      aux = aux->dir;
    else aux = aux->esq;
  }

  return aux;
}
Node* gotoHigher(Node *start) {
  Node *aux = start;
  while (aux->esq != NULL)
    aux = aux->esq;
  
  return aux;
}
void removeNode(int id, Node *aux) {
  Node *toRemove = searchNode(id, aux);
  Node *dad = searchDad(id);

  if(toRemove->dir == NULL && toRemove->esq == NULL) {
    if(dad->dir == toRemove) dad->dir = NULL;
    else dad->esq = NULL;
  }
  else if(toRemove->dir == NULL && toRemove->esq != NULL || toRemove->esq == NULL && toRemove->dir != NULL) {
    Node *child = toRemove->dir != NULL ? toRemove->dir : toRemove->esq;

    if(dad->esq == toRemove)
      dad->esq = child;
    else dad->dir = child;
  }
  else if(toRemove->dir != NULL && toRemove->esq != NULL) {
    Node *higher = gotoHigher(toRemove->dir);
    
    if(dad->esq == toRemove)
      dad->esq = higher;
    else dad->dir = higher;

    higher->dir = toRemove->dir != higher ? toRemove->dir : NULL;
    higher->esq = toRemove->esq != higher ? toRemove->esq : NULL;
  }

  free(toRemove);
}

void printPreOrder(Node *aux) {
  printf("%d\n", aux->id);
  if (aux->esq != NULL) {
    printPreOrder(aux->esq);
  }
  if (aux->dir != NULL) {
    printPreOrder(aux->dir);
  }
}

void PrintInOrder(Node *aux) {
  if (aux->esq != NULL) {
    PrintInOrder(aux->esq);
  }
  printf("%d\n", aux->id);
  if (aux->dir != NULL) {
    PrintInOrder(aux->dir);
  }
}

void PrintPosOrder(Node *aux) {
  if (aux->esq != NULL) {
    PrintPosOrder(aux->esq);
  }
  if (aux->dir != NULL) {
    PrintPosOrder(aux->dir);
  }
  printf("%d\n", aux->id);
}

int main() {
  addNode(10);
  addNode(5);
  addNode(3);
  addNode(8);
  addNode(13);
  addNode(11);

  removeNode(13, root);

  printPreOrder(root);
  return 0;
}
