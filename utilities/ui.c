/**
 * @file ui.c
 * @author Rodrigo Baptista (202200217@estudantes.ips.pt)
 * @brief Provides an implementation of ui.h.
 * 
 * Handles printing.
 * 
 * @version 1
 * @date 2024-08-10
 * 
 */

#include "ui.h"

#include <stdio.h>

void printMenu() {
  printf("Command               | Description\n");
  printf("-------               | -----------\n");
  printf("HELP                  | Shows the command menu.\n");
  printf("LOAD_A                | Loads athlete information.\n");
  printf("LOAD_M                | Loads medal information.\n");
  printf("LOAD_H                | Loads host information.\n");
  printf("CLEAR                 | Clears all stored information.\n");
  printf("QUIT                  | Quits the program.\n");
  printf("SHOW_ALL              | Shows all athletes ordered by name.\n");
  printf("SHOW_PARTICIPATIONS   | Shows athletes that participated, at least, once.\n");
  printf("SHOW_FIRST            | Shows athletes whose first participation was in a year.\n");
  printf("SHOW_HOST             | Shows information about a host.\n");
  printf("DISCIPLINE_STATISTICS | Shows disciplines information for an Olympic Games edition.\n");
  printf("ATHLETE_INFO          | Shows information about an athlete.\n");
  printf("TOPN                  | Shows athletes with most won medals.\n");
  printf("MEDALS_WON            | Shows information about medals won by a country in 5 successive editions.\n");
}