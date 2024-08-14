/**
 * @file memory.h
 * @author Rodrigo Baptista (202200217@estudantes.ips.pt)
 * @brief Provides heap memory deallocation commands CLEAR, QUIT.
 * 
 * @version 1
 * @date 2024-08-11
 * 
 */

#pragma once

#include "../adts/list.h"
#include "../adts/map.h"
#include "../types/medal.h"

/**
 * @brief Clears allocated memory in the program. 
 * 
 * Clears the three main imported collections:
 * - Athlete List.
 * - Dynamic Medal Array.
 * - Host Map.
 *
 * @param ptAthletes [in] Address of pointer to the athlete list.
 * @param ptHosts [in] Address of pointer to the hosts map.
 * @param ptMedals [in] Pointer to the medals list.
 */
void clear(PtList *ptAthletes, PtMap *ptHosts, PtMedalList medals);

/**
 * @brief Quits the program. Uses clear().
 * 
 * @param ptAthletes [in] Address of pointer to the athlete list.
 * @param ptHosts [in] Address of pointer to the hosts map.
 * @param ptMedals [in] Pointer to the medals list.
 */
void quit(PtList *ptAthletes, PtMap *ptHosts, PtMedalList medals);