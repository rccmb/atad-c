/**
 * @file listElem.c
 * @brief Implements operations for ListElem.
 * 
 * @author Bruno Silva (brunomnsilva@gmail.com)
 * @bug No known bugs.
 */

#include <stdio.h>
#include "../types/athlete.h"

#include "listElem.h"

void listElemPrint(ListElem elem) {
	athletePrint(&elem);
}