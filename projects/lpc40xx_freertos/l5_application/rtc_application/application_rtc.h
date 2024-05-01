#pragma once

/*************************************************************************
                            I N C L U D E S
*************************************************************************/

#include <stdint.h>

/*************************************************************************
                            S T R U C T U R E
*************************************************************************/

typedef struct {
  uint8_t hours;
  uint8_t minutes;
  uint8_t seconds;
} Time;

typedef struct {
  uint8_t year;
  uint8_t month;
  uint8_t day;
  uint8_t hours;
  uint8_t minutes;
  uint8_t seconds;
} DateTime;

/*************************************************************************
                     P U B L I C    F U N C T I O N S
*************************************************************************/

uint8_t rtc_get_status(void);

void rtc_get_time(Time *time);

void rtc_set_time(const Time *time);

uint32_t rtc_get_epoch(void);
