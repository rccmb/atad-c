/**
 * @file simple.c
 * @author Rodrigo Baptista (202200217@estudantes.ips.pt)
 * @brief Provides an implementation of simple.h.
 * 
 * Allows for displaying information about the imported athlete and host data.
 * Only requires the athlete and host dataset.
 *
 * @version 1
 * @date 2024-08-09
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include "../adts/map.h"
#include "../adts/list.h"
#include "../types/athlete.h"
#include "../types/host.h"
#include "../utilities/ui.h"
#include "../utilities/input.h"
#include "../utilities/helper.h"

#include "simple.h"

void showAll(PtList athletes) {
  if(athletes == NULL) {
    printf("No Athletes provided. Have you imported them? (LOAD_A)\n");
    return;
  }

  paginate(athletes);
}

void showParticipations(PtList athletes, int participationCount) {
  if(athletes == NULL) {
    printf("No Athletes provided. Have you imported them? (LOAD_A)\n");
    return;
  }

  PtList filteredList = listCreate();

  int athletesSize;
  listSize(athletes, &athletesSize);

  int filteredSize = 0;
  for(int i = 0; i < athletesSize; i++) {
    Athlete athlete;
    listGet(athletes, i, &athlete);
    if(athlete.gamesParticipations >= participationCount) {
      listAdd(filteredList, filteredSize++, athlete);
    }
  }

  if(filteredSize <= 0) {
    printf("No Athletes found with atleast %d participations.\n", participationCount);
    return;
  }

  paginate(filteredList);

  listDestroy(&filteredList);
}

void showFirst(PtList athletes, int firstYear) {
  if(athletes == NULL) {
    printf("No Athletes provided. Have you imported them? (LOAD_A)\n");
    return;
  }

  PtList filteredList = listCreate();

  int athletesSize;
  listSize(athletes, &athletesSize);

  int filteredSize = 0;
  for(int i = 0; i < athletesSize; i++) {
    Athlete athlete;
    listGet(athletes, i, &athlete);
    if(athlete.yearFirstParticipation == firstYear) {
      listAdd(filteredList, filteredSize++, athlete);
    }
  }

  if(filteredSize <= 0) {
    printf("No Athletes found whose first participation was at %d .\n", firstYear);
    return;
  }

  paginate(filteredList);

  listDestroy(&filteredList);
}

void showHost(PtMap hosts, char *gameSlug) {
  if(hosts == NULL) {
    printf("No Hosts provided. Have you imported them? (LOAD_H)\n");
    return;
  }

  StringWrap swr = stringWrapCreate(gameSlug);

  if(mapContains(hosts, swr)) {
    Host h;
    mapGet(hosts, swr, &h);

    char city[MAX_GAME_NAME_LENGTH];
    extractCity(h.gameName, city);

    int dayCount = calculateDayDifference(h.gameStartDate, h.gameEndDate);

    printf("%-30s %-30s %-5s %-9s\n", "COUNTRY", "CITY", "YEAR", "DAY COUNT");
    printf("%-30s %-30s %-5d %-9d\n", h.gameLocation, city, h.gameYear, dayCount);
  } else printf("No edition found!\n");
}