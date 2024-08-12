/**
 * @file athleteShow.h
 * @author Rodrigo Baptista (202200217@estudantes.ips.pt)
 * @brief Responsible for all of the commands SHOW commands for the athletes.
 * 
 * @version 1
 * @date 2024-08-09
 * 
 */

#pragma once

#include "../list.h"

/**
 * @brief Orders the given athlete list alphabetically by name.
 * 
 * @param athletes [in] The list of athletes to order.
 */
void orderAthletes(PtList athletes);

/**
 * @brief Prints the provided athlete list in a paginated manner.
 * 
 * @param athletes [in] The list of athletes to print.
 */
void paginate(PtList athletes);

/**
 * @brief Shows all athletes in the provided list with no filters.
 * 
 * @param athletes [in] The list of athletes.
 */
void showAll(PtList athletes);

/**
 * @brief Shows all athletes in the provided list filtered by participation count.
 * 
 * @param athletes [in] The list of athletes.
 * @param participationCount [in] Participation count to filter athletes.
 */
void showParticipations(PtList athletes, int participationCount);

/**
 * @brief Shows all athletes in the provided list filtered by first year participated.
 * 
 * @param athletes [in] The list of athletes.
 * @param firstYear [in] First year the athletes participated in the olympic games.
 */
void showFirst(PtList athletes, int firstYear);

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