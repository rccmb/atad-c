#include <stdio.h> 
#include <stdlib.h>

#include "list.h"
#include "data/import.h"
#include "utilities/ui.h"
#include "utilities/helper.h"
#include "types/athlete.h"
#include "types/medal.h"
#include "types/host.h"
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
    PtList athletes = listCreate();
    int athletesSize = -1;

    PtMedal medals = NULL;
    int medalsSize = -1;

    PtHost hosts = NULL;
    int hostsSize = -1;

    while(true) {
        char command[COMMAND_LENGTH];
        printf("Command > ");
        readString(command, COMMAND_LENGTH);
        
        if(strcmpins(command, "HELP") == 0) {
            printMenu();
        } 
        
        else if(strcmpins(command, "LOAD_A") == 0) {
            athletes = load_a(&athletesSize);

            athletesSize > 0 
                ? printf("<%d> Athlete records imported.", athletesSize)
                : printf("No athlete records imported!");
        } 
        
        else if(strcmpins(command, "LOAD_M") == 0) {
            medals = load_m(&medalsSize);

            medalsSize > 0 
                ? printf("<%d> Medal records imported.", medalsSize)
                : printf("No medal records imported!");
        } 
        
        else if(strcmpins(command, "LOAD_H") == 0) {
            hosts = load_h(&hostsSize);

            hostsSize > 0 
                ? printf("<%d> Medal records imported.", hostsSize)
                : printf("No medal records imported!");
        } 
        
        else if(strcmpins(command, "CLEAR") == 0) {
        
        } 
        
        else if(strcmpins(command, "QUIT") == 0) {
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



