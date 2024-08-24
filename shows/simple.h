/**
 * @file simple.h
 * @author Rodrigo Baptista (202200217@estudantes.ips.pt)
 * @brief Responsible for all of the commands SHOW commands for the athletes and hosts.
 *
 * Functions only require one dataset per SHOW. Therefore being simple.
 * 
 * @version 1
 * @date 2024-08-09
 * 
 */

#pragma once

#include "../adts/list.h"
#include "../adts/map.h"

/**
 * @brief Shows all athletes in the provided list with no filters.
 * 
 * @param athletes [in] The list of athletes.
 */
void showAll(PtList athletes);

/**
 * @brief Shows all athletes in the provided list filtered by minimum participation count.
 * 
 * @param athletes [in] The list of athletes.
 * @param participationCount [in] The minimum participation count to filter by.
 */
void showParticipations(PtList athletes, int participationCount);

/**
 * @brief Shows all athletes whose first participation was in the provided year.
 * 
 * @param athletes [in] The list of athletes.
 * @param firstYear [in] The first participation year to filter by.
 */
void showFirst(PtList athletes, int firstYear);

/**
 * @brief Shows host relative to the game slug inserted by the user.
 * 
 * @param hosts [in] The map of hosts.
 * @param gameSlug [in] The gameSlug of the host.
 */
void showHost(PtMap hosts, char *gameSlug);