/**
 * @file medalsWon.c
 * @author Rodrigo Baptista (202200217@estudantes.ips.pt)
 * @brief Provides an implementation of medalsWon.h.
 *
 * @version 1
 * @date 2024-09-11
 * 
 */

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "medal.h"

#include "medalsWon.h"

static void populateCategories(PtMedalsWon medalsWon);

MedalsWon medalsWonCreate(char *edition, int year) {
  MedalsWon mw;
  strcpy(mw.edition, edition);
  mw.year = year;
  populateCategories(&mw);
  return mw;
}

bool medalsWonAddMedal(PtMedalsWon medalsWon, PtMedal medal) {
  if(medalsWon == NULL || medal == NULL) return false;

  for(int i = 0; i < 3; i++) {
    if(medalsWon->categories[i].category == medalGender(medal)) { 
      if(medal->medalType == 'G') {
        medalsWon->categories[i].gold += 1;
        return true;
      }
      if(medal->medalType == 'S') {
        medalsWon->categories[i].silver += 1;
        return true;
      }
      if(medal->medalType == 'B') {
        medalsWon->categories[i].bronze += 1;
        return true;
      }
    }
  }

  return true;
}

static void populateCategories(PtMedalsWon medalsWon) {
  medalsWon->categories = (Category*) calloc(3, sizeof(Category));
  if(medalsWon->categories == NULL) return;

  medalsWon->categories[0].category = 'M';
  medalsWon->categories[1].category = 'W';
  medalsWon->categories[2].category = 'X';
}