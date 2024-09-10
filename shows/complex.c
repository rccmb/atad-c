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
#include "../types/medal.h"
#include "../adts/map.h"
#include "../types/athlete.h"
#include "../types/athleteMedals.h"
#include "../adts/set.h"
#include "../adts/list.h"

#include "complex.h"

void showAthleteInfo(PtList athletes, PtMedalList medals, char *athleteId) {
  if(athletes == NULL || medals->elements == NULL) return;
  
  Athlete athlete;
  bool result = getAthlete(athletes, athleteId, &athlete);

  if(result == false) {
    printf("Athlete %s does not exist.\n", athleteId);
    return;
  }

  Medal* entries = (Medal*) malloc(sizeof(Medal));
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

  PtSet validHosts = setCreate();
  Host* validHostsValues = (Host*) malloc(sizeof(Host));
  int validHostsValuesSize = 0;
  if(validHosts == NULL || validHostsValues ==  NULL) {
    printf("[TOPN] Something went wrong initializing the valid hosts set or array.\n");
    // TODO DESTROY
    return;
  }

  Host* hostsValues = mapValues(hosts);
  int sz = 0;
  mapSize(hosts, &sz);
  for(int i = 0; i < sz; i++) {
    if(
      strcmpins(hostsValues[i].gameSeason, season) == 0
      && start <= datetimeYear(&(hostsValues[i].gameStartDate))
      && end >= datetimeYear(&(hostsValues[i].gameEndDate))
    ) {
      StringWrap swrGameSlug = stringWrapCreate(hostsValues[i].gameSlug);
      int result = setAdd(validHosts, swrGameSlug);
      if(result != SET_OK && result != SET_DUPLICATE) {
        printf("[TOPN] Failed to add value to valid hosts set.\n");
        // TODO DESTROY
        return;
      } else {
        validHostsValues = (Host*) realloc(validHostsValues, sizeof(Host) * (validHostsValuesSize + 1));
        if(validHostsValues == NULL) {
          printf("[TOPN] Something went wrong realloc'ing the valid hosts array.\n");
          // TODO DESTROY
          return;
        }
        validHostsValues[validHostsValuesSize++] = hostsValues[i];
      }
    }
  }

  PtSet validAthletes = setCreate();
  AthleteMedals *athleteMedals = (AthleteMedals*) malloc(sizeof(AthleteMedals));
  int athleteMedalsSize = 0;
   if(validAthletes == NULL || athleteMedals ==  NULL) {
    printf("[TOPN] Something went wrong initializing the valid athletes set or athlete medals array.\n");
    // TODO DESTROY
    return;
  }

  for(int i = 0; i < medals->size; i++) {
    if(strcmp(medals->elements[i].athleteID, "") != 0) {
      StringWrap swrEdition = stringWrapCreate(medals->elements[i].game);
      if(setContains(validHosts, swrEdition)) {
        StringWrap swrAthId = stringWrapCreate(medals->elements[i].athleteID);
        if(setContains(validAthletes, swrAthId)) {
          for(int j = 0; j < athleteMedalsSize; j++) {
            if(strcmp(athleteMedals[j].athleteID, medals->elements[i].athleteID) == 0) {
              bool added = athleteMedalsAddMedal(&(athleteMedals[j]), &(medals->elements[i]));
              if(!added) {
                printf("[TOPN] Something went wrong adding medal to EXISTING athlete medals.\n");
                // TODO DESTROY
                return;
              }
              break;
            }
          }
        } else {
          setAdd(validAthletes, swrAthId);

          athleteMedals = (AthleteMedals*) realloc(athleteMedals, sizeof(AthleteMedals) * (athleteMedalsSize + 1));
          if(athleteMedals == NULL) {
            printf("[TOPN] Something went wrong initializing the valid athletes set or athlete medals array.\n");
            // TODO DESTROY
            return;
          }
          
          athleteMedals[athleteMedalsSize] = athleteMedalsCreate(medals->elements[i].athleteID);
          bool added = athleteMedalsAddMedal(&(athleteMedals[athleteMedalsSize]), &(medals->elements[i]));
          athleteMedalsSize++;
          if(!added) {
            printf("[TOPN] Something went wrong adding medal to FRESH athlete medals.\n");
            // TODO DESTROY
            return;
          }
        }
      }
    }
  }



  for(int i = athleteMedalsSize - 1; i >= 0; i--) {
    printf("%d -> %s %d\n", i, athleteMedals[i].athleteID, athleteMedals[i].medalCount);
  }

  setDestroy(&validHosts);
  free(validHostsValues);
  free(hostsValues);
}