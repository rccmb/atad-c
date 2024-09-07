/**
 * @file medal.h
 * @author Rodrigo Baptista (202200217@estudantes.ips.pt)
 * @brief Provides the Medal code module. Type definition and functions.
 * 
 * @version 1
 * @date 2024-08-09
 * 
 */

#pragma once

#define MAX_DISC_LENGTH 50
#define MAX_GAME_LENGTH 50
#define MAX_EVENT_LENGTH 100
#define MAX_ID_A_LENGTH 50
#define MAX_COUNTRY_LENGTH 50
#define MAX_GENDER 20

typedef struct medal {
  char discipline[MAX_DISC_LENGTH]; // Modalidade.
  char game[MAX_GAME_LENGTH]; // Nome da edição dos jogos olímpicos.
  char eventTitle[MAX_EVENT_LENGTH]; // Título da prova. 
  char gender[MAX_GENDER]; // Género da prova.
  char medalType; // G - GOLD, S - SILVER, B - BRONZE
  char participantType; // A - Athlete, G - GameTeam
  char athleteID[MAX_ID_A_LENGTH]; // Identificador de cada atleta.
  char country[MAX_COUNTRY_LENGTH]; // País pelo qual o atleta competiu.
} Medal;

typedef struct medal *PtMedal;

typedef struct medalList {
  PtMedal elements; // Elements inside the medal list.
  int size; // Current size of the medal list.
} MedalList;

typedef struct medalList *PtMedalList;

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

typedef struct medalAccumulator *PtMedalAccumulator;

/**
 * @brief Adds a medal to the medal list.
 * 
 * @param discipline [in] Discipline of the medal.
 * @param game [in] Edition of the olympic games.
 * @param eventTitle [in] The event title.
 * @param gender [in] Gender of the event.
 * @param medalType [in] Medal type. G - Gold, S - Silver, B - Bronze.
 * @param participant [in] The type of participant. A - Athlete, G - GameTeam
 * @param athleteId [in] Athlete that won this medal.
 * @param country [in] Country of the athlete.
 *
 * @return Medal that holds the provided information.
 */
Medal medalCreate(char *discipline, char *game, char *eventTitle, char *gender, char *medalType, char *participantType, char *athleteId, char *country);

/**
 * @brief Prints the information of a medal.
 * 
 * @param medal Pointer to a medal.
 */
void medalPrint(PtMedal medal);

/**
 * @brief Receives a medal and returns it's type in extended form. 
 *
 * A medal whose type is 'G', will return "Gold".
 * 
 * @param medal Pointer to a medal.
 */
void medalType(PtMedal medal, char *type);

/**
 * @brief Creates a medal accumulator. Auxiliary structure for DISCIPLINE_STATISTICS.
 * 
 * @param discipline [in] The name of the discipline associated with this accumulator.
 *
 * @return A new MedalAccumulator.
 */
MedalAccumulator medalAccumulatorCreate(char *discipline);

// TODO
bool medalAccumulatorAddMedal(PtMedalAccumulator accum, PtMedal medal);

// TODO
void accumulatorPrint(PtMedalAccumulator accum);