/**
 * @file import.c
 * @author Rodrigo Baptista (202200217@estudantes.ips.pt)
 * @brief Provides an implementation of import.h.
 * 
 * Imports athlete information, medal information and host information from corresponding CSV files.
 * 
 * @version 1
 * @date 2024-08-10
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../utilities/input.h"
#include "../types/athlete.h"
#include "../adts/list.h"
#include "import.h"

PtList loadAthletes() {
  FILE *stream = fopen("data/athletes.csv", "r"); // Relative to main.

  if(stream == NULL) {
    printf("File not found.");
    return NULL;
  }

  PtList list = listCreate();

  int count = 0;
  char line[1024];
  fgets(line, 1024, stream);
  while(fgets(line, 1024, stream)) {

    char *tmp = strdup(line);  
    char **tokens = splitString(tmp, 5, ";");  

    char firstGameYear[5]; 
    int yearPos = strlen(tokens[3]) - 4;
    strncpy(firstGameYear, tokens[3] + yearPos, 4);
    firstGameYear[4] = '\0';
    
    Athlete ath = athleteCreate(
      tokens[0], // athlete_id
      tokens[1], // athlete_full_name
      atoi(tokens[2]), // games_participations
      atoi(firstGameYear), // first_game
      atoi(tokens[4]) // athlete_year_birth
    );

    listAdd(list, count++, ath);

    free(tmp);
    free(tokens);
  }

  count > 0
    ? printf("<%d> Athlete records imported.\n", count)
    : printf("No athlete records imported!\n");

  fclose(stream);

  return list;
}