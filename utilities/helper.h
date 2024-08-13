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

#include "../adts/list.h"

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

/**
 * @brief Orders the given athlete list alphabetically by name.
 * 
 * @param athletes [in] The list of athletes to order.
 */
void orderAthletes(PtList athletes);

/**
 * @brief Copies an athlete list.
 * 
 * @param athletes [in] The list of athletes.
 * 
 * @return PtList with the copied list of athletes.
 */
PtList athleteListCopy(PtList athletes);

/**
 * @brief Checks if the provided copy of ordered athletes has been loaded into memory.
 *
 * Saves execution time but not having to repeatedly order athletes by name.
 * 
 * @param athletes [in] The list of athletes to copy.
 * @param athletesCopy [out] Address of the list to hold the ordered athletes, only modified if it's already NULL.
 */
void checkOrderedAthletesLoaded(PtList athletes, PtList *athletesCopy);

/**
 * @brief Extracts the date from a string. 1952-08-03T07:00:00Z -> 1952-08-03
 * 
 * @param datetime [in] String with the hour.
 * @param date [in] String to hold only the date.
 */
void extractDate(char *datetime, char *date);