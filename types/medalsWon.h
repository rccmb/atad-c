/**
 * @file medalsWon.h
 * @author Rodrigo Baptista (202200217@estudantes.ips.pt)
 * @brief Provides the MedalsWon code module. Type definition and functions.
 *
 * NOTE: This type is used as a support data structure for the MEDALS_WON command.
 * 
 * @version 1
 * @date 2024-09-10
 * 
 */

#pragma once

#include <stdbool.h>

#include "medal.h"

typedef struct category {
  char category; // Category. M - Men, W - Women, X - Mixed.
  int gold; // Amount of gold medals.
  int silver; // Amount of silver medals.
  int bronze; // Amount of bronze medals.
} Category;

/** Definition of pointer to the  data stucture. */
typedef struct category *PtCategory;

typedef struct medalsWon {
  char edition[MAX_GAME_LENGTH]; // Edition associated with this medals won.
  int year; // Year os this edition.
  Category* categories; // Categories present in this medals won.
} MedalsWon;

/** Definition of pointer to the  data stucture. */
typedef struct medalsWon *PtMedalsWon;

/**
 * @brief Creates a medals won. Auxiliary structure for MEDALS_WON.
 * 
 * @param edition [in] The name of the edition associated with this medals won.
 * @param year [in] The year of the edition associated with this medals won.
 *
 * @return A new MedalsWon.
 */
MedalsWon medalsWonCreate(char *edition, int year);

/**
 * @brief Adds a medal to the medals won.
 * 
 * @param medalsWon [in] Pointer to the medals won that will receive the medal.
 * @param medal [in] Pointer to the medal that will be added.
 *
 * @return true if the addition was successful.
 * @return false if the addition was unsuccessful.
 */
bool medalsWonAddMedal(PtMedalsWon medalsWon, PtMedal medal);