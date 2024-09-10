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
#include "../utilities/helper.h"
#include "../utilities/input.h"
#include "../types/athleteMedals.h"
#include "../types/host.h"
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

void uiShowHost(Host h) {
  char city[MAX_GAME_NAME_LENGTH];
  extractCity(h.gameName, city);

  int dayCount = calculateDayDifference(h.gameStartDate, h.gameEndDate);

  printf("%-30s %-30s %-5s %-9s\n", "COUNTRY", "CITY", "YEAR", "DAY COUNT");
  printf("%-30s %-30s %-5d %-9d\n", h.gameLocation, city, h.gameYear, dayCount);
}

void uiTopN(AthleteMedals* athleteMedals, int size, int totalDayCount, int n) {
  int iterationCount = size;
  if(iterationCount > n) iterationCount = n;
  printf("%-35s | %-35s | %-12s | %-22s | %-25s\n", "ATHLETE ID", "COUNTRY", "TOTAL MEDALS", "AVG. MEDALS BY EDITION", "AVG. MEDALS BY DAY");
  printf("%-35s | %-35s | %-12s | %-22s | %-25s\n", "----------", "-------", "------------", "----------------------", "------------------");
  for(int i = 0; i < iterationCount; i++) {
    int firstCountryIndex = -1, firstCountryYear = 3000;
    for(int j = 0; j < athleteMedals[i].countriesSize; j++) {
      if(athleteMedals[i].countries[j].year < firstCountryYear) {
        firstCountryYear = athleteMedals[i].countries[j].year;
        firstCountryIndex = j;
      }
    }
    double avgMedalEdition = 0;
    for(int j = 0; j < athleteMedals[i].editionsSize; j++) {
      avgMedalEdition += (double) athleteMedals[i].editions[j].medalCount / athleteMedals[i].editionsSize;
    }
    printf("%-35s | ", athleteMedals[i].athleteID);
    printf("%-29s", athleteMedals[i].countries[firstCountryIndex].country);
    athleteMedals[i].countriesSize == 1 
      ? printf("       | ")
      : printf(" %s(%02d) | ", "*", athleteMedals[i].countriesSize - 1);
    printf("%-12d | %-22.2f | %-20.2f\n",
      athleteMedals[i].medalCount,
      (double) avgMedalEdition, 
      (double) athleteMedals[i].medalCount / totalDayCount
    );
  }
  printf("* This athlete changed countries during this period.\n");
}