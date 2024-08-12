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
#include "processing/athleteShow.h"
#include "input.h"

#define COMMAND_LENGTH 32

int main() {

    printf("Olympic Games Data Analysis\n");
    printf("---------------------------\n");

    printMenu();

    PtList athletes = NULL;
    PtList alphabeticAthletes = NULL;

    while(true) {
        char command[COMMAND_LENGTH];
        printf("MENU Command > ");
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
            listDestroy(&alphabeticAthletes);
            clear(&athletes);
        }
        
        else if(strcmpins(command, "QUIT") == 0) {
            listDestroy(&alphabeticAthletes);
            quit(&athletes);
            break;
        } 

        else if(strcmpins(command, "SHOW_ALL") == 0) {
            checkOrderedAthletesLoaded(athletes, &alphabeticAthletes);
            showAll(alphabeticAthletes);
        }
        
        else if(strcmpins(command, "SHOW_PARTICIPATIONS") == 0) {
            checkOrderedAthletesLoaded(athletes, &alphabeticAthletes);
            showParticipations(alphabeticAthletes);
        } 

        else if(strcmpins(command, "SHOW_FIRST") == 0) {
            checkOrderedAthletesLoaded(athletes, &alphabeticAthletes);
            showFirst(alphabeticAthletes);
        } 

        else printf("Invalid command inserted. Use HELP to view all available commands.\n");
    }

    printf("-----------------------------------------------\n");
    printf("Thank you for using Olympic Games Data Analysis\n");
    
    return EXIT_SUCCESS;
}



