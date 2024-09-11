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
#include "adts/set.h"
#include "data/memory.h"
#include "shows/simple.h"
#include "types/stringWrap.h"
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

    // Testing START
    athletes = loadAthletes();
    loadMedals(&medals);
    hosts = loadHosts();
    medalsWon(&medals, hosts, "United States of America", "Winter", 1924);
    // Testing END

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
            bool missing = athletesIsNull(athletes);
            if(missing) continue;

            checkOrderedAthletesLoaded(athletes, &alphabeticAthletes);
            showAll(alphabeticAthletes);
        }
        
        else if(strcmpins(command, "SHOW_PARTICIPATIONS") == 0) {
            bool missing = athletesIsNull(athletes);
            if(missing) continue;

            checkOrderedAthletesLoaded(athletes, &alphabeticAthletes);

            int participationCount;
            printf("Participation Count: ");
            readInteger(&participationCount);

            showParticipations(alphabeticAthletes, participationCount);
        } 

        else if(strcmpins(command, "SHOW_FIRST") == 0) {
            bool missing = athletesIsNull(athletes);
            if(missing) continue;

            checkOrderedAthletesLoaded(athletes, &alphabeticAthletes);

            int firstYear;
            printf("First Participation Year: ");
            readInteger(&firstYear);

            showFirst(alphabeticAthletes, firstYear);
        }

        else if(strcmpins(command, "SHOW_HOST") == 0) {
            bool missing = hostsIsNull(hosts);
            if(missing) continue;

            char gameSlug[MAX_GAME_SLUG_LENGTH];
            printf("Game Slug: ");
            readString(gameSlug, MAX_GAME_SLUG_LENGTH);

            showHost(hosts, gameSlug);
        }

        else if(strcmpins(command, "DISCIPLINE_STATISTICS") == 0) {
            bool missing = medalsIsNull(&medals);
            if(missing) continue;

            char gameSlug[MAX_GAME_SLUG_LENGTH];
            printf("Game Slug: ");
            readString(gameSlug, MAX_GAME_SLUG_LENGTH);

            showDisciplineStatistics(&medals, gameSlug);
        }

        else if(strcmpins(command, "ATHLETE_INFO") == 0) {
            bool missing = athletesIsNull(athletes) | medalsIsNull(&medals);
            if(missing) continue;
                
            char athleteId[MAX_ID_A_LENGTH];
            printf("Athlete ID: ");
            readString(athleteId, MAX_ID_A_LENGTH);

            showAthleteInfo(athletes, &medals, athleteId);
        }

        else if(strcmpins(command, "TOPN") == 0) {
            bool missing = athletesIsNull(athletes) | medalsIsNull(&medals) | hostsIsNull(hosts);
            if(missing) continue;

            int n;
            printf("Number of Athletes: ");
            readInteger(&n);
            while(n < 0) {
                printf("Number of Athletes must not be smaller than or equal to 0.\n");
                printf("Number of Athletes: ");
                readInteger(&n);
            }

            int start, end;
            printf("Start Year: ");
            readInteger(&start);
            printf("End Year: ");
            readInteger(&end);
            while(end < start) {
                printf("End Year must not be smaller than the start Year!\n");
                printf("End Year: ");
                readInteger(&end);
            }

            char season[MAX_GAME_SEASON_LENGTH];
            printf("Season (Winter, Summer): ");
            readString(season, MAX_GAME_SEASON_LENGTH);
            while(strcmpins(season, "Winter") != 0 && strcmpins(season, "Summer") != 0) {
                printf("Season must be either \"Winter\" or \"Summer\"!\n");
                printf("Season (Winter, Summer): ");
                readString(season, MAX_GAME_SEASON_LENGTH);
            }
            
            showTopN(athletes, &medals, hosts, n, start, end, season);
        }

        else if(strcmpins(command, "MEDALS_WON") == 0) {
            bool missing = medalsIsNull(&medals) | hostsIsNull(hosts);
            if(missing) continue;

            char country[MAX_COUNTRY_LENGTH];
            printf("Country: ");
            readString(country, MAX_COUNTRY_LENGTH);

            char season[MAX_GAME_SEASON_LENGTH];
            printf("Season (Winter, Summer): ");
            readString(season, MAX_GAME_SEASON_LENGTH);
            while(strcmpins(season, "Winter") != 0 && strcmpins(season, "Summer") != 0) {
                printf("Season must be either \"Winter\" or \"Summer\"!\n");
                printf("Season (Winter, Summer): ");
                readString(season, MAX_GAME_SEASON_LENGTH);
            }

            int year;
            printf("Year: ");
            readInteger(&year);

            medalsWon(&medals, hosts, country, season, year);
        }

        else printf("Invalid command inserted. Use HELP to view all available commands.\n");
    }

    printf("-----------------------------------------------\n");
    printf("Thank you for using Olympic Games Data Analysis\n");
    
    return EXIT_SUCCESS;
}



