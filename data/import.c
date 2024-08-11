/**
 * @file import.c
 * @author Rodrigo Baptista (202200217@estudantes.ips.pt)
 * @brief Provides an implementation of import.h.
 * 
 * Imports athlete information, medal information and host information from corresponding CSV files.
 * The CSV file should be present in the same directory.
 * 
 * @version 1
 * @date 2024-08-10
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../list.h"
#include "import.h"

PtList load_a(int *size) {
  FILE *stream = fopen("athletes.csv", "r");

  if(stream == NULL) return NULL;
}

PtMedal load_m(int *size) {

}

PtHost load_h(int *size) {
  
}