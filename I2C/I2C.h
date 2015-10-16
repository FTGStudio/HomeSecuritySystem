/*
 * I2C.h
 *
 * Created: 10/16/2015 8:58:47 AM
 *  Author: Michael
 */ 

#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>

#define F_SCL						100000L // I2C clock speed 100 KHz
#define F_CPU						8000000

// TYPEDEFS
typedef uint8_t byte; // I just like byte & sbyte better
typedef int8_t sbyte;

#define ClearBit(x,y) x &= ~_BV(y)			// equivalent to cbi(x,y)
#define SetBit(x,y) x |= _BV(y)				// equivalent to sbi(x,y)
#define READ 1
#define TW_START 0xA4						// send start condition (TWINT,TWSTA,TWEN)
#define TW_STOP 0x94						// send stop condition (TWINT,TWSTO,TWEN)
#define TW_ACK 0xC4							// return ACK to slave
#define TW_NACK 0x84						// don't return ACK to slave
#define TW_SEND 0x84						// send data (TWINT,TWEN)
#define TW_READY (TWCR & 0x80)				// ready when TWINT returns to logic 1.
#define TW_STATUS (TWSR & 0xF8)				// returns value of status register
#define I2C_Stop() TWCR = TW_STOP			// inline macro for stop condition

void I2C_Init(void);
byte I2C_Detect(byte addr);
void I2C_Start (byte slaveAddr);
byte I2C_Write (byte data);
byte I2C_ReadACK (void);
byte I2C_ReadNACK (void);
void I2C_WriteByte(byte busAddr, byte data);
void I2C_WriteRegister(byte busAddr, byte deviceRegister, byte data);
byte I2C_ReadRegister(byte busAddr, byte deviceRegister);

