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

/** Medal structure. */
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

/** Definition of pointer to the medal data stucture. */
typedef struct medal *PtMedal;

/** Forward declaration of the medal list data structure. */
struct medalArrList;

/** Definition of pointer to the medal list data stucture. */
typedef struct medalArrList *PtMedalList;