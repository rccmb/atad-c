/**
 * @file setArrayList.c
 * 
 * @brief Provides an implementation of the ADT Set with an array list
 * as the underlying data structure.
 * 
 * @author Rodrigo Baptista (202200217@estudantes.ips.pt)
 * @bug No known bugs.
 */

#include <stdio.h>
#include <stdlib.h>

#include "set.h"

#define INITIAL_CAPACITY 20

typedef struct setImpl {
  SetElem *elements;
  int size;
  int capacity;
} SetImpl;

static bool ensureCapacity(PtSet set);

PtSet setCreate() {
  PtSet set = (PtSet) malloc(sizeof(SetImpl));
  if(set == NULL) return NULL;

  set->elements = (SetElem*) calloc(INITIAL_CAPACITY, sizeof(SetElem));

  if(set->elements == NULL) {
    free(set);
    return NULL;
  }

  set->size = 0;
  set->capacity = INITIAL_CAPACITY;

  return set;
}

int setAdd(PtSet set, SetElem elem) {
  // TODO
}

int setRemove(PtSet set, SetElem elem) {
  // TODO
}

bool setContains(PtSet set, SetElem elem) {
  // TODO
}

int setSize(PtSet set, int *ptSize) {
  // TODO
}

bool setSubset(PtSet set1, PtSet set2) {
  // TODO
}

bool setIsEmpty(PtSet set) {
  // TODO
}

int setClear(PtSet set) {
  // TODO
}

SetElem* setValues(PtSet set) {
  // TODO
}

void setPrint(PtSet set) {
  // TODO
}

int setDestroy(PtSet *ptSet) {
  // TODO
}

static bool ensureCapacity(PtSet set) {
  if(set->size == set->capacity) {
    int newCap = set->capacity * 2;
    SetElem *newElems = (SetElem*) realloc(set->elements, sizeof(SetElem) * newCap);

    if(newElems == NULL) return false;

    set->elements = newElems;
    set->capacity = newCap;
  }

  return true;
}