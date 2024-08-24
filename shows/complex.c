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
#include "../types/athlete.h"
#include "../adts/list.h"

#include "complex.h"

void showAthleteInfo(PtList athletes, MedalList *medals, char *athleteId) {
  if(athletes == NULL) {
    printf("No Athletes provided. Have you imported them? (LOAD_A)\n");
    return;
  }

  if(medals->elements == NULL) {
    printf("No Medals provided. Have you imported them? (LOAD_M)\n");
    return;
  }
  
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
  }
  else {
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
  }

  free(entries);
}