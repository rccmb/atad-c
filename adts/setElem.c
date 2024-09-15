/**
 * @file setElem.c
 *
 * @brief Implements operations for SetElem.
 * 
 * @author Rodrigo Baptista (202200217@estudantes.ips.pt)
 * @bug No known bugs.
 */

#include <string.h>
#include <stdio.h>

#include "setElem.h"

void setElemPrint(SetElem elem) {
  printf("%s\n", elem.text);
}

int setElemCompare(SetElem elem1, SetElem elem2) {
  return strcmp(elem1.text, elem2.text);
}

int setElemHash(SetElem elem) {
  char str[256];
  int sum = 0, cur = 0;
  strcpy(str, elem.text);
  while(str[cur] != '\0') sum += (int) str[cur++];
  return sum;
}