#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    const void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(const void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
  List* nueva = (List*) malloc (sizeof(List));
  nueva->head= NULL;
  nueva->tail= NULL;
  nueva->current= NULL;
   
    return nueva;
}

void * firstList(List * list) {
  if (list->head == NULL){
   return NULL;
   }
   list->current = list->head;
   return (void*) list->current-> data;
}

void * nextList(List * list) {
  if (list == NULL){return NULL;}
  if (list->current == NULL || list->current->next == NULL) {return NULL;}
  list->current = list->current->next;
    return (void*) list-> current-> data;
}

void * lastList(List * list) {
  if (list->tail == NULL){
    return NULL;
    }
   list->current = list->tail;
   return (void*) list->current-> data;
}

void * prevList(List * list) {
  if (list == NULL){return NULL;}
  if (list->current == NULL || list->current->prev == NULL){return NULL;}
  list->current = list->current->prev;
    return (void*) list-> current-> data;
}

void pushFront(List * list, const void * data) {
  Node* p = createNode(data);
  if (list->head){
    list->head->prev = p;
    p->next = list->head;
  }
  if (list->tail == NULL) {
    list->tail = p;
  }
  list->head=p;
  
} 

void pushBack(List * list, const void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, const void * data) {
  Node* p = createNode(data);
  if (!list->current){
    list->head = p;
    list->tail = p;
    list->current = p;  
  }
  else if (list->current == list->tail){
    p->prev = list->current;
    list->current->next = p;
    list->tail = p;
    list->current = p;
  
  }
  else{
    p->prev = list->current;
    Node* aux = list->current->next;
    list->current->next = p;
    p->next=aux;
    aux->prev=p;
    list->current = p;

  }

  
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
  const void * p = list -> current -> data;
  Node* aux;
  if (list-> current == list->head){
    aux = list->current->next;
    aux->prev = NULL;
    list->head = aux;
    free(list->current);
    list->current = aux;
  }
  else if(list->current == list->tail){
    aux = list->current->prev;
    aux->next = NULL;
    list->tail = aux;
    free(list->current);
    list->current=aux;
  }
  else{
    aux = list->current->prev;
    aux->next = list->current->next;
    aux = list->current->prev;
    free(list->current);
    list->current = aux;
    }

    return (void*)p;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}