/**
 * @file helper.c
 * @author Rodrigo Baptista (202200217@estudantes.ips.pt)
 * @brief Provides an implementation of helper.h.
 * 
 * Commonly used operations throughout the program.
 * 
 * @version 1
 * @date 2024-08-10
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "helper.h"

static int partition(PtList athletes, int low, int high) {
  Athlete pivot;
  listGet(athletes, high, &pivot);
  
  int i = low - 1;

  for(int j = low; j < high; j++) {
    Athlete comp;
    listGet(athletes, j, &comp);

    if(strcmp(comp.athleteName, pivot.athleteName) <= 0) {
      i++;
      Athlete temp;
      listSet(athletes, i, comp, &temp);
      listSet(athletes, j, temp, &temp);
    }
  }

  Athlete temp;
  listSet(athletes, i + 1, pivot, &temp);
  listSet(athletes, high, temp, &temp);

  return i + 1;
}

static void quicksort(PtList athletes, int low, int high) {
  if (low < high) {
    int pi = partition(athletes, low, high);

    quicksort(athletes, low, pi - 1);
    quicksort(athletes, pi + 1, high);
  }
}

int strcmpins(char *str1, char *str2) {
  while(*str1 != '\0' || *str2 != '\0') {
    char a = tolower(*str1);
    char b = tolower(*str2);

    if(a != b) return a > b ? 1 : -1; 
    if(a == '\0' && b == '\0') return 0;

    str1++; 
    str2++;
  }

  return 0;
}

void orderAthletes(PtList athletes) {
  if(athletes == NULL) return;

  int size;
  listSize(athletes, &size);

  quicksort(athletes, 0, size - 1);
}

PtList athleteListCopy(PtList athletes) {
  if(athletes == NULL) return NULL;

  int size;
  listSize(athletes, &size);

  PtList list = listCreate();

  for(int i = 0; i < size; i++) {
    Athlete athlete;
    listGet(athletes, i, &athlete);
    listAdd(list, i, athlete);
  }

  return list;
}

void checkOrderedAthletesLoaded(PtList athletes, PtList *athletesCopy) {
  if(athletes != NULL) {
    PtList list = *athletesCopy;

    if(list == NULL) {
      printf("Ordered copy of athlete information not detected.\n");
      printf("Creating an ordered copy of athletes and loading it into memory... (saves execution time in the future)\n");
      list = athleteListCopy(athletes);
      orderAthletes(list);
      *athletesCopy = list;
    }
  }
}