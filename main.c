#include <stdio.h> 
#include <stdlib.h>

#include "input.h"

#include "types/athlete.h"
#include "types/host.h"
#include "types/medal.h"

#define COMMAND_LENGTH 32

void printMenu();
bool requestCommand();

int main() {

    printf("Olympic Games Data Analysis\n");
    printf("---------------------------\n");

    printMenu();

    while(true) {
        bool command = requestCommand();
    }
    
    return EXIT_SUCCESS;
}

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

bool requestCommand() {
    char command[COMMAND_LENGTH];
    printf("Command > ");
    readString(command, COMMAND_LENGTH);

    switch() {

    }
}