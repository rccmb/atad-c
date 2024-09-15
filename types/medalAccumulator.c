/**
 * @file medalAccumulator.c
 * @brief Provides an implementation of medalAccumulator.h.
 *
 * @version 1
 * @date 2024-09-10
 *
 * @author Rodrigo Baptista (202200217@estudantes.ips.pt)
 * @bug No known bugs.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "medalAccumulator.h"

static CountryMedal countryMedalCreate(char *country);

MedalAccumulator medalAccumulatorCreate(char *discipline) {
  MedalAccumulator ma;
  strcpy(ma.discipline, discipline);
  ma.countries = (CountryMedal*) calloc(0, sizeof(CountryMedal));
  ma.countriesSize = 0;
  ma.women = 0;
  ma.totalParticipants = 0;
  return ma;
}

bool medalAccumulatorAddMedal(PtMedalAccumulator accum, PtMedal medal) {
  if(accum == NULL || medal == NULL) return false;

  for(int i = 0; i < accum->countriesSize; i++) {
    if(strcmp(accum->countries[i].country, medal->country) == 0) {
      if(strcmp(medal->gender, "Women") == 0) {
        accum->women++;
      }
      accum->totalParticipants++;
      accum->countries[i].medalCount++;
      return true;
    }
  }

  CountryMedal *newCountries = (CountryMedal*) realloc(accum->countries, sizeof(CountryMedal) * (accum->countriesSize + 1));
  if(newCountries == NULL) return false;

  CountryMedal countryMedal = countryMedalCreate(medal->country);

  accum->countries = newCountries;
  accum->countries[accum->countriesSize++] = countryMedal;

  if(strcmp(medal->gender, "Women") == 0) {
    accum->women++;
  }
  accum->totalParticipants++;

  return true;
}

void accumulatorPrint(PtMedalAccumulator accum) {
  printf("%d countries competed in %s:\n", accum->countriesSize, accum->discipline);
  for(int i = 0; i < accum->countriesSize; i++) {
    printf("\t-> %s: %d medals won.\n", accum->countries[i].country, accum->countries[i].medalCount);
  }
  printf("There were %d total participations, of which %d were specifically women.\n", accum->totalParticipants, accum->women);
}

static CountryMedal countryMedalCreate(char *country) {
  CountryMedal cm;
  strcpy(cm.country, country);
  cm.medalCount = 1;
  return cm;
}