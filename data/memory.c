/**
 * @file memory.c
 * @brief Provides an implementation of memory.h.
 * 
 * Responsible for deallocating all dynamically allocated memory.
 * 
 * @version 1
 * @date 2024-08-11
 *
 * @author Rodrigo Baptista (202200217@estudantes.ips.pt)
 * @bug No known bugs.
 */

#include <stdio.h>
#include <stdlib.h>

#include "memory.h"

static void heapWipe(PtList *ptAthletes, PtMap *ptHosts, PtMedalList medals) {
  if(*ptAthletes != NULL) {
    PtList athList = *ptAthletes;

    int athSize = 0;
    listSize(athList, &athSize);
    
    listDestroy(&athList);

    athList == NULL 
      ? printf("<%d> Athletes cleared from heap memory.\n", athSize)
      : printf("Error clearing Athletes from heap memory.\n");

    if(athList == NULL) *ptAthletes = NULL;
  }

  if(*ptHosts != NULL) {
    PtMap hMap = *ptHosts;

    int hostsSize = 0;
    mapSize(hMap, &hostsSize);

    mapDestroy(&hMap);

    hMap == NULL 
      ? printf("<%d> Hosts cleared from heap memory.\n", hostsSize)
      : printf("Error clearing Hosts from heap memory.\n");

    if(hMap == NULL) *ptHosts = NULL;
  } 

  if(medals->elements != NULL) {
    free(medals->elements);
    medals->elements = NULL;
    
    medals->elements == NULL 
      ? printf("<%d> Medals cleared from heap memory.\n", medals->size)
      : printf("Error clearing Medals from heap memory.\n");

    medals->size = 0;
  } 
}

void clear(PtList *ptAthletes, PtMap *ptHosts, PtMedalList medals) {
  if(*ptAthletes == NULL && *ptHosts == NULL && medals->elements == NULL) {
    printf("There is nothing to clear. Have you already imported Athletes (LOAD_A), Medals (LOAD_M), or Hosts (LOAD_H)?\n");
  }

  heapWipe(ptAthletes, ptHosts, medals);
}

void quit(PtList *ptAthletes, PtMap *ptHosts, PtMedalList medals) {
  printf("Clearing memory before exiting...\n");

  heapWipe(ptAthletes, ptHosts, medals);

  printf("Memory cleared.\n"); 
}