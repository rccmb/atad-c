/**
 * @file complex.c
 * @brief Provides an implementation of complex.h.
 * 
 * Allows for displaying information about the imported athlete, host and medal data.
 *
 * @version 1
 * @date 2024-08-24
 * 
 * @author Rodrigo Baptista (202200217@estudantes.ips.pt)
 * @bug No known bugs.
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

static void bubbleSortMedalsWon(MedalsWon* array, int size);

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
    return;
  }
  int entriesSize = 0;

  char athleteCountry[MAX_COUNTRY_LENGTH];

  for(int i = 0; i < medals->size; i++) {
    if(strcmp(medals->elements[i].athleteID, athleteId) == 0) {
      if(entriesSize == 0) strcpy(athleteCountry, medals->elements[i].country);
      Medal* newEntries = (Medal*) realloc(entries, sizeof(Medal) * (entriesSize + 1));
      if(newEntries == NULL) {
        printf("[ATHLETE_INFO] Something went wrong realloc'ing the medal entries.\n");
        free(entries);
        return;
      }
      entries = newEntries;
      entries[entriesSize++] = medals->elements[i];
    }
  }

  if(entriesSize == 0) {
    printf("Athlete %s did not win any medals!\n", athleteId);
    free(entries);
    return;
  }
  
  uiAthleteInfo(entries, athleteId, athleteCountry, entriesSize);

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

void medalsWon(PtMedalList medals, PtMap hosts, char *country, char *season, int year) {
  if(medals->elements == NULL || hosts == NULL) return;

  int terminationFlag = 0;

  PtSet foundEditions = setCreate();
  if(foundEditions == NULL) {
    printf("[MEDALS_WON] Could not create set to store found editions.\n");
    return;
  }

  MedalsWon* medalsWon = (MedalsWon*) calloc(0, sizeof(MedalsWon));
  int medalsWonSize = 0;
  if(medalsWon == NULL) {
    printf("[MEDALS_WON] Could not create array to store medals won.\n");
    setDestroy(&foundEditions);
    return;
  }

  /* Populating valid hosts. */
  int hostsSize = 0;
  mapSize(hosts, &hostsSize);
  Host* hostsValues = mapValues(hosts);
  PtSet validHosts = setCreate();
  if(hostsValues == NULL || validHosts == NULL) {
    printf("[MEDALS_WON] Something went wrong getting hosts values or creating the set for hosts values.\n");
    setDestroy(&validHosts);
    setDestroy(&foundEditions);
    free(medalsWon);
    free(hostsValues);
    return;
  }

  for(int i = 0; i < hostsSize; i++) {
    if(strcmp(hostsValues[i].gameSeason, season) == 0) {
      StringWrap swrGameSlug = stringWrapCreate(hostsValues[i].gameSlug);
      setAdd(validHosts, swrGameSlug);
    }
  }

  /* Populating all valid medals. */
  bool countryExists = false;
  for(int i = 0; i < medals->size; i++) {
    StringWrap swrGameSlug = stringWrapCreate(medals->elements[i].game);
    if(strcmpins(medals->elements[i].country, country) == 0) {
      countryExists = true;
      if(
        setContains(validHosts, swrGameSlug)
        && getYearFromSlug(medals->elements[i].game) >= year
      ) {
        StringWrap swrEdition = stringWrapCreate(medals->elements[i].game);
        if(setContains(foundEditions, swrEdition)) {
          for(int j = 0; j < medalsWonSize; j++) {
            if(strcmp(medals->elements[i].game, medalsWon[j].edition) == 0) {
              bool added = medalsWonAddMedal(&(medalsWon[j]), &(medals->elements[i]));
              if(!added) {
                printf("[MEDALS_WON] Something went wrong adding medal to EXISTING medals won.\n");
                terminationFlag = 1;
                break;
              }
              break;
            }
          }
          if(terminationFlag == 1) break;
        } else {
          setAdd(foundEditions, swrEdition);
          MedalsWon* newMedalsWon = (MedalsWon*) realloc(medalsWon, sizeof(MedalsWon) * (medalsWonSize + 1));
          if(newMedalsWon == NULL) {
            printf("[MEDALS_WON] Could not realloc the array to store medals won.\n");
            terminationFlag = 1;
            break;
          }
          medalsWon = newMedalsWon;
          medalsWon[medalsWonSize] = medalsWonCreate(medals->elements[i].game, getYearFromSlug(medals->elements[i].game));
          bool added = medalsWonAddMedal(&(medalsWon[medalsWonSize]), &(medals->elements[i]));
          if(!added) {
            printf("[MEDALS_WON] Something went wrong adding medal to FRESH medals won.\n");
            terminationFlag = 1;
            break;
          }
          medalsWonSize++;
        }
      }
    }
  }

  if(countryExists == false) {
    printf("Error! The specified country does not exist.\n");
    terminationFlag = 1;
  }

  if(medalsWonSize == 0) {
    printf("Error! There are no entries for the specified time period/season.\n");
    terminationFlag = 1;
  }

  if(terminationFlag != 1) {
    bubbleSortMedalsWon(medalsWon, medalsWonSize);
  }

  int sizePrint = medalsWonSize;
  if(sizePrint > 5) sizePrint = 5;
  if(terminationFlag != 1) {
    uiMedalsWon(medalsWon, sizePrint, hosts);
  }

  for(int i = 0; i < medalsWonSize; i++) {
    free(medalsWon[i].categories);
  }
  setDestroy(&validHosts);
  setDestroy(&foundEditions); 
  free(medalsWon);
  free(hostsValues);
}

static void bubbleSortMedalsWon(MedalsWon* array, int size) {
  for(int i = 0; i < size - 1; i++) {
    bool swapped = false;
    for(int j = 0; j < size - i - 1; j++) {
      if(array[j].year > array[j + 1].year) {
        MedalsWon temp = array[j];
        array[j] = array[j + 1];
        array[j + 1] = temp;
        swapped = true;
      }
    }
    if(!swapped) break;
  }
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