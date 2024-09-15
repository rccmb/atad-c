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

#define ATHLETE_MEDALS_OK 0
#define ATHLETE_MEDALS_NULL 1 

#include <stdbool.h>
#include "athlete.h"
#include "medal.h"

// Support type to be used in athlete medals.
typedef struct country {
  char country[MAX_COUNTRY_LENGTH]; // Name of the country.
  int year; // First year the athlete in athlete medals participated for this country.
} Country;

// Support type to be used in athlete medals.
typedef struct edition {
  char edition[MAX_GAME_LENGTH]; // Name of the edition.
  int medalCount; // Number of medals the athlete in athlete medals won for this edition.
} Edition;

// Auxiliary structure to be used in TOPN.
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

/**
 * @brief Creates a athlete medals. Auxiliary structure for TOPN.
 * 
 * @param discipline [in] The name of the athlete associated with this athlete medals.
 *
 * @return A new AthleteMedals.
 */
AthleteMedals athleteMedalsCreate(char *athleteID);

/**
 * @brief Adds a medal to an AthleteMedals. Auxiliary structure for TOPN.
 * 
 * @param am [in] Pointer to the athlete medals that will receive the medal.
 * @param medal [in] Pointer to the medal that will be added.
 *
 * @return true if the medal was added successfully.
 * @return false if the medal was not added successfully.
 */
bool athleteMedalsAddMedal(PtAthleteMedals am, PtMedal medal); 