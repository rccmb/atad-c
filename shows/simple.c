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
#include "../types/medalAccumulator.h"
#include "../types/host.h"
#include "../utilities/ui.h"
#include "../utilities/input.h"
#include "../utilities/helper.h"
#include "../adts/set.h"

#include "simple.h"

void showAll(PtList athletes) {
  if(athletes == NULL) return;

  paginate(athletes);
}

void showParticipations(PtList athletes, int participationCount) {
  if(athletes == NULL) return;

  PtList filteredList = listCreate();
  if(filteredList == NULL) {
    printf("[SHOW_PARTICIPATIONS] Memory error ocurred while creating filtered list.\n");
    // TODO DESTROY
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
  if(athletes == NULL) return;

  PtList filteredList = listCreate();
  if(filteredList == NULL) {
    printf("[SHOW_FIRST] Memory error ocurred while creating filtered list.\n");
    // TODO DESTROY
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
  if(hosts == NULL) return;

  StringWrap swr = stringWrapCreate(gameSlug);

  if(mapContains(hosts, swr)) {
    Host h;
    mapGet(hosts, swr, &h);

    uiShowHost(h);
  } else printf("No edition found!\n");
}

void showDisciplineStatistics(PtMedalList medals, char *gameSlug) {
  if(medals->elements == NULL) return;

  PtSet set = setCreate();
  if(set == NULL) {
    printf("[DISCIPLINE_STATISTICS] Memory error ocurred while creating set.\n");
    // TODO DESTROY
    return;
  }

  MedalAccumulator *accumulators = (MedalAccumulator*) calloc(0, sizeof(MedalAccumulator));

  for(int i = 0; i < medals->size; i++) {
    Medal currentMedal = medals->elements[i];

    if(strcmp(currentMedal.game, gameSlug) == 0) {
      int accumulatorSize = 0;
      setSize(set, &accumulatorSize);

      StringWrap swr = stringWrapCreate(currentMedal.discipline);
      
      if(setContains(set, swr)) {
        for(int i = 0; i < accumulatorSize; i++) {
          if(strcmp(accumulators[i].discipline, currentMedal.discipline) == 0) {
            bool added = medalAccumulatorAddMedal(&(accumulators[i]), &currentMedal);
            if(!added) {
              printf("[DISCIPLINE_STATISTICS] Error ocurred while adding medal to EXISTING accumulator.\n");
              // TODO DESTROY
              return;
            }
            break;
          }
        }
      } else {
        setAdd(set, swr);

        MedalAccumulator *newAccumulators = (MedalAccumulator*) realloc(accumulators, sizeof(MedalAccumulator) * (accumulatorSize + 1));
        if(newAccumulators == NULL) {
          printf("[DISCIPLINE_STATISTICS] Memory error ocurred while realloc'ing medal accumulator array.\n");
          // TODO DESTROY
          return;
        }

        MedalAccumulator accum = medalAccumulatorCreate(currentMedal.discipline);
        
        accumulators = newAccumulators;
        accumulators[accumulatorSize] = accum;

        bool added = medalAccumulatorAddMedal(&(accumulators[accumulatorSize]), &currentMedal);
        if(!added) {
          printf("[DISCIPLINE_STATISTICS]  Error ocurred while adding medal to FRESH accumulator.\n");
          // TODO DESTROY
          return;
        }
      }
    }
  }

  int size = 0;
  setSize(set, &size);

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
      : printf("%54s %s(%02d)", country, "*", tied);
    printf("%10d %17.2f", max, (double) currentMA.women / currentMA.totalParticipants);
    printf("\n");

    free(accumulators[i].countries);
  }

  printf("*(tie count) represents the number of countries tied for first place.\n");
  printf("The women ration is calculated with the specific amount of women. All other types go towards total participations.\n");

  free(accumulators);
  setDestroy(&set);
}