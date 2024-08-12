/**
 * @file athleteShow.c
 * @author Rodrigo Baptista (202200217@estudantes.ips.pt)
 * @brief Provides an implementation of athleteShow.h.
 * 
 * Allows for displaying information about the imported athlete data.
 * Only requires the athlete dataset.
 *
 * @version 1
 * @date 2024-08-09
 * 
 */

#include <stdio.h>
#include <string.h>
#include "../list.h"
#include "../types/athlete.h"
#include "../input.h"

#include "athleteShow.h"

#define PAGE_LENGTH 20
#define LINE_LENGTH 150

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

void orderAthletes(PtList athletes) {
  if(athletes == NULL) return;

  int size;
  listSize(athletes, &size);

  quicksort(athletes, 0, size - 1);
}

void paginate(PtList athletes) { 
  if(athletes == NULL) return;

  int size;
  listSize(athletes, &size);

  int current = 0;
  int limit = current + PAGE_LENGTH;
  while(true) {
    printf("%d ATHLETES FOUND.\n", size);
    printf("%40s %60s %15s %20s %11s\n", "ATHLETE ID", "FULL NAME", "PARTICIPATIONS", "FIRST PARTICIPATION", "BIRTH YEAR");
    for(int i = 0; i < LINE_LENGTH; i++) {
      printf("-");
    }
    printf("\n");

    if(limit > size) limit = size;
    for(int i = current; i < limit; i++) {
      Athlete ath;
      listGet(athletes, i, &ath);
      printf("%40s %60s %15d %20d %11d\n", ath.athleteID, ath.athleteName, ath.gamesParticipations, ath.yearFirstParticipation, ath.athleteBirth);
    }

    printf("Lines from %d to %d.\n", current, limit);
    printf("\n");

    if(limit == size) {
      printf("Reached the final page of SHOW_ALL.\n");
      printf("Exited SHOW_ALL.\n");
      return;
    }

    printf("SHOW_ALL PAGINATED\n");
    printf("1. Next %d\n", PAGE_LENGTH);
    printf("2. Return\n");

    printf("SHOW_ALL Command > ");
    int userChoice;
    readInteger(&userChoice);

    if(userChoice == 1) {
      current = limit;
      limit = current + PAGE_LENGTH;
      continue;
    }
    else if(userChoice == 2) {
      printf("Exited SHOW_ALL.\n");
      return;
    }
    else printf("Command not found. Type 1 to show the next page or 2 to exit SHOW_ALL.\n");
  }
}

void showAll(PtList athletes) {
  if(athletes == NULL) {
    printf("No Athletes provided. Have you imported them? (LOAD_A)\n");
    return;
  }

  paginate(athletes);
}

void showParticipations(PtList athletes, int participationCount) {
  return;
}

void showFirst(PtList athletes, int firstYear) {
  return;
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
      printf("Creating an ordered copy of athletes and loading it into memory...\n");
      list = athleteListCopy(athletes);
      orderAthletes(list);
      *athletesCopy = list;
    }
  }
}