#include <stdio.h> 
#include <stdlib.h>

#include "list.h"
#include "data/import.h"
#include "utilities/ui.h"
#include "utilities/helper.h"
#include "types/athlete.h"
#include "types/medal.h"
#include "types/host.h"
#include "memory.h"
#include "input.h"

#define COMMAND_LENGTH 32

int main() {

    printf("Olympic Games Data Analysis\n");
    printf("---------------------------\n");

    printMenu();

    // TODO Adapt assigments to:
    // Athletes -> List.
    // Medals -> Dynamic Array.
    // Hosts -> Map.
    PtList athletes = NULL;

    while(true) {
        char command[COMMAND_LENGTH];
        printf("Command > ");
        readString(command, COMMAND_LENGTH);
        
        if(strcmpins(command, "HELP") == 0) printMenu();
        
        else if(strcmpins(command, "LOAD_A") == 0) {
            if(athletes == NULL) athletes = loadAthletes();
            else printf("Athletes were already imported, use CLEAR to clear them from memory.\n");
        }
        
        else if(strcmpins(command, "LOAD_M") == 0) {
            // TODO
        } 
        
        else if(strcmpins(command, "LOAD_H") == 0) {
            // TODO
        } 
        
        else if(strcmpins(command, "CLEAR") == 0) {
            clear(&athletes);
        } 
        
        else if(strcmpins(command, "QUIT") == 0) {
            quit(&athletes);
            break;
        } 

        else {
            printf("Invalid command inserted. Use HELP to view all available commands.\n");
        }
    }

    printf("-----------------------------------------------\n");
    printf("Thank you for using Olympic Games Data Analysis\n");
    
    return EXIT_SUCCESS;
}



