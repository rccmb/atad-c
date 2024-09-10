/**
 * @file complex.c
 * @author Rodrigo Baptista (202200217@estudantes.ips.pt)
 * @brief Provides an implementation of complex.h.
 * 
 * Allows for displaying information about the imported athlete, host and medal data.
 *
 * @version 1
 * @date 2024-08-24
 * 
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../utilities/helper.h"
#include "../utilities/ui.h"
#include "../types/medal.h"
#include "../adts/map.h"
#include "../types/athlete.h"
#include "../types/athleteMedals.h"
#include "../adts/set.h"
#include "../adts/list.h"

#include "complex.h"

static void bubbleSortAthleteMedals(AthleteMedals* array, int start, int end);

void showAthleteInfo(PtList athletes, PtMedalList medals, char *athleteId) {
  if(athletes == NULL || medals->elements == NULL) return;
  
  Athlete athlete;
  bool result = getAthlete(athletes, athleteId, &athlete);

  if(result == false) {
    printf("Athlete %s does not exist.\n", athleteId);
    return;
  }

  Medal* entries = (Medal*) calloc(0, sizeof(Medal));
  if(entries == NULL) {
    printf("[ATHLETE_INFO] Something went wrong alloc'ing the medal entries.\n");
    // TODO DESTROY
    return;
  }
  int entriesSize = 0;

  char athleteCountry[MAX_COUNTRY_LENGTH];

  for(int i = 0; i < medals->size; i++) {
    if(strcmp(medals->elements[i].athleteID, athleteId) == 0) {
      if(entriesSize == 0) strcpy(athleteCountry, medals->elements[i].country);
      entries = (Medal*) realloc(entries, sizeof(Medal) * (entriesSize + 1));
      if(entries == NULL) {
        printf("[ATHLETE_INFO] Something went wrong realloc'ing the medal entries.\n");
        // TODO DESTROY
        return;
      }
      entries[entriesSize++] = medals->elements[i];
    }
  }

  int flag[entriesSize];
  for(int i = 0; i < entriesSize; i++) flag[i] = 0;

  if(entriesSize == 0) {
    printf("Athlete %s did not win any medals!\n", athleteId);
    free(entries);
    return;
  }

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

  free(entries);
}

void showTopN(PtList athletes, PtMedalList medals, PtMap hosts, int n, int start, int end, char *season) {
  if(athletes == NULL || medals->elements == NULL || hosts == NULL) return;

  int terminationFlag = 0;

  int totalDayCount = 0;
  int hostsSize = 0;
  mapSize(hosts, &hostsSize);

  PtSet validHosts = setCreate();
  Host* validHostsValues = (Host*) calloc(0, sizeof(Host));
  Host* hostsValues = mapValues(hosts);

  int validHostsValuesSize = 0;
  if(validHosts == NULL || validHostsValues ==  NULL || hostsValues == NULL) {
    printf("[TOPN] Something went wrong initializing the valid hosts set, valid hosts array, or copying the values from the hosts.\n");
    terminationFlag = 1;
  }

  PtSet validAthletes = setCreate();
  AthleteMedals *athleteMedals = (AthleteMedals*) calloc(0, sizeof(AthleteMedals));
  AthleteMedals* orderedFinalAthleteMedals = (AthleteMedals*) calloc(0, sizeof(AthleteMedals));
  if(validAthletes == NULL || athleteMedals ==  NULL) {
    printf("[TOPN] Something went wrong initializing the valid athletes set or athlete medals array.\n");
    terminationFlag = 1;
  }
  
  /* Populating the valid hosts. */
  if(terminationFlag != 1) {
    for(int i = 0; i < hostsSize; i++) {
      if(
        strcmpins(hostsValues[i].gameSeason, season) == 0
        && start <= datetimeYear(&(hostsValues[i].gameStartDate))
        && end >= datetimeYear(&(hostsValues[i].gameEndDate))
      ) {
        StringWrap swrGameSlug = stringWrapCreate(hostsValues[i].gameSlug);
        int result = setAdd(validHosts, swrGameSlug);
        if(result != SET_OK && result != SET_DUPLICATE) {
          printf("[TOPN] Failed to add value to valid hosts set.\n");
          terminationFlag = 1;
          break;
        } 
        else {
          validHostsValues = (Host*) realloc(validHostsValues, sizeof(Host) * (validHostsValuesSize + 1));
          if(validHostsValues == NULL) {
            printf("[TOPN] Something went wrong realloc'ing the valid hosts array.\n");
            terminationFlag = 1;
            break;
          }
          validHostsValues[validHostsValuesSize++] = hostsValues[i];
          totalDayCount += calculateDayDifference(hostsValues[i].gameStartDate, hostsValues[i].gameEndDate);
        }
      }
    }
  }

  /* Populating athlete medals. */
  int athleteMedalsSize = 0;
  int maxFound = 1;
  if(terminationFlag != 1) {
    for(int i = 0; i < medals->size; i++) {
      StringWrap swrEdition = stringWrapCreate(medals->elements[i].game);
      if(
        strcmp(medals->elements[i].athleteID, "") != 0 
        && setContains(validHosts, swrEdition)
      ) {
        StringWrap swrAthId = stringWrapCreate(medals->elements[i].athleteID);
        if(setContains(validAthletes, swrAthId)) {
          for(int j = 0; j < athleteMedalsSize; j++) {
            if(strcmp(athleteMedals[j].athleteID, medals->elements[i].athleteID) == 0) {
              bool added = athleteMedalsAddMedal(&(athleteMedals[j]), &(medals->elements[i]));
              if(athleteMedals[j].medalCount > maxFound) maxFound = athleteMedals[j].medalCount;
              if(!added) {
                printf("[TOPN] Something went wrong adding medal to EXISTING athlete medals.\n");
                terminationFlag = 1;
              }
              break;
            }
          }
          if(terminationFlag == 1) break;
        } else {
          setAdd(validAthletes, swrAthId);
          athleteMedals = (AthleteMedals*) realloc(athleteMedals, sizeof(AthleteMedals) * (athleteMedalsSize + 1));
          if(athleteMedals == NULL) {
            printf("[TOPN] Something went wrong initializing the valid athletes set or athlete medals array.\n");
            terminationFlag = 1;
            break;
          }
          athleteMedals[athleteMedalsSize] = athleteMedalsCreate(medals->elements[i].athleteID);
          bool added = athleteMedalsAddMedal(&(athleteMedals[athleteMedalsSize]), &(medals->elements[i]));
          athleteMedalsSize++;
          if(!added) {
            printf("[TOPN] Something went wrong adding medal to FRESH athlete medals.\n");
            terminationFlag = 1;
            break;
          }
        }
      }
    }
  }

  /* Organizing the chosen athlete medals. */
  int currentMax = maxFound, nextMax = 0;
  int currentSize = 0;
  int partitionIndex = -1;
  if(terminationFlag != 1) {
    for(int i = 0; i < n; i++) {
      for(int j = 0; j < athleteMedalsSize; j++) {
        if(athleteMedals[j].medalCount == currentMax) {
          AthleteMedals* newAthleteMedals = (AthleteMedals*) realloc(orderedFinalAthleteMedals, sizeof(AthleteMedals) * (currentSize + 1));
          if(newAthleteMedals == NULL) {
            printf("[TOPN] Something went wrong realloc'ing the FINAL ordered athlete medals.\n");
            terminationFlag = 1;
            break;
          }
          orderedFinalAthleteMedals = newAthleteMedals;
          orderedFinalAthleteMedals[currentSize++] = athleteMedals[j];
          if(partitionIndex == -1) partitionIndex = currentSize - 1;
        }
        if(athleteMedals[j].medalCount < currentMax && athleteMedals[j].medalCount > nextMax) {
          nextMax = athleteMedals[j].medalCount;
        }
      }
      if(terminationFlag == 1) break;
      if(partitionIndex != -1) {
        bubbleSortAthleteMedals(orderedFinalAthleteMedals, partitionIndex, currentSize);
        partitionIndex = -1;
      }
      if(currentSize >= n) break;
      currentMax = nextMax;
      nextMax = 0;
      partitionIndex = -1;
    }
  }
  
  if(terminationFlag != 1) {
    uiTopN(orderedFinalAthleteMedals, currentSize, totalDayCount, n);
  }

  /* Wiping associated memory. */
  for(int i = 0; i < athleteMedalsSize; i++) {
    free(athleteMedals[i].countries);
    free(athleteMedals[i].editions);
  }
  free(athleteMedals);
  free(orderedFinalAthleteMedals);
  setDestroy(&validAthletes);
  setDestroy(&validHosts);
  free(validHostsValues);
  free(hostsValues);
}

static void bubbleSortAthleteMedals(AthleteMedals* array, int start, int end) {
  for(int i = start; i < end - 1; i++) {
    bool swapped = false;
    for(int j = start; j < end - (i - start) - 1; j++) {
      if(strcmp(array[j].athleteID, array[j + 1].athleteID) > 0) {
        AthleteMedals temp = array[j];
        array[j] = array[j + 1];
        array[j + 1] = temp;
        swapped = true;
      }
    }
    if(!swapped) break;
  }
}