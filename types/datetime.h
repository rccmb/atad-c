/**
 * @file datetime.h
 * @author Rodrigo Baptista (202200217@estudantes.ips.pt)
 * @brief Provides the DateTime code module. Type definition and functions.
 * 
 * @version 1
 * @date 2024-08-14
 * 
 */

#pragma once

/** Declaration of the data structure. */
typedef struct datetime {
  int year;
  int month;
  int day;
  int hour;
  int minutes;
} DateTime;

/** Definition of pointer to the data stucture. */
typedef struct datetime *PtDateTime;

/**
 * @brief Parses a string and transforms it into DateTime.
 *
 * The string must be in "YYYY-MM-DDTHH:MM:SSZ" format.
 * 
 * @param date [in] String with the date and time.
 *
 * @return DateTime with the date and time.
 */
DateTime datetimeCreate(char *date);

/**
 * @brief Calculates the amount of days between two dates.
 * 
 * @param startDate [in] DateTime with the beginning date.
 * @param endDate [in] DateTime with the ending date.
 *
 * @return Integer representing the amount of days between the date.
 */
int calculateDayDifference(DateTime startDate, DateTime endDate);

/**
 * @brief Prints a DateTime, YYYY-MM-DD HH:MM:SS
 * 
 * @param dt [in] Pointer to a DateTime with the date.
 */
void datetimePrint(PtDateTime dt);

/**
 * @brief Prints only the date from a DateTime, YYYY-MM-DD
 * 
 * @param dt [in] Pointer to a DateTime with the date.
 */
void datePrint(PtDateTime dt);

/**
 * @brief Gets the year from a datetime.
 * 
 * @param dt [in] Pointer to a DateTime with the date.
 *
 * @return Integer representing the year in the datetime, or
 * @return -1 if the pointer is null.
 */
int datetimeYear(PtDateTime dt);