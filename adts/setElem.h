/**
 * @file setElem.h
 * @brief Defines the type SetElem.
 * 
 * The SetElem is an alias to the type of elements 
 * held by an instance of the ADT Set (PtSet).
 * 
 * This alias must be changed according to the use-case.
 * 
 * @author Rodrigo Baptista (202200217@estudantes.ips.pt)
 * @bug No known bugs.
 */

#pragma once

#include <stdbool.h>
#include "../types/stringWrap.h"

/* Change according to use-case. */
typedef StringWrap SetElem;

/**
 * @brief Prints a set element.
 * 
 * Must be implemented according to the concrete
 * type of SetElem.
 * 
 * @param elem [in] set element to print.
 */
void setElemPrint(SetElem elem); 

/**
 * @brief Compares two set elements.
 * 
 * This function provides the comparison criteria
 * between two set elements.
 * 
 * @param elem1 [in] a set element.
 * @param elem2 [in] another set element.
 *
 * @return 0 if they are equal.
 * @return value less than 0, if 'elem1' is less than 'elem2' 
 * @return value greater than 0 if 'elem1' is greater than 'elem2' 
 */
int setElemCompare(SetElem elem1, SetElem elem2);

/**
 * @brief Returns the hash of the SetElem
 * 
 * It is up to the caller to determine how the SetElem will be hashed.
 * If it has any fields, what fields will be used to determine the hash.
 * 
 * @param elem1 [in] a set element to be hashed.
 *
 * @return an int with the hash of the element.
 */
int setElemHash(SetElem elem);