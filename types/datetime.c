/**
 * @file datetime.c
 * @author Rodrigo Baptista (202200217@estudantes.ips.pt)
 * @brief Provides an implementation of datetime.h.
 * 
 * Allows for creating datetimes and getting their information.
 * 
 * @version 1
 * @date 2024-08-14
 * 
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#include "datetime.h"

static bool isLeapYear(int year);
static int getDaysInMonth(int month, int year);
static int calculateDaysSinceStart(DateTime dt);

DateTime datetimeCreate(char *date) {
  DateTime dt;

  char buffer[32];
  strcpy(buffer, date);

  dt.year = atoi(strtok(buffer, "-"));
  dt.month = atoi(strtok(NULL, "-"));
  dt.day = atoi(strtok(NULL, "T"));
  dt.hour = atoi(strtok(NULL, ":"));
  dt.minutes = atoi(strtok(NULL, ":"));

  return dt;
}

int calculateDayDifference(DateTime startDate, DateTime endDate) {
  int startDays = calculateDaysSinceStart(startDate);
  int endDays = calculateDaysSinceStart(endDate);

  return endDays - startDays;
}

void datetimePrint(PtDateTime dt) {
  printf("%04d-%02d-%02d %02d:%02d\n", dt->year, dt->month, dt->day, dt->hour, dt->minutes);
}

void datePrint(PtDateTime dt) {
  printf("%04d-%02d-%02d\n", dt->year, dt->month, dt->day);
}

static bool isLeapYear(int year) {
  return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

static int getDaysInMonth(int month, int year) {
  if (month == 2) return isLeapYear(year) ? 29 : 28;
  if (month == 4 || month == 6 || month == 9 || month == 11) return 30;
  return 31;
}

static int calculateDaysSinceStart(DateTime dt) {
  int days = 0;
  for(int i = 1; i < dt.year; i++) days += isLeapYear(i) ? 366 : 365;
  for(int i = 1; i < dt.month; i++) days += getDaysInMonth(i, dt.year);
  days += dt.day;
  return days;
}
