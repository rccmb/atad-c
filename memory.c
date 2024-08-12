/**
 * @file memory.c
 * @author Rodrigo Baptista (202200217@estudantes.ips.pt)
 * @brief Provides an implementation of memory.h.
 * 
 * Responsible for deallocating all dynamically allocated memory.
 * 
 * @version 1
 * @date 2024-08-11
 * 
 */

#include <stdio.h>

#include "memory.h"

static void heapWipe(PtList *ptAthletes) {
  if(*ptAthletes != NULL) {
    PtList athList = *ptAthletes;
    listDestroy(&athList);
    
    athList == NULL 
      ? printf("Athletes cleared from heap memory.\n")
      : printf("Error clearing Athletes from heap memory.\n");

    if(athList == NULL) *ptAthletes = NULL;
  }
}

void clear(PtList *ptAthletes) {
  if(*ptAthletes == NULL) { // TODO Other cases.
    printf("There is nothing to clear. Have you already imported Athletes (LOAD_A), Medals (LOAD_M), or Hosts (LOAD_H)?\n");
  }

  heapWipe(ptAthletes);
}

void quit(PtList *ptAthletes) {
  printf("Clearing memory before exiting...");

  heapWipe(ptAthletes);

  printf("Memory cleared.\n"); 
}