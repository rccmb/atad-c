/**
 * @file medalAccumulator.h
 * @author Rodrigo Baptista (202200217@estudantes.ips.pt)
 * @brief Provides the MedalAccumulator code module. Type definition and functions.
 *
 * NOTE: This type is used as a support data structure for the DISCIPLINE_STATISTICS command.
 * 
 * @version 1
 * @date 2024-09-10
 * 
 */

#pragma once

#include <stdbool.h>
#include "medal.h"

typedef struct countryMedal {
  char country[MAX_COUNTRY_LENGTH]; // Country name.
  int medalCount; // Medal count of this country.
} CountryMedal;

typedef struct countryMedal *PtCountryMedal;

typedef struct medalAccumulator {
  char discipline[MAX_DISC_LENGTH]; // Discipline associated with this medal accumulator.
  CountryMedal *countries; // Countries with medals in this discipline.
  int countriesSize; // Size of the countries array.
  int women; // Number of women with medals. (Mixed do not count).
  int totalParticipants; // Number of total participants.
} MedalAccumulator;

// TODO DOCS
typedef struct medalAccumulator *PtMedalAccumulator;

/**
 * @brief Creates a medal accumulator. Auxiliary structure for DISCIPLINE_STATISTICS.
 * 
 * @param discipline [in] The name of the discipline associated with this accumulator.
 *
 * @return A new MedalAccumulator.
 */
MedalAccumulator medalAccumulatorCreate(char *discipline);

// TODO DOCS
bool medalAccumulatorAddMedal(PtMedalAccumulator accum, PtMedal medal);

// TODO DOCS
void accumulatorPrint(PtMedalAccumulator accum);