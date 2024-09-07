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
  int entriesSize = 0;

  char athleteCountry[MAX_COUNTRY_LENGTH];

  for(int i = 0; i < medals->size; i++) {
    if(strcmp(medals->elements[i].athleteID, athleteId) == 0) {
      if(entriesSize == 0) strcpy(athleteCountry, medals->elements[i].country);
      entries = (Medal*) realloc(entries, sizeof(Medal) * (entriesSize + 1));
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
  if(validHosts == NULL) {
    printf("[TOPN_HOSTS] Something went wrong initializing the hosts set.\n");
    return;
  }

  Host* hostsValues = mapValues(hosts);
  int sz = 0;
  mapSize(hosts, &sz);
  for(int i = 0; i < sz; i++) {
    if(
      strcmpins(hostsValues[i].gameSeason, season) == 0
      && start >= datetimeYear(&(hostsValues[i].gameStartDate))
      && end <= datetimeYear(&(hostsValues[i].gameEndDate))
    ) {
      StringWrap swrGameSlug = stringWrapCreate(hostsValues[i].gameSlug);
      int result = setAdd(validHosts, swrGameSlug);
      if(result != SET_OK && result != SET_DUPLICATE) {
        printf("[TOPN_HOSTS] Failed to add value to valid hosts set.\n");
        setDestroy(&validHosts);
        return;
      }
    }
  }

  PtSet validAthletes = setCreate();

  int validHostsSize = 0;
  setSize(validHosts, &validHostsSize);

  AthleteMedals* athMed = (AthleteMedals*) malloc(sizeof(AthleteMedals) * validHostsSize);
  int athMedSize = 0;
  if(athMed == NULL) {
    // TODO ERROR.
  }

  for(int i = 0; i < medals->size; i++) {
    StringWrap swrHost = stringWrapCreate(medals->elements[i].game)
    if(setContains(validHosts, swrHost)) {
      StringWrap swrAthlete = stringWrapCreate(medals->elements[i].athleteID);
      if(setContains(validAdthletes, swrAthlete)) {
        for(int j = 0; j < athMedSize; j++) {
          if(strcmp(athMed[j].athleteID, medals->elements[i].athleteID) == 0) {
            athMed[j].medalCount++;
            
            bool found = false;
            for(int k = 0; k < athMed[j].countriesSize; k++) {
              if(strcmp(medals->elements[i].country, athMed[j].countries[k].country) == 0) {
                // TODO CHECK YEAR.
                found = true;
              }
            }

            if(!found) {
              athMed[j].countries = (Country*) realloc(athMed[j].countries, sizeof(Country) * (athMed[j].countriesSize + 1));
              if(athMed[j].countries == NULL) {
                // TODO ERROR.
              }

              athMed[j].countries[athMed[j].countriesSize++] = athleteCountryCreate(medals->elements[i].country, 0); // TODO FIX YEAR.
            }
          }
        }
      } else {
        int result = setAdd(validAthletes, swrAthlete);
        if(result != SET_OK) {
          // TOOD ERROR.
        }

        athMed[athMedSize] = athleteMedalsCreate(medals->elements[i].athleteID);
        athMed[athMedSize++].medalCount++;

        athMed[j].countries = (Country*) realloc(athMed[j].countries, sizeof(Country) * (athMed[j].countriesSize + 1));
        athMed[j].countries[athMed[j].countriesSize++] = athleteCountryCreate(medals->elements[i].country, 0); 
        if(athMed[j].countries == NULL) {
          // TODO ERROR.
        }
      }
    }
  }

  athMed = (AthleteMedals*) realloc(athMed, sizeof(AthleteMedals) * athMedSize);
  
  // TODO DESTROY ATHMED.

  setDestroy(&validHosts);
  setDestroy(&validAthletes);
  free(hostsValues);
  free(validHosts);
}