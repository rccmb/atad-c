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

// TODO Documentation.
void orderAthletes(PtList athletes);

// TODO Documentation.
void paginate(PtList athletes);

// TODO Documentation.
void showAll(PtList athletes);

// TODO Documentation.
void showParticipations(PtList athletes, int participationCount);

// TODO Documentation.
void showFirst(PtList athletes, int firstYear);

// TODO Documentation.
PtList athleteListCopy(PtList athletes);

// TODO Documentation.
void checkOrderedAthletesLoaded(PtList athletes, PtList *athletesCopy);