/**
 * @file menu.h
 * @author Rodrigo Baptista (202200217@estudantes.ips.pt)
 * @brief Responsible for showing the user interface and printing information.
 * 
 * @version 1
 * @date 2024-08-10
 * 
 */

#pragma once

#include "../types/athleteMedals.h"
#include "../types/medalsWon.h"
#include "../types/medalAccumulator.h"

#define LINE_LENGTH 150

/**
 * @brief Print the menu with the available commands.
 */
void printMenu();

/**
 * @brief Prints the provided athlete list in a paginated manner.
 * 
 * @param athletes [in] The list of athletes to print.
 */
void paginate(PtList athletes);

/**
 * @brief Prints the discipline statistics. Used for DISCIPLINE_STATISTICS.
 * 
 * @param accumulators [in] Accumulators to print.
 * @param size [in] Size of the accumulators.
 * @param gameSlug [in] Game slug.
 */
void uiDisciplineStatistics(PtMedalAccumulator accumulators, int size, char *gameSlug);

/**
 * @brief Prints the given host information. Used for SHOW_HOST.
 * 
 * @param h [in] The host to print.
 */
void uiShowHost(Host h);

/**
 * @brief Prints the given athlete medals information. Used for ATHLETE_INFO.
 * 
 * @param entries [in] The medals the athlete has won.
 * @param athleteId [in] The athletes id.
 * @param athleteCountry [in] The athletes country.
 * @param entriesSize [in] Size of the medals array.
 */
void uiAthleteInfo(PtMedal entries, char *athleteId, char *athleteCountry, int entriesSize);

/**
 * @brief Prints the top N athletes. Used for TOPN.
 * 
 * @param athleteMedals [in] The array of athletes to print.
 * @param size [in] Size of athleteMedals.
 * @param totalDayCount [in] Number to be used when calculating the athletes average medals per day.
 * @param n [in] Maximum number of athletes to print.
 */
void uiTopN(PtAthleteMedals athleteMedals, int size, int totalDayCount, int n);

// TODO
void uiMedalsWon(PtMedalsWon medalsWon, int size);