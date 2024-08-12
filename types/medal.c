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

#define INITIAL_CAPACITY 20

typedef struct medalArrList {
  PtMedal elements;
  int size;
  int capacity;
} MedalArrList;

