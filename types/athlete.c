/**
 * @file athlete.c
 * @author Rodrigo Baptista (202200217@estudantes.ips.pt)
 * @brief Provides an implementation of athlete.h.
 * 
 * Allows for creating athletes and accessing their information.
 * Does not provide modifying functions.
 * 
 * @version 1
 * @date 2024-08-09
 * 
 */

#include <stdio.h>
#include <string.h>

#include "athlete.h"

Athlete athleteCreate(char *athleteID, char *athleteName, int gamesParticipations, int yearFirstParticipation, int athleteBirth) {
  Athlete ath;
  strcpy(ath.athleteID, athleteID);
  strcpy(ath.athleteName, athleteName);
  ath.gamesParticipations = gamesParticipations;
  ath.yearFirstParticipation = yearFirstParticipation;
  ath.athleteBirth = athleteBirth;
  return ath;
}

void athletePrint(PtAthlete ath) {
  if(ath == NULL) return;

  printf("Athlete: {\n");
  printf("\tID: %s\n", ath->athleteID);
  printf("\tName: %s\n", ath->athleteName);
  printf("\tGame Participations: %d\n", ath->gamesParticipations);
  printf("\tFirst Year Participation: %d\n", ath->yearFirstParticipation);
  printf("\tBirth Year: %d\n", ath->athleteBirth);
  printf("}\n");
}