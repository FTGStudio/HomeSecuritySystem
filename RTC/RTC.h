/*
 * RTC.h
 *
 * Created: 10/11/2015 6:16:08 PM
 *  Author: karnazed
 */ 

#include "../I2C/I2C.h"

#ifndef RTC_H_
#define RTC_H_

#define DS3231 0xD0 // I2C bus address of DS3231 RTC (READ)
#define SECONDS_REGISTER 0x00
#define MINUTES_REGISTER 0x01
#define HOURS_REGISTER 0x02
#define DAYOFWK_REGISTER 0x03
#define DAYS_REGISTER 0x04
#define MONTHS_REGISTER 0x05
#define YEARS_REGISTER 0x06
#define CONTROL_REGISTER 0x0E
#define RAM_BEGIN 0x08
#define RAM_END 0x3F
#define STATUS_REGISTER 0x0
#define TEMP_REGISTER_MSB 0x11
#define TEMP_REGISTER_LSB 0x12

void DS3231_GetTemp(byte *tempHigh, byte *tempLow);
void DS3231_GetTime(byte *hours, byte *minutes, byte *seconds);
void DS3231_GetDate(byte *months, byte *days, byte *years, byte *dayOfWeek);
void SetTime(byte *hours, byte *minutes, byte *seconds);
void SetDate(byte *months, byte *days, byte *years, byte *dayOfWeek);
byte asciiToHex(char input);
void promptTime(byte *hours, byte *minutes, byte *seconds);
void promptDate(byte *year, byte *month, byte *day, byte *dayOfWeek);


// ---------------------------------------------------------------------------

#endif /* RTC_H_ */