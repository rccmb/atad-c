/**
 * @file athleteMedals.h
 * @author Rodrigo Baptista (202200217@estudantes.ips.pt)
 * @brief Provides the AthleteMedals code module. Type definition and functions.
 *
 * NOTE: This type is used as a support data structure for the TOPN command.
 * 
 * @version 1
 * @date 2024-09-10
 * 
 */

#pragma once

#include <stdbool.h>
#include "athlete.h"
#include "medal.h"

// TODO DOCS
typedef struct country {
  char country[MAX_COUNTRY_LENGTH];
  int year;
} Country;

// TODO DOCS
typedef struct edition {
  char edition[MAX_GAME_LENGTH];
  int medalCount;
} Edition;

// TODO DOCS
typedef struct athleteMedals {
  char athleteID[MAX_ID_LENGTH]; // Athlete ID.
  int medalCount; // The amount of medals this athlete won.
  Country *countries;
  int countriesSize;
  Edition *editions;
  int editionsSize;
} AthleteMedals;

/** Definition of pointer to the data stucture. */
typedef struct athleteMedals *PtAthleteMedals;

// TODO DOCS
AthleteMedals athleteMedalsCreate(char *athleteID);

// TODO DOCS
bool athleteMedalsAddMedal(AthleteMedals *am, PtMedal medal); 