/**
 * @file medal.c
 * @author Rodrigo Baptista (202200217@estudantes.ips.pt)
 * @brief Provides an implementation of medal.h.
 * 
 * Allows for creating medals and getting their information.
 * Does not provide modifying functions.
 * 
 * @version 1
 * @date 2024-08-09
 * 
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "medal.h"

static CountryMedal countryMedalCreate(char *country);

static char characterMap(char *type);

Medal medalCreate(char *discipline, char *game, char *eventTitle, char *gender, char *medalType, char *participantType, char *athleteId, char *country) {
  Medal m;
  strcpy(m.discipline, discipline);
  strcpy(m.game, game);
  strcpy(m.eventTitle, eventTitle);
  strcpy(m.gender, gender);
  m.medalType = characterMap(medalType);
  m.participantType = characterMap(participantType);
  strcpy(m.athleteID, athleteId);
  strcpy(m.country, country);
  return m;
}

void medalPrint(PtMedal medal) {
  if (medal == NULL) return;

  printf("Medal: {\n");
  printf("\tDiscipline: %s\n", medal->discipline);
  printf("\tGame: %s\n", medal->game);
  printf("\tEvent Title: %s\n", medal->eventTitle);
  printf("\tGender: %s\n", medal->gender);
  printf("\tMedal Type: %c\n", medal->medalType);
  printf("\tParticipant Type: %c\n", medal->participantType);
  printf("\tAthlete ID: %s\n", medal->athleteID);
  printf("\tCountry: %s\n", medal->country);
  printf("}\n");
}

void medalType(PtMedal medal, char *type) {
  if(medal->medalType == 'G') strcpy(type, "Gold");
  if(medal->medalType == 'S') strcpy(type, "Silver");
  if(medal->medalType == 'B') strcpy(type, "Bronze");
}

MedalAccumulator medalAccumulatorCreate(char *discipline) {
  MedalAccumulator ma;
  strcpy(ma.discipline, discipline);
  ma.countries = (CountryMedal*) malloc(sizeof(CountryMedal));
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

static char characterMap(char *type) {
  if(strcmp(type, "GOLD") == 0) return 'G';
  if(strcmp(type, "SILVER") == 0) return 'S';
  if(strcmp(type, "BRONZE") == 0) return 'B';
  if(strcmp(type, "Athlete") == 0) return 'A';
  if(strcmp(type, "GameTeam") == 0) return 'G';
  return ' ';
}