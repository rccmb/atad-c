/**
 * @file simple.c
 * @author Rodrigo Baptista (202200217@estudantes.ips.pt)
 * @brief Provides an implementation of simple.h.
 * 
 * Allows for displaying information about the imported athlete and host data.
 * Only requires the athlete and host dataset.
 *
 * @version 2
 * @date 2024-08-25
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../adts/map.h"
#include "../adts/list.h"
#include "../types/athlete.h"
#include "../types/host.h"
#include "../utilities/ui.h"
#include "../utilities/input.h"
#include "../utilities/helper.h"
#include "../adts/set.h"

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
  if(filteredList == NULL) {
    printf("[SHOW_PARTICIPATIONS_FILTERED_LIST] Memory error ocurred.\n");
    return;
  }

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
  if(filteredList == NULL) {
    printf("[SHOW_FIRST_FILTERED_LIST] Memory error ocurred.\n");
    return;
  }

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

void showDisciplineStatistics(PtMedalList medals, char *gameSlug) {
  if(medals->elements == NULL) {
    printf("No Medals provided. Have you imported them? (LOAD_M)\n");
    return;
  } 

  PtSet set = setCreate();
  if(set == NULL) {
    printf("[DISC_STATS_SET] Memory error ocurred.\n");
    return;
  }

  MedalAccumulator *accumulators = (MedalAccumulator*) malloc(sizeof(MedalAccumulator));

  for(int i = 0; i < medals->size; i++) {
    Medal currentMedal = medals->elements[i];

    if(strcmp(currentMedal.game, gameSlug) == 0) {
      int accumulatorSize = 0;
      setSize(set, &accumulatorSize);

      StringWrap swr = stringWrapCreate(currentMedal.discipline);
      int result = setAdd(set, swr);

      if(result == SET_DUPLICATE) {
        for(int i = 0; i < accumulatorSize; i++) {
          if(strcmp(accumulators[i].discipline, currentMedal.discipline) == 0) {
            bool added = medalAccumulatorAddMedal(&(accumulators[i]), &currentMedal);
            if(!added) {
              printf("[DISC_STATS_ACCUMULATOR] Something went wrong adding medal to old accumulator...\n");
              return;
            }
            break;
          }
        }
      } else {
        MedalAccumulator *newAccumulators = (MedalAccumulator*) realloc(accumulators, sizeof(MedalAccumulator) * (accumulatorSize + 1));
        if(newAccumulators == NULL) {
          printf("[DISC_STATS_ACCUMULATOR] Memory error ocurred.\n");
          return;
        }

        MedalAccumulator accum = medalAccumulatorCreate(currentMedal.discipline);
        
        accumulators = newAccumulators;
        accumulators[accumulatorSize] = accum;

        bool added = medalAccumulatorAddMedal(&(accumulators[accumulatorSize]), &currentMedal);
        if(!added) {
          printf("[DISC_STATS_ACCUMULATOR] Something went wrong adding medal to fresh accumulator...\n");
          return;
        }
      }
    }
  }

  int size = 0;
  setSize(set, &size);

  printf("Discipline statistics for %s.\n", gameSlug);
  printf("\t-> There were %d different disciplines.\n", size);
  printf("%45s %45s %10s %47s\n", "DISCIPLINE", "TOP COUNTRY", "MEDALS", "WOMEN RATIO");
  for(int i = 0; i < LINE_LENGTH; i++) {
    printf("-");
  }
  printf("\n");
  for(int i = 0; i < size; i++) {
    
  }

  setDestroy(&set);
}