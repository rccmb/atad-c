/**
 * @file complex.h
 * @author Rodrigo Baptista (202200217@estudantes.ips.pt)
 * @brief Provides an implementation of complex.h.
 * 
 * Complex SHOW functions, require multiple datasets.
 *
 * @version 1
 * @date 2024-08-24
 * 
 */

#pragma once

#include "../types/athlete.h"
#include "../types/medal.h"

/**
 * @brief Shows the info of an athlete.
 * 
 * @param athletes [in] List of athletes.
 * @param medals [in] List of medals.
 * @param athleteId [in] ID of the athlete whose info will be shown.
 */
void showAthleteInfo(PtList athletes, MedalList *medals, char *athleteId);