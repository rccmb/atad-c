/**
 * @file stringWrap.c
 * @author IPS
 * @brief Provides an implementation of stringWrap.h.
 * 
 * Allows for the "creation" of statically allocated strings.
 * 
 * @version 1
 * @date 2024-08-11
 * 
 */

#include <string.h>

#include "stringWrap.h"

StringWrap stringWrapCreate(char *str) {
  StringWrap sw;
  strcpy(sw.text, str);
  return sw;
}