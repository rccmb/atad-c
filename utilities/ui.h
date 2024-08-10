/**
 * @file menu.h
 * @author Rodrigo Baptista (202200217@estudantes.ips.pt)
 * @brief Responsible for handling user interaction.
 * 
 * @version 1
 * @date 2024-08-10
 * 
 */

#pragma once

#include <stdbool.h>

/**
 * @brief Print the menu with the available commands.
 */
void printMenu();

/**
 * @brief Read an integer from standard input.
 * 
 * @return false if the processed command terminates the application.
 * @return true if the processed command allows the application to keep running.
 */
bool requestCommand();