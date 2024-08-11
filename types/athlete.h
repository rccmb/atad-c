/**
 * @file athlete.h
 * @author Rodrigo Baptista (202200217@estudantes.ips.pt)
 * @brief Provides the Athlete code module. Type definition and functions.
 * 
 * @version 1
 * @date 2024-08-09
 * 
 */

#pragma once

#define MAX_ID_LENGTH 50
#define MAX_NAME_LENGTH 100
#define MAX_GAME_LENGTH 50

typedef struct athlete {
  char athleteID[MAX_ID_LENGTH]; // Identificador único do atleta.
  char athleteName[MAX_NAME_LENGTH]; // Nome do atleta.
  int gamesParticipations; // Número de jogos em que participou.
  int yearFirstParticipation; // O ano em que participou pela primeira vez.
  int athleteBirth; // Ano de nascimento.
} Athlete;

/** Definition of pointer to the data stucture. */
typedef struct Athlete *PtAthlete;
