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

static void heapWipe(PtList *ptAthletes, PtMap *ptHosts) {
  if(*ptAthletes != NULL) {
    PtList athList = *ptAthletes;
    listDestroy(&athList);
    
    athList == NULL 
      ? printf("Athletes cleared from heap memory.\n")
      : printf("Error clearing Athletes from heap memory.\n");

    if(athList == NULL) *ptAthletes = NULL;
  }

  if(*ptHosts != NULL) {
    PtMap hMap = *ptHosts;
    mapDestroy(&hMap);
    
    hMap == NULL 
      ? printf("Hosts cleared from heap memory.\n")
      : printf("Error clearing Hosts from heap memory.\n");

    if(hMap == NULL) *ptHosts = NULL;
  }
}

void clear(PtList *ptAthletes, PtMap *ptHosts) {
  if(*ptAthletes == NULL && *ptHosts == NULL) {
    printf("There is nothing to clear. Have you already imported Athletes (LOAD_A), Medals (LOAD_M), or Hosts (LOAD_H)?\n");
  }

  heapWipe(ptAthletes, ptHosts);
}

void quit(PtList *ptAthletes, PtMap *ptHosts) {
  printf("Clearing memory before exiting...");

  heapWipe(ptAthletes, ptHosts);

  printf("Memory cleared.\n"); 
}