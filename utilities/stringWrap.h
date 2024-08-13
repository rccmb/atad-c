/**
 * @file stringWrap.h
 * @author IPS
 * @brief Simplifies the usage of Strings in collections.
 * 
 * @version 1
 * @date 2024-08-11
 * 
 */

#pragma once

#define STRING_MAX_LEN 100

typedef struct stringWrap {
  char text[STRING_MAX_LEN];
} StringWrap;

/**
 * @brief Creates a StringWrap.
 * 
 * @param str [in] Value of the string.
 * 
 * @return StringWrap with the associated string.
 */
StringWrap stringWrapCreate(char *str);