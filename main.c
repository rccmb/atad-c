#include <stdio.h> 
#include <stdlib.h>

#include "adts/list.h"
#include "adts/map.h"
#include "data/import.h"
#include "utilities/ui.h"
#include "utilities/helper.h"
#include "types/athlete.h"
#include "types/medal.h"
#include "types/host.h"
#include "data/memory.h"
#include "shows/simple.h"
#include "shows/complex.h"
#include "utilities/input.h"

#define COMMAND_LENGTH 32

int main() {

    printf("Olympic Games Data Analysis\n");
    printf("---------------------------\n");

    printMenu();

    PtList athletes = NULL;
    PtList alphabeticAthletes = NULL;

    MedalList medals;
    medals.elements = NULL;
    medals.size = 0;

    PtMap hosts = NULL;

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
            if(medals.elements == NULL) loadMedals(&medals);
            else printf("Medals were already imported, use CLEAR to clear them from memory.\n");
        } 
        
        else if(strcmpins(command, "LOAD_H") == 0) {
            if(hosts == NULL) hosts = loadHosts();
            else printf("Hosts were already imported, use CLEAR to clear them from memory.\n");
        } 
        
        else if(strcmpins(command, "CLEAR") == 0) {
            listDestroy(&alphabeticAthletes);
            clear(&athletes, &hosts, &medals);
        }
        
        else if(strcmpins(command, "QUIT") == 0) {
            listDestroy(&alphabeticAthletes);
            quit(&athletes, &hosts, &medals);
            break;
        } 

        else if(strcmpins(command, "SHOW_ALL") == 0) {
            checkOrderedAthletesLoaded(athletes, &alphabeticAthletes);
            showAll(alphabeticAthletes);
        }
        
        else if(strcmpins(command, "SHOW_PARTICIPATIONS") == 0) {
            checkOrderedAthletesLoaded(athletes, &alphabeticAthletes);

            int participationCount;
            printf("Participation Count: ");
            readInteger(&participationCount);

            showParticipations(alphabeticAthletes, participationCount);
        } 

        else if(strcmpins(command, "SHOW_FIRST") == 0) {
            checkOrderedAthletesLoaded(athletes, &alphabeticAthletes);

            int firstYear;
            printf("First Participation Year: ");
            readInteger(&firstYear);

            showFirst(alphabeticAthletes, firstYear);
        }

        else if(strcmpins(command, "SHOW_HOST") == 0) {
            char gameSlug[MAX_GAME_SLUG_LENGTH];
            printf("Game Slug: ");
            readString(gameSlug, MAX_GAME_SLUG_LENGTH);

            showHost(hosts, gameSlug);
        }

        else if(strcmpins(command, "ATHLETE_INFO") == 0) {
            char athleteId[MAX_ID_A_LENGTH];
            printf("Athlete ID: ");
            readString(athleteId, MAX_ID_A_LENGTH);

            showAthleteInfo(athletes, &medals, athleteId);
        }

        else printf("Invalid command inserted. Use HELP to view all available commands.\n");
    }

    printf("-----------------------------------------------\n");
    printf("Thank you for using Olympic Games Data Analysis\n");
    
    return EXIT_SUCCESS;
}



