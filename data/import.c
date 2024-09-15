/**
 * @file import.c
 * @brief Provides an implementation of import.h.
 * 
 * Imports athlete information, medal information and host information from corresponding CSV files.
 * 
 * @version 1
 * @date 2024-08-10
 * 
 * @author Rodrigo Baptista (202200217@estudantes.ips.pt)
 * @bug No known bugs.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../utilities/helper.h"
#include "../types/stringWrap.h"
#include "../utilities/input.h"
#include "../types/athlete.h"
#include "../types/medal.h"
#include "../types/host.h"
#include "../adts/list.h"
#include "../adts/map.h"

#include "import.h"

static int fileLength(char *name); 

PtList loadAthletes() {
  FILE *stream = fopen("data/athletes.csv", "r"); // Relative to main.

  if(stream == NULL) {
    printf("Athletes file not found.");
    return NULL;
  }

  PtList list = listCreate();
  if(list == NULL) {
    printf("Something went wrong allocating the athlete list. Try again...\n");
    return NULL;
  }

  int count = 0;
  char line[1024];
  fgets(line, 1024, stream);
  printf("Importing athletes...\n");
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

void loadMedals(PtMedalList medals) {
  int lines = fileLength("data/medals.csv");

  FILE *stream = fopen("data/medals.csv", "r"); // Relative to main.

  if(stream == NULL) {
    printf("Medals file not found.");
    return;
  }

  medals->elements = (PtMedal) calloc(lines, sizeof(Medal));

  int count = 0;
  char line[1024];
  fgets(line, 1024, stream);
  printf("Importing medals...\n");
  while(fgets(line, 1024, stream)) {

    char *tmp = strdup(line);  
    char **tokens = splitString(tmp, 11, ";");  

    Medal medal = medalCreate(
      tokens[0], // discipline_title
      tokens[1], // slug_game
      tokens[2], // event_title
      tokens[3], // event_gender
      tokens[4], // medal_type
      tokens[5], // participant_type
      tokens[7], // athlete_id
      tokens[8] // country_name
    );

    medals->elements[count++] = medal;

    free(tmp);
    free(tokens);
  }

  medals->size = count;

  medals->size > 0
    ? printf("<%d> Medal records imported.\n", medals->size)
    : printf("No medal records imported!\n");

  fclose(stream);
}

PtMap loadHosts() {
  FILE *stream = fopen("data/hosts.csv", "r"); // Relative to main.

  if(stream == NULL) {
    printf("Hosts file not found.");
    return NULL;
  }

  PtMap map = mapCreate();
  if(map == NULL) {
    printf("Something went wrong allocating the host map. Try again...\n");
    return NULL;
  }

  int count = 0;
  char line[1024];
  fgets(line, 1024, stream);
  printf("Importing hosts...\n");
  while(fgets(line, 1024, stream)) {

    char *tmp = strdup(line);  
    char **tokens = splitString(tmp, 7, ";");

    DateTime endDate = datetimeCreate(tokens[1]);
    DateTime startDate = datetimeCreate(tokens[2]);
    
    Host h = hostCreate(
      tokens[0],
      endDate,
      startDate,
      tokens[3],
      tokens[4], 
      tokens[5],
      atoi(tokens[6])
    );
    count++;

    StringWrap swr = stringWrapCreate(tokens[0]);
    mapPut(map, swr, h);

    free(tmp);
    free(tokens);
  }

  count > 0
    ? printf("<%d> Host records imported.\n", count)
    : printf("No host records imported!\n");

  fclose(stream);

  return map;
}

static int fileLength(char *name) {
  FILE *streamLines = fopen(name, "r"); // Relative to main.

  if(streamLines == NULL) {
    printf("File not found.");
    return 0;
  }

  int lines = 0;
  char line[1024];
  fgets(line, 1024, streamLines);
  while(fgets(line, 1024, streamLines)) lines++;

  fclose(streamLines);

  return lines;
}