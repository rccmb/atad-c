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

void clear(PtList *ptAthletes) {
  if(*ptAthletes == NULL) {
    printf("There is nothing to clear. Have you already imported Athletes (LOAD_A), Medals (LOAD_M), or Hosts (LOAD_H)?\n");
  }

  if(*ptAthletes != NULL) {
    PtList athList = *ptAthletes;
    listDestroy(&athList);
    
    athList == NULL 
      ? printf("Deallocated athletes from heap memory.\n")
      : printf("Something went wrong deallocating athletes from heap memory.\n");

    if(athList == NULL) *ptAthletes = NULL;
  }
}

void quit(PtList *ptAthletes) {
  clear(ptAthletes);
}