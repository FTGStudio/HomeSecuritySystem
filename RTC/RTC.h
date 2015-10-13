/*
 * RTC.h
 *
 * Created: 10/11/2015 6:16:08 PM
 *  Author: karnazed
 */ 


#ifndef RTC_H_
#define RTC_H_

// INCLUDES
#include <avr/io.h> // deal with port registers
#include <string.h> // string manipulation routines
#include <stdlib.h>
#include <stdio.h>

// TYPEDEFS
typedef uint8_t byte; // I just like byte & sbyte better
typedef int8_t sbyte;

void InitAVR(void);
void I2C_Init(void);
byte I2C_Detect(byte addr);
void I2C_Start (byte slaveAddr);
byte I2C_Write (byte data);
byte I2C_ReadACK (void);
byte I2C_ReadNACK (void);
void I2C_WriteByte(byte busAddr, byte data);
void I2C_WriteRegister(byte busAddr, byte deviceRegister, byte data);
byte I2C_ReadRegister(byte busAddr, byte deviceRegister);

void DS3231_GetTemp(byte *tempHigh, byte *tempLow);
void DS3231_GetTime(byte *hours, byte *minutes, byte *seconds);
void DS3231_GetDate(byte *months, byte *days, byte *years, byte *dayOfWeek);
void SetTime(byte *hours, byte *minutes, byte *seconds);
void SetDate(byte *months, byte *days, byte *years, byte *dayOfWeek);
byte asciiToHex(char input);
void promptTime(byte *hours, byte *minutes, byte *seconds);
void promptDate(byte *year, byte *month, byte *day, byte *dayOfWeek);






#define ClearBit(x,y) x &= ~_BV(y) // equivalent to cbi(x,y)
#define SetBit(x,y) x |= _BV(y) // equivalent to sbi(x,y)
#define F_SCL 100000L // I2C clock speed 100 KHz
#define F_CPU 8000000
#define READ 1
#define TW_START 0xA4 // send start condition (TWINT,TWSTA,TWEN)
#define TW_STOP 0x94 // send stop condition (TWINT,TWSTO,TWEN)
#define TW_ACK 0xC4 // return ACK to slave
#define TW_NACK 0x84 // don't return ACK to slave
#define TW_SEND 0x84 // send data (TWINT,TWEN)
#define TW_READY (TWCR & 0x80) // ready when TWINT returns to logic 1.
#define TW_STATUS (TWSR & 0xF8) // returns value of status register
#define I2C_Stop() TWCR = TW_STOP // inline macro for stop condition
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
#define STATUS_REGISTER 0x0F
#define TEMP_REGISTER_MSB 0x11
#define TEMP_REGISTER_LSB 0x12



// ---------------------------------------------------------------------------









#endif /* RTC_H_ */