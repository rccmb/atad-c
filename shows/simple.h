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
 */
void showParticipations(PtList athletes);

/**
 * @brief Shows all athletes in the provided list filtered by first year participated.
 * 
 * @param athletes [in] The list of athletes.
 */
void showFirst(PtList athletes);