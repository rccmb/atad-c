/**
 * @file helper.h
 * @author Rodrigo Baptista (202200217@estudantes.ips.pt)
 * @brief Provides helper functions.
 * 
 * @version 1
 * @date 2024-08-10
 * 
 */

#pragma once

/**
 * @brief Compare two strings, case insensitive.
 * 
 * @param str1 [in] String 1 to compare.
 * @param str2 [in] String 2 to compare.
 * 
 * @return 0 if the strings are equal.
 * @return >0 if the first non-matching character in str1 is greater (lowercased) than that of str2.
 * @return <0 if the first non-matching character in str1 is lower (lowercased) than that of str2.
 */
int strcmpins(char *str1, char *str2);