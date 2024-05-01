/*************************************************************************
                                I N C L U D E S
*************************************************************************/

#include "rtc_MCP795xx.h"
#include "ssp2.h"

// Private Function Prototype
static void clear_power_fail_flag(void);

/*************************************************************************
                P U B L I C    F U N C T I O N S
*************************************************************************/

void initialize_rtc(void) {

  // start oscillator
  write_register(RTCSEC_REG, ST_BIT); // ST is bit 7 in Table 5-2

  // setting a known date and time, e.g., 12:00:00 on 1st April 2024
  write_register(RTCYEAR_REG, 0x24);         // Year 2024
  write_register(RTCMTH_REG, 0x04);          // April
  write_register(RTCDATE_REG, 0x01);         // 1st
  write_register(RTCHOUR_REG, 0x12);         // 12 PM
  write_register(RTCMIN_REG, 0x00 | ST_BIT); // 00 minutes and start oscillator

  clear_power_fail_flag();
}

uint8_t read_register(uint8_t reg_address) {
  const uint8_t read_command = 0x13; // '0x13' is the command to read register
  const uint8_t dummy_byte = 0x00;
  const uint8_t mask_msb = 0x7F;

  // Send read command with register address
  ssp2__exchange_byte(read_command | (reg_address & mask_msb));

  return ssp2__exchange_byte(dummy_byte); // Send dummy byte to read data
}

void write_register(uint8_t reg_address, uint8_t data) {
  const uint8_t mask_msb = 0x7F;

  // Ensure MSB is 0 write operations
  uint8_t address_byte = RTC_WRITE_COMMAND | (reg_address & mask_msb);
  ssp2__exchange_byte(address_byte);
  ssp2__exchange_byte(data);
}

/*************************************************************************
        P R I V A T E   F U N C T I O N  D E F I N I T I O N
*************************************************************************/

static void clear_power_fail_flag(void) {
  uint8_t status = read_register(RTCWKDAY_REG); // Read the current value
  status &= CLEAR_PWRFAIL_MASK;                 // Clear the PWRFAIL bit
  write_register(RTCWKDAY_REG, status);         // Write the modified value back
}