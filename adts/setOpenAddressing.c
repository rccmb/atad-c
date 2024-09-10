/**
 * @file setOpenAddressing.c
 * 
 * @brief ADT Set implementation with hash tables (open addressing) using lazy deletion.
 * 
 * @author Rodrigo Baptista (202200217@estudantes.ips.pt)
 * @bug No known bugs.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "set.h"

#define LOAD_FACTOR_THRESHOLD 0.75

typedef struct setNode {
  SetElem element; // Element present at this node.
  int occupied; // Whether this node is occupied or not.
  int deleted; // Whether this node has been deleted or not.
} SetNode;

typedef struct setImpl {
  SetNode* nodes; // Nodes of the set.
  int size; // Size of the set.
  int deletedCount; // Number of nodes that have been deleted.
  int index; // Determines the capacity (getPrime(index)) and multiplier (getPrime(index - 1)). 
} SetImpl;

static int hashFunction(SetElem elem, int multiplier, int tableSize);

static bool ensureCapacity(PtSet set);

static int findPosition();

static int getPrime(int index);

PtSet setCreate() {
  PtSet set = (PtSet) malloc(sizeof(SetImpl));
  if(set == NULL) return NULL;
  
  SetNode* newNodes = (SetNode*) calloc(getPrime(1), sizeof(SetNode));
  if(newNodes == NULL) return NULL;

  set->nodes = newNodes;
  set->size = 0;
  set->deletedCount = 0;
  set->index = 1;

  return set;
}

int setAdd(PtSet set, SetElem elem) {
  if(set == NULL) return SET_NULL;

  if(!ensureCapacity(set)) return SET_NO_MEMORY;

  int position = findPosition(set, elem);
  if(position == -1) return SET_ERROR;

  int capacity = getPrime(set->index);
  int firstDeletedIndex = -1;
  bool added = false;
  for(int i = 0; i < capacity; i++) {
    if(set->nodes[position].occupied == 0 && set->nodes[position].deleted == 0) {
      if(firstDeletedIndex != -1) {
        position = firstDeletedIndex;
        set->deletedCount--;
      }
      set->nodes[position].element = elem;
      set->nodes[position].occupied = 1;
      set->nodes[position].deleted = 0;
      set->size++;
      added = true;
      break;
    }
    if(set->nodes[position].occupied == 1) {
      if(setElemCompare(set->nodes[position].element, elem) == 0) {
        return SET_DUPLICATE;
      }
    }
    if(set->nodes[position].deleted == 1 && firstDeletedIndex == -1) {
      firstDeletedIndex = position;
    }
    position = (position + 1) % capacity;
  }

  if(added == false) return SET_FULL;
  else return SET_OK;
}

int setRemove(PtSet set, SetElem elem) {
  // TODO
  return 0;
}

bool setContains(PtSet set, SetElem elem) {
  if(set == NULL) return SET_NULL;

  if(!ensureCapacity(set)) return SET_NO_MEMORY;

  int position = findPosition(set, elem);
  if(position == -1) return SET_ERROR;

  int capacity = getPrime(set->index);
  for(int i = 0; i < capacity; i++) {
    if(set->nodes[position].occupied == 0 && set->nodes[position].deleted == 0) return false;
    if(set->nodes[position].occupied == 1 && set->nodes[i].deleted == 0) {
      if(setElemCompare(set->nodes[position].element, elem) == 0) {
        return true;
      }
    }
    position = (position + 1) % capacity;
  }
  
  return false;
}

int setSize(PtSet set, int *ptSize) {
  if(set == NULL) return SET_NULL;

  *ptSize = set->size;

  return SET_OK;
}

int setSubset(PtSet set1, PtSet set2) {
  // TODO
  return 0;
}

bool setIsEmpty(PtSet set) {
  // TODO
  return true;
}

int setClear(PtSet set) {
  // TODO
  return 0;
}

SetElem* setValues(PtSet set) {
  if(set == NULL) return NULL;
  
  SetElem *newValues = (SetElem*) calloc(set->size, sizeof(SetElem));

  int j = 0;
  for(int i = 0; i < getPrime(set->index); i++) {
    if(set->nodes[i].occupied == 1 && set->nodes[i].deleted == 0) {
      newValues[j++] = set->nodes[i].element;
    }
  }

  return newValues;
}

void setPrint(PtSet set) {
  // TODO
  return;
}

int setDestroy(PtSet *ptSet) {
  PtSet set = *ptSet;
  if(set == NULL) return SET_NULL;

  free(set->nodes);
  free(set);

  *ptSet = NULL;

  return SET_OK;
}

static int hashFunction(SetElem elem, int multiplier, int tableSize) {
  int key = setElemHash(elem);
  return (key * multiplier) % tableSize;
}

static bool ensureCapacity(PtSet set) {
  if(set == NULL) return false;
  
  if((double) (set->size + set->deletedCount) / getPrime(set->index) >= LOAD_FACTOR_THRESHOLD) {
    SetNode *newNodes = (SetNode*) calloc(getPrime(set->index + 1), sizeof(SetNode));
    if(newNodes == NULL) return false;

    int oldElementsSize;
    setSize(set, &oldElementsSize);
    SetElem *oldElements = setValues(set);

    free(set->nodes);
    set->nodes = newNodes;
    set->size = 0;
    set->deletedCount = 0;
    set->index++;

    for(int i = 0; i < oldElementsSize; i++) {
      setAdd(set, oldElements[i]);
    }
    free(oldElements);

    return true;
  }

  return true;
}

static int findPosition(PtSet set, SetElem elem) {
  if(set == NULL) return -1;

  int position = hashFunction(elem, getPrime(set->index - 1), getPrime(set->index));

  return position;
}

static int getPrime(int index) {
  // Useful prime numbers for setting table size.
  int primeTable[] = {
    53, 107, 193, 389, 769, 1543, 3079, 6151, 12289, 24593,
    49157, 98317, 196613, 393241, 786433, 1572869, 3145739, 6291469, 12582917,
    25165843, 50331653, 100663319, 201326611, 402653189, 805306457, 1610612741
  };
  int primeSize = sizeof(primeTable) / sizeof(int);

  if(index >= primeSize) return -1;
  else return primeTable[index];
}