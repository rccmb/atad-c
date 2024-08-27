/**
 * @file ui.c
 * @author Rodrigo Baptista (202200217@estudantes.ips.pt)
 * @brief Provides an implementation of ui.h.
 * 
 * Handles printing.
 * 
 * @version 1
 * @date 2024-08-10
 * 
 */

#include "../adts/list.h"
#include "../utilities/input.h"
#include <stdio.h>

#include "ui.h"

#define PAGE_LENGTH 20

void printMenu() {
  printf("Command               | Description\n");
  printf("-------               | -----------\n");
  printf("HELP                  | Shows the command menu.\n");
  printf("LOAD_A                | Loads athlete information.\n");
  printf("LOAD_M                | Loads medal information.\n");
  printf("LOAD_H                | Loads host information.\n");
  printf("CLEAR                 | Clears all stored information.\n");
  printf("QUIT                  | Quits the program.\n");
  printf("SHOW_ALL              | Shows all athletes ordered by name.\n");
  printf("SHOW_PARTICIPATIONS   | Shows athletes that participated, at least, X times.\n");
  printf("SHOW_FIRST            | Shows athletes whose first participation was in X year.\n");
  printf("SHOW_HOST             | Shows information about a host.\n");
  printf("DISCIPLINE_STATISTICS | Shows disciplines information for an Olympic Games edition.\n");
  printf("ATHLETE_INFO          | Shows information about an athlete.\n");
  printf("TOPN                  | Shows athletes with most won medals.\n");
  printf("MEDALS_WON            | Shows information about medals won by a country in 5 successive editions.\n");
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
      printf("Reached the final page.\n");
      printf("Exited pagination.\n");
      return;
    }

    printf("PAGINATION COMMANDS\n");
    printf("1. Next %d\n", PAGE_LENGTH);
    printf("2. Return\n");

    printf("Pagination Command > ");
    int userChoice;
    readInteger(&userChoice);

    if(userChoice == 1) {
      current = limit;
      limit = current + PAGE_LENGTH;
      continue;
    }
    else if(userChoice == 2) {
      printf("Exited pagination.\n");
      return;
    }
    else printf("Command not found. Type 1 to show the next page or 2 to exit pagination.\n");
  }
}