/**
 * @file host.h
 * @author Rodrigo Baptista (202200217@estudantes.ips.pt)
 * @brief Provides the Host code module. Type definition and functions.
 * 
 * @version 1
 * @date 2024-08-09
 * 
 */

#pragma once

#define MAX_GAME_SLUG_LENGTH 50
#define MAX_GAME_LOCATION_LENGTH 50
#define MAX_GAME_NAME_LENGTH 50
#define MAX_GAME_SEASON_LENGTH 8

#include "../types/datetime.h"

/** Forward declaration of the data structure. */
typedef struct host {
  char gameSlug[MAX_GAME_SLUG_LENGTH];
  DateTime gameEndDate;
  DateTime gameStartDate;
  char gameLocation[MAX_GAME_LOCATION_LENGTH];
  char gameName[MAX_GAME_NAME_LENGTH];
  char gameSeason[MAX_GAME_SEASON_LENGTH];
  int gameYear;
} Host;

/** Definition of pointer to the data stucture. */
typedef struct host *PtHost;

/**
 * @brief Create a new Host.
 * 
 * @param gameSlug [in] Slug of the game.
 * @param gameEndDate [in] End date of the game. DateTime struct.
 * @param gameStartDate [in] Start date of the game. DateTime struct.
 * @param gameLocation [in] Location of the game.
 * @param gameName [in] Name of the game (city).
 * @param gameSeason [in] Season of the game (Winter / Summer).
 * @param gameYear [in] Year of the game.
 *
 * @return Host with the given information.
 */
Host hostCreate(char *gameSlug, DateTime gameEndDate, DateTime gameStartDate, char *gameLocation, char *gameName, char *gameSeason, int gameYear);

/**
 * @brief Prints the information of a host.
 * 
 * @param host Pointer to a host.
 */
void hostPrint(PtHost host);