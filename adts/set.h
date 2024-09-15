/**
 * @file set.h
 * @brief Definition of the ADT Set in C.
 * 
 * Defines the type PtSet and associated operations.
 * 
 * @author Rodrigo Baptista (202200217@estudantes.ips.pt)
 * @bug No known bugs.
 */

#pragma once

#define SET_OK 0
#define SET_NULL 1 
#define SET_NO_MEMORY	2
#define SET_EMPTY 3
#define SET_FULL 4
#define SET_ERROR 5
#define SET_DUPLICATE 6
#define SET_NOT_FOUND 7

#include "setElem.h"
#include <stdbool.h>

/** Forward declaration of the data structure. */
struct setImpl;

/** Definition of pointer to the  data stucture. */
typedef struct setImpl *PtSet;

/**
 * @brief Creates a new empty set.
 * 
 * @return PtSet pointer to allocated data structure, or
 * @return NULL if unsufficient memory for allocation.
 */
PtSet setCreate();

/**
 * @brief Add an element to the set. If it already exists, then silently replace it.
 * 
 * @param set [in] pointer to the set.
 * @param elem [in] element to add.
 * 
 * @return SET_OK if successful, or
 * @return SET_FULL if no capacity available, or
 * @return SET_NO_MEMORY if unsufficient memory for allocation, or
 * @return SET_NULL if 'set' is NULL.
 */
int setAdd(PtSet set, SetElem elem);

/**
 * @brief Remove an element from the set if it exists.
 * 
 * @param set [in] pointer to the set.
 * @param elem [in] element to remove.
 * 
 * @return SET_OK if successful, or
 * @return SET_FULL if no capacity available, or
 * @return SET_NO_MEMORY if unsufficient memory for allocation, or
 * @return SET_NULL if 'set' is NULL.
 */
int setRemove(PtSet set, SetElem elem);

/**
 * @brief Checks if an element exists in the set.
 * 
 * @param set [in] pointer to the set.
 * @param elem [in] element to check.
 * 
 * @return true if the element exists, or
 * @return false if it doesn't.
 */
bool setContains(PtSet set, SetElem elem);

/**
 * @brief Gets the size of the set.
 * 
 * @param set [in] pointer to the set.
 * @param ptSize [out] size of the set.
 * 
 * @return SET_OK if successful, or
 * @return SET_FULL if no capacity available, or
 * @return SET_NO_MEMORY if unsufficient memory for allocation, or
 * @return SET_NULL if 'set' is NULL.
 */
int setSize(PtSet set, int *ptSize);

/**
 * @brief Checks the sets are subsets.
 * 
 * @param set1 [in] pointer to set one.
 * @param set2 [in] pointer to set two.
 * 
 * @return true if set1 is a subset of set2.
 * @return false if set1 is not a subset of set2.
 */
bool setSubset(PtSet set1, PtSet set2);

/**
 * @brief Checks if the given set is empty.
 * 
 * @param set [in] pointer to the set.
 * 
 * @return true if the set is empty, or
 * @return false if the set has elements.
 */
bool setIsEmpty(PtSet set);

/**
 * @brief Clears the given set.
 * 
 * @param set [in] pointer to the set.
 * 
 * @return SET_OK if successful, or
 * @return SET_FULL if no capacity available, or
 * @return SET_NO_MEMORY if unsufficient memory for allocation, or
 * @return SET_NULL if 'set' is NULL.
 */
int setClear(PtSet set);

/**
 * @brief Gets the values from a given set. 
 *
 * The size of the dynamic array will be the size of the set.
 * 
 * @param set [in] pointer to the set.
 * 
 * @return array containing the values of the set, or
 * @return NULL if the 'set' is empty or NULL
 */
SetElem* setValues(PtSet set);

/**
 * @brief Prints the contents of a set.
 * 
 * @param set [in] pointer to the set
 */
void setPrint(PtSet set);

/**
 * @brief Free all resources of a set.
 * 
 * @param ptSet [in] ADDRESS OF pointer to the set.
 * 
 * @return SET_OK if success, or
 * @return SET_NULL if '*ptSet' is NULL 
 */
int setDestroy(PtSet *ptSet);