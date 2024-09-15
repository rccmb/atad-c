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
#include "../types/medalsWon.h"
#include "../types/host.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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

    while(userChoice != 1 && userChoice != 2) {
      printf("Command not found. Type 1 to show the next page or 2 to exit pagination.\n");
      printf("Pagination Command > ");
      readInteger(&userChoice);
    }

    if(userChoice == 1) {
      current = limit;
      limit = current + PAGE_LENGTH;
      continue;
    }
    else if(userChoice == 2) {
      printf("Exited pagination.\n");
      return;
    }
  }
}

void uiDisciplineStatistics(PtMedalAccumulator accumulators, int size, char *gameSlug) {
  printf("Discipline statistics for %s.\n", gameSlug);
  printf("-> There were %d different disciplines.\n", size);

  printf("%60s %60s %10s %17s\n", "DISCIPLINE", "TOP COUNTRY", "MEDALS", "WOMEN RATIO");
  for(int i = 0; i < LINE_LENGTH; i++) {
    printf("-");
  }
  printf("\n");

  for(int i = 0; i < size; i++) {
    MedalAccumulator currentMA = accumulators[i];

    char country[MAX_COUNTRY_LENGTH];
    int max = 0;
    int tied = 0;
    for(int j = 0; j < currentMA.countriesSize; j++) {
      if(currentMA.countries[j].medalCount == max) {
        tied++;
      }
      if(currentMA.countries[j].medalCount > max) {
        max = currentMA.countries[j].medalCount;
        strcpy(country, currentMA.countries[j].country);
        tied = 0;
      }
    }

    printf("%5d. %53s ", i + 1, currentMA.discipline);
    tied == 0 
      ? printf("%60s", country)
      : printf("%54s %s(%02d)", country, "*", tied + 1);
    printf("%10d %17.2f", max, (double) currentMA.women / currentMA.totalParticipants);
    printf("\n");

    free(accumulators[i].countries);
  }

  printf("*(tie count) represents the number of countries tied for first place.\n");
  printf("The women ration is calculated with the specific amount of women. All other types go towards total participations.\n");
}

void uiShowHost(Host h) {
  char city[MAX_GAME_NAME_LENGTH];
  extractCity(h.gameName, city);

  int dayCount = calculateDayDifference(h.gameStartDate, h.gameEndDate);

  printf("%-30s %-30s %-5s %-9s\n", "COUNTRY", "CITY", "YEAR", "DAY COUNT");
  printf("%-30s %-30s %-5d %-9d\n", h.gameLocation, city, h.gameYear, dayCount);
}

void uiAthleteInfo(PtMedal entries, char *athleteId, char *athleteCountry, int entriesSize) {
  int flag[entriesSize];
  for(int i = 0; i < entriesSize; i++) flag[i] = 0;
  printf("Athlete %s competed for %s and won %d medals!\n", athleteId, athleteCountry, entriesSize);
  for(int i = 0; i < entriesSize; i++) {
    if(flag[i] == 1) continue;
    printf("Edition %s:\n", entries[i].game);
    for(int j = i; j < entriesSize; j++) {
      if(strcmp(entries[j].game, entries[i].game) == 0) {
        flag[j] = 1;
        char extType[64];
        medalType(&(entries[j]), extType);
        printf("\t-> Won %s in %s, event: %s.\n", 
          extType, 
          entries[j].discipline,
          entries[j].eventTitle
        );
      }
    }
  }
}

void uiTopN(PtAthleteMedals athleteMedals, int size, int totalDayCount, int n) {
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

void uiMedalsWon(PtMedalsWon medalsWon, int size, PtMap hosts) {
  printf("%-30s | %-4s | %-8s | %-3s | %-3s | %-3s\n", "EDITION", "YEAR", "CATEGORY", "G", "S", "B");
  printf("%-30s | %-4s | %-8s | %-3s | %-3s | %-3s\n", "------------------------------", "----", "--------", "---", "---", "---");
  for(int i = 0; i < size; i++) {
    Host currentHost;
    StringWrap swr = stringWrapCreate(medalsWon[i].edition);
    mapGet(hosts, swr, &currentHost);
    for(int j = 0; j < 3; j++) {
      printf("%-30s | %-4d | %-8c | %-3d | %-3d | %-3d\n", 
        currentHost.gameName,
        medalsWon[i].year,
        medalsWon[i].categories[j].category,
        medalsWon[i].categories[j].gold,
        medalsWon[i].categories[j].silver,
        medalsWon[i].categories[j].bronze
      );
    }
  }
}