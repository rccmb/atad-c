/**
 * @file host.c
 * @brief Provides an implementation of host.h.
 * 
 * Allows for creating hosts and getting their information.
 * Does not provide modifying functions.
 * 
 * @version 1
 * @date 2024-08-09
 * 
 * @author Rodrigo Baptista (202200217@estudantes.ips.pt)
 * @bug No known bugs.
 */

#include <stdio.h>
#include <string.h>
#include "../types/datetime.h"

#include "host.h"

Host hostCreate(char *gameSlug, DateTime gameEndDate, DateTime gameStartDate, char *gameLocation, char *gameName, char *gameSeason, int gameYear) {
  Host h;
  strcpy(h.gameSlug, gameSlug);
  h.gameEndDate = gameEndDate;
  h.gameStartDate = gameStartDate;
  strcpy(h.gameLocation, gameLocation);
  strcpy(h.gameName, gameName);
  strcpy(h.gameSeason, gameSeason);
  h.gameYear = gameYear;
  return h;
}

void hostPrint(PtHost host) {
  if(host == NULL) return;

  printf("Host: {\n");
  printf("\tGame Slug: %s\n", host->gameSlug);
  printf("\tGame End Date: ");
  datetimePrint(&(host->gameEndDate));
  printf("\tGame Start Date: ");
  datetimePrint(&(host->gameStartDate));
  printf("\tGame Location: %s\n", host->gameLocation);
  printf("\tGame Name: %s\n", host->gameName);
  printf("\tGame Season: %s\n", host->gameSeason);
  printf("\tGame Year: %d\n", host->gameYear);
  printf("}\n");
}