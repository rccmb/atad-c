/**
 * @file stringWrap.c
 * @brief Provides an implementation of stringWrap.h.
 * 
 * Allows for the "creation" of statically allocated strings.
 * 
 * @version 1
 * @date 2024-08-11
 *
 * @author Rodrigo Baptista (202200217@estudantes.ips.pt)
 * @bug No known bugs.
 */

#include <string.h>

#include "stringWrap.h"

StringWrap stringWrapCreate(char *str) {
  StringWrap sw;
  strcpy(sw.text, str);
  return sw;
}