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