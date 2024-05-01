// clang-format off
#pragma once

/*************************************************************************
                                I N C L U D E S
*************************************************************************/

#include <stdint.h>

/*************************************************************************
                                D E F I N E S
*************************************************************************/

#define RTC_WRITE_COMMAND        0x12 // from Table 4-1
#define RTC_READ_COMMAND         0x13
#define READ_STATUS_REGISTER     0x05
#define WRITE_STATUS_REGISTER    0x01
#define RTCSEC_REG               0x01 // RTC Seconds Register Address - Table 5-2
#define RTCYEAR_REG              0x07
#define RTCMTH_REG               0x06
#define RTCDATE_REG              0x05
#define RTCHOUR_REG              0x03   
#define RTCMIN_REG               0x02
#define RTCWKDAY_REG             0x04

#define CLEAR_PWRFAIL_MASK 0xEF // Bit mask to clear the PWRFAIL bit (11101111)
#define ST_BIT (1 << 7)         // Start oscillator bit in RTCSEC

/*************************************************************************
                P U B L I C    F U N C T I O N S
*************************************************************************/

void initialize_rtc(void);

uint8_t read_register(uint8_t reg_address);

void write_register(uint8_t reg_address, uint8_t data);