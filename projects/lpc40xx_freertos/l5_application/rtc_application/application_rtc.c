/*************************************************************************
                            I N C L U D E S
*************************************************************************/

#include "application_rtc.h"
#include "rtc_MCP795xx.h"
#include <time.h>

/*************************************************************************
            H E L P E R   F U N C T I O N   P R O T O T Y P E S
*************************************************************************/

static uint8_t bcd_to_decimal(uint8_t bcd);
static uint8_t decimal_to_bcd(uint8_t decimal);
static uint32_t calculate_epoch(const DateTime *dt);

/*************************************************************************
                     P U B L I C    F U N C T I O N S
*************************************************************************/

uint8_t rtc_get_status(void) { return read_register(READ_STATUS_REGISTER); }

void rtc_get_time(Time *time) {
  time->hours = bcd_to_decimal(read_register(RTCHOUR_REG));
  time->minutes = bcd_to_decimal(read_register(RTCMIN_REG));
  time->seconds = bcd_to_decimal(read_register(RTCSEC_REG));
}

void rtc_set_time(const Time *time) {
  write_register(RTCHOUR_REG, decimal_to_bcd(time->hours));
  write_register(RTCMIN_REG, decimal_to_bcd(time->minutes));
  write_register(RTCSEC_REG, decimal_to_bcd(time->seconds) |
                                 ST_BIT); // Ensure oscillator is started
}

uint32_t rtc_get_epoch(void) {
  DateTime dt;
  dt.year = bcd_to_decimal(read_register(RTCYEAR_REG));
  dt.month = bcd_to_decimal(read_register(RTCMTH_REG));
  dt.day = bcd_to_decimal(read_register(RTCDATE_REG));
  dt.hours = bcd_to_decimal(read_register(RTCHOUR_REG));
  dt.minutes = bcd_to_decimal(read_register(RTCMIN_REG));
  dt.seconds = bcd_to_decimal(read_register(RTCSEC_REG));

  return calculate_epoch(&dt);
}

/************************************************************************
        H E L P E R   F U N C T I O N   D E F I N I T I O N S
*************************************************************************/

static uint8_t bcd_to_decimal(uint8_t bcd) {
  return ((bcd >> 4) * 10) + (bcd & 0x0F);
}

static uint8_t decimal_to_bcd(uint8_t decimal) {
  return ((decimal / 10) << 4) | (decimal % 10);
}

static uint32_t calculate_epoch(const DateTime *dt) {
  struct tm t;
  time_t t_of_day;

  t.tm_year = dt->year + 100; // tm_year is years since 1900
  t.tm_mon = dt->month - 1;   // tm_mon is months since January (0-11)
  t.tm_mday = dt->day;
  t.tm_hour = dt->hours;
  t.tm_min = dt->minutes;
  t.tm_sec = dt->seconds;
  t.tm_isdst = -1; // Not considering daylight saving time

  t_of_day = mktime(&t);

  return (uint32_t)t_of_day;
}
