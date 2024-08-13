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

/**
 * @brief Imports athlete information.
 * 
 * @return PtList containing all of the imported athletes.
 */
PtList loadAthletes();

/**
 * @brief Imports host information.
 * 
 * @return PtMap containing all of the imported hosts where key is the game slug and value the host structure.
 */
PtMap loadHosts();