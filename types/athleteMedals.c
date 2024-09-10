/**
 * @file athleteMedals.c
 * @author Rodrigo Baptista (202200217@estudantes.ips.pt)
 * @brief Provides an implementation of athleteMedals.h.
 *
 * @version 1
 * @date 2024-09-10
 * 
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "athleteMedals.h"

static Country athleteMedalsCreateCountry(char *game, char *country);

static Edition athleteMedalsCreateEdition(char *game);

static int getYearFromSlug(char *slug);

AthleteMedals athleteMedalsCreate(char *athleteID) {
  AthleteMedals am;
  strcpy(am.athleteID, athleteID);
  am.medalCount = 0;
  am.countries = (Country*) malloc(sizeof(Country));
  am.countriesSize = 0;
  am.editions = (Edition*) malloc(sizeof(Edition));
  am.editionsSize = 0;
  return am;
}

bool athleteMedalsAddMedal(AthleteMedals *am, PtMedal medal) {
  if(am == NULL || medal == NULL) return false;

  am->medalCount++;

  bool found = false;
  for(int i = 0; i < am->countriesSize; i++) {
    if(strcmp(am->countries[i].country, medal->country) == 0) {
      found = true;
      int countryYear = getYearFromSlug(medal->game);
      if(am->countries[i].year > countryYear) {
        am->countries[i].year = countryYear; 
      }
    }
  }

  if(!found) {
    am->countries = (Country*) realloc(am->countries, sizeof(Country) * (am->countriesSize + 1));
    if(am->countries == NULL) return false;
    am->countries[am->countriesSize++] = athleteMedalsCreateCountry(medal->game, medal->country);
  }

  found = false;
  for(int i = 0; i < am->editionsSize; i++) {
    if(strcmp(am->editions[i].edition, medal->game) == 0) {
      found = true;
      am->editions[i].medalCount++;
    }
  }

  if(!found) {
    am->editions = (Edition*) realloc(am->editions, sizeof(Edition) * (am->editionsSize + 1));
    if(am->editions == NULL) return false;
    am->editions[am->editionsSize++] = athleteMedalsCreateEdition(medal->game);
  }

  return true;
}

static Country athleteMedalsCreateCountry(char *game, char *country) {
  Country co;
  strcpy(co.country, country);
  co.year = getYearFromSlug(game);
  return co;
}

static Edition athleteMedalsCreateEdition(char *game) {
  Edition ed;
  strcpy(ed.edition, game);
  ed.medalCount = 1;
  return ed;
}

static int getYearFromSlug(char *slug) {
  char year[5]; 
  int yearPos = strlen(slug) - 4;
  strncpy(year, slug + yearPos, 4);
  year[4] = '\0';
  int y = atoi(year);
  return y;
}