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
#include "../adts/map.h"
#include "../types/medal.h"

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
 * If there is no ordered athletes list in memory, it loads it.
 * Saves execution time by not having to repeatedly order athletes by name.
 * 
 * @param athletes [in] The list of athletes to copy.
 * @param athletesCopy [out] Address of the list to hold the ordered athletes, only modified if it's already NULL.
 */
void checkOrderedAthletesLoaded(PtList athletes, PtList *athletesCopy);

/**
 * @brief Extracts the date from a string. 1952-08-03T07:00:00Z -> 1952-08-03
 *
 * It is assumed that the string is well formated. "YYYY-MM-DDTHH:MM:SSZ"
 * 
 * @param datetime [in] String with the date and hour.
 * @param date [in] String to hold only the date.
 */
void extractDate(char *datetime, char *date);

/**
 * @brief Extracts the city from a string with a year. Helsinki 1952 -> Helsinki
 *
 * It is assumed that the string is well formated. "CITY YEAR"
 * 
 * @param cityyear [in] String with the city and year.
 * @param city [in] String to hold the city.
 */
void extractCity(char *cityyear, char *city);

/**
 * @brief Gets an athlete with the given ID from an athlete list.
 * 
 * @param athletes [in] List of athletes.
 * @param athleteId [in] String with the ID of the athlete.
 * @param ath [out] Adress to hold the found athlete.
 */
bool getAthlete(PtList athletes, char *athleteId, PtAthlete ath);

/**
 * @brief Check if the given athlete list is null.
 * 
 * @param athletes [in] Athlete list.
 * 
 * @return true if the given athlete list is null, or
 * @return false if the given athlete list is not null.
 */
bool athletesIsNull(PtList athletes);

/**
 * @brief Check if the given medal list is null.
 * 
 * @param medals [in] Medal list.
 * 
 * @return true if the given medal list is null, or
 * @return false if the given medal list is not null.
 */
bool medalsIsNull(PtMedalList medals);

/**
 * @brief Check if the given hosts map is null.
 * 
 * @param hosts [in] Hosts map.
 * 
 * @return true if the given hosts map is null, or
 * @return false if the given hosts map is not null.
 */
bool hostsIsNull(PtMap hosts);

/**
 * @brief Gets the year from a game edition.
 * 
 * @param slug [in] Name of the game edition.
 * 
 * @return Integer with the year.
 */
int getYearFromSlug(char *slug);