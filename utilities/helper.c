/**
 * @file helper.c
 * @author Rodrigo Baptista (202200217@estudantes.ips.pt)
 * @brief Provides an implementation of helper.h.
 * 
 * Commonly used operations throughout the program.
 * 
 * @version 1
 * @date 2024-08-10
 * 
 */

#include "helper.h"

#include <ctype.h>

int strcmpins(char *str1, char *str2) {
  while(*str1 != '\0' || *str2 != '\0') {
    char a = tolower(*str1);
    char b = tolower(*str2);

    if(a != b) return a > b ? 1 : -1; 
    if(a == '\0' && b == '\0') return 0;

    str1++; 
    str2++;
  }

  return 0;
}