/**
 * @file medal.c
 * @author Rodrigo Baptista (202200217@estudantes.ips.pt)
 * @brief Provides an implementation of medal.h.
 * 
 * Allows for creating medals and getting their information.
 * Does not provide modifying functions.
 * 
 * @version 1
 * @date 2024-08-09
 * 
 */

#include "medal.h"

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