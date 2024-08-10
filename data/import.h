/**
 * @file import.h
 * @author Rodrigo Baptista (202200217@estudantes.ips.pt)
 * @brief Provides data import commands (LOAD_A, LOAD_M, LOAD_H).
 * 
 * @version 1
 * @date 2024-08-10
 * 
 */

#pragma once

#include "../types/athlete.h"
#include "../types/medal.h"
#include "../types/host.h"

PtAthlete load_a(int *size);

PtMedal load_m(int *size);

PtHost load_h(int *size);