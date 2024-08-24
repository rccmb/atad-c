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
#include <string.h>

#include "medal.h"

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

static char characterMap(char *type) {
  if(strcmp(type, "GOLD") == 0) return 'G';
  if(strcmp(type, "SILVER") == 0) return 'S';
  if(strcmp(type, "BRONZE") == 0) return 'B';
  if(strcmp(type, "Athlete") == 0) return 'A';
  if(strcmp(type, "GameTeam") == 0) return 'G';
  return ' ';
}