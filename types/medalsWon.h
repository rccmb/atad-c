// TODO DOCS ALL

#pragma once

#include <stdbool.h>

#include "medal.h"

typedef struct category {
  char category;
  int gold;
  int silver;
  int bronze;
} Category;

typedef struct category *PtCategory;

typedef struct medalsWon {
  char edition[MAX_GAME_LENGTH];
  int year;
  Category* categories;
} MedalsWon;

typedef struct medalsWon *PtMedalsWon;

MedalsWon medalsWonCreate(char *edition, int year);

bool medalsWonAddMedal(PtMedalsWon medalsWon, PtMedal medal);