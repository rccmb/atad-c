#include <stdio.h> 
#include <stdlib.h>

#include "utilities/ui.h"

int main() {

    printf("Olympic Games Data Analysis\n");
    printf("---------------------------\n");

    printMenu();

    while(requestCommand() == true);
    
    return EXIT_SUCCESS;
}



