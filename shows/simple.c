/**
 * @file simple.c
 * @brief Provides an implementation of simple.h.
 * 
 * Allows for displaying information about the imported athlete and host data.
 * Only requires the athlete and host dataset.
 *
 * @version 2
 * @date 2024-08-25
 * 
 * @author Rodrigo Baptista (202200217@estudantes.ips.pt)
 * @bug No known bugs.
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
    return;
  }

  int athletesSize;
  listSize(athletes, &athletesSize);

  int filteredSize = 0;
  for(int i = 0; i < athletesSize; i++) {
    Athlete athlete;
    listGet(athletes, i, &athlete);
    if(athlete.gamesParticipations >= participationCount) {
      int result = listAdd(filteredList, filteredSize++, athlete);
      if(result != 0) {
        printf("[SHOW_PARTICIPATIONS] Error ocurred while creating filtered list: %d.\n", result);
        listDestroy(&filteredList);
        return;
      }
    }
  }

  if(filteredSize <= 0) {
    printf("No Athletes found with atleast %d participations.\n", participationCount);
    listDestroy(&filteredList);
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
    return;
  }

  int athletesSize;
  listSize(athletes, &athletesSize);

  int filteredSize = 0;
  for(int i = 0; i < athletesSize; i++) {
    Athlete athlete;
    listGet(athletes, i, &athlete);
    if(athlete.yearFirstParticipation == firstYear) {
      int result = listAdd(filteredList, filteredSize++, athlete);
      if(result != 0) {
        printf("[SHOW_FIRST] Error ocurred while creating filtered list: %d.\n", result);
        listDestroy(&filteredList);
        return;
      }
    }
  }

  if(filteredSize <= 0) {
    printf("No Athletes found whose first participation was at %d .\n", firstYear);
    listDestroy(&filteredList);
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

  int terminationFlag = 0;

  PtSet set = setCreate();
  if(set == NULL) {
    printf("[DISCIPLINE_STATISTICS] Memory error ocurred while creating set.\n");
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
              terminationFlag = 1;
            }
            break;
          }
        }
        if(terminationFlag == 1) break;
      } else {
        setAdd(set, swr);
        MedalAccumulator *newAccumulators = (MedalAccumulator*) realloc(accumulators, sizeof(MedalAccumulator) * (accumulatorSize + 1));
        if(newAccumulators == NULL) {
          printf("[DISCIPLINE_STATISTICS] Memory error ocurred while realloc'ing medal accumulator array.\n");
          terminationFlag = 1;
          break;
        }
        MedalAccumulator accum = medalAccumulatorCreate(currentMedal.discipline);
        accumulators = newAccumulators;
        accumulators[accumulatorSize] = accum;
        bool added = medalAccumulatorAddMedal(&(accumulators[accumulatorSize]), &currentMedal);
        if(!added) {
          printf("[DISCIPLINE_STATISTICS]  Error ocurred while adding medal to FRESH accumulator.\n");
          terminationFlag = 1;
          break;
        }
      }
    }
  }

  if(terminationFlag != 1) {
    int size = 0;
    setSize(set, &size);

    uiDisciplineStatistics(accumulators, size, gameSlug);
  }

  free(accumulators);
  setDestroy(&set);
}