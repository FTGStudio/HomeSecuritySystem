



#include "RTC.h"
// MISC ROUTINES
void InitAVR()
{
	DDRB = 0x3F; // 0011.1111; set B0-B5 as outputs
	DDRC = 0x00; // 0000.0000; set PORTC as inputs
}


// ---------------------------------------------------------------------------
// I2C (TWI) ROUTINES
//
// On the AVRmega series, PC4 is the data line (SDA) and PC5 is the clock (SCL
// The standard clock rate is 100 KHz, and set by I2C_Init. It depends on the AVR osc. freq.

void I2C_Init()
// at 16 MHz, the SCL frequency will be 16/(16+2(TWBR)), assuming prescalar of 0.
// so for 100KHz SCL, TWBR = ((F_CPU/F_SCL)-16)/2 = ((16/0.1)-16)/2 = 144/2 = 72.
{
	TWSR = 0; // set prescalar to zero
	TWBR = ((F_CPU/F_SCL)-16)/2; // set SCL frequency in TWI bit register
}
byte I2C_Detect(byte addr)
// look for device at specified address; return 1=found, 0=not found
{
	TWCR = TW_START; // send start condition
	while (!TW_READY); // wait
	TWDR = addr; // load device's bus address
	TWCR = TW_SEND; // and send it
	while (!TW_READY); // wait
	return (TW_STATUS==0x18); // return 1 if found; 0 otherwise
}
byte I2C_FindDevice(byte start)
// returns with address of first device found; 0=not found
{
	for (byte addr=start;addr<0xFF;addr++) // search all 256 addresses
	{
		if (I2C_Detect(addr)) // I2C detected?
		return addr; // leave as soon as one is found
	}
	return 0; // none detected, so return 0.
}
void I2C_Start (byte slaveAddr)
{
	I2C_Detect(slaveAddr);
}
byte I2C_Write (byte data) // sends a data byte to slave
{
	TWDR = data; // load data to be sent
	TWCR = TW_SEND; // and send it
	while (!TW_READY); // wait
	return (TW_STATUS!=0x28);
}
byte I2C_ReadACK () // reads a data byte from slave
{
	TWCR = TW_ACK; // ack = will read more data
	while (!TW_READY); // wait
	return TWDR;
	//return (TW_STATUS!=0x28);
}
byte I2C_ReadNACK () // reads a data byte from slave
{
	TWCR = TW_NACK; // nack = not reading more data
	while (!TW_READY); // wait
	return TWDR;
	//return (TW_STATUS!=0x28);
}
void I2C_WriteByte(byte busAddr, byte data)
{
	I2C_Start(busAddr); // send bus address
	I2C_Write(data); // then send the data byte
	I2C_Stop();
}
void I2C_WriteRegister(byte busAddr, byte deviceRegister, byte data)
{
	I2C_Start(busAddr); // send bus address
	I2C_Write(deviceRegister); // first byte = device register address
	I2C_Write(data); // second byte = data for device register
	I2C_Stop();
}
byte I2C_ReadRegister(byte busAddr, byte deviceRegister)
{
	byte data = 0;
	I2C_Start(busAddr); // send device address
	I2C_Write(deviceRegister); // set register pointer
	I2C_Start(busAddr+READ); // restart as a read operation
	data = I2C_ReadNACK(); // read the register data
	I2C_Stop(); // stop
	return data;
}
// ---------------------------------------------------------------------------


void DS3231_GetTemp(byte *tempHigh, byte *tempLow)
{
	byte var = 0x00;
	//int polarity = 1;
	var = I2C_ReadRegister(DS3231,TEMP_REGISTER_MSB);
	//polarity = -1*((var & 0x80)>>7);
	var &=~ 0x80;
	*tempHigh = var;
	
	*tempLow = (I2C_ReadRegister(DS3231,TEMP_REGISTER_LSB)>>6)*25;
}

void DS3231_GetTime(byte *hours, byte *minutes, byte *seconds)
// returns hours, minutes, and seconds in BCD format
{
	*hours = I2C_ReadRegister(DS3231,HOURS_REGISTER);
	*minutes = I2C_ReadRegister(DS3231,MINUTES_REGISTER);
	*seconds = I2C_ReadRegister(DS3231,SECONDS_REGISTER);
	if (*hours & 0x40) // 12hr mode:
	*hours &= 0x1F; // use bottom 5 bits (pm bit = temp & 0x20)
	else *hours &= 0x3F; // 24hr mode: use bottom 6 bits
}
void DS3231_GetDate(byte *months, byte *days, byte *years, byte *dayOfWeek)
// returns months, days, and years in BCD format
{
	*months = I2C_ReadRegister(DS3231,MONTHS_REGISTER);
	*days = I2C_ReadRegister(DS3231,DAYS_REGISTER);
	*years = I2C_ReadRegister(DS3231,YEARS_REGISTER);
	*dayOfWeek = I2C_ReadRegister(DS3231,DAYOFWK_REGISTER);
}



void SetTime(byte *hours, byte *minutes, byte *seconds)
{
	I2C_WriteRegister(DS3231,HOURS_REGISTER, *hours); // add 0x40 for PM
	I2C_WriteRegister(DS3231,MINUTES_REGISTER, *minutes);
	I2C_WriteRegister(DS3231,SECONDS_REGISTER, *seconds);
	
}

void SetDate(byte *months, byte *days, byte *years, byte *dayOfWeek)
{
	I2C_WriteRegister(DS3231,MONTHS_REGISTER, *months);
	I2C_WriteRegister(DS3231,DAYS_REGISTER, *days);
	I2C_WriteRegister(DS3231,YEARS_REGISTER, *years);
	I2C_WriteRegister(DS3231,DAYOFWK_REGISTER, *dayOfWeek);
}


//helper functions

byte asciiToHex(char input)
{
	return (input - 0x30);
}

void promptTime(byte *hours, byte *minutes, byte *seconds)
{
	byte hoursH, hoursL, minH, minL, secH, secL;
	byte temp = 'z';
	
	printf("\nEnter hours (Format 00) :");
	temp = getchar();
	if(temp != '\n')hoursH = asciiToHex(temp);
	temp = getchar();
	if(temp != '\n')hoursL = asciiToHex(temp);
	hoursH = (hoursH)<<4;
	*hours = (hoursH|hoursL);
	I2C_WriteRegister(DS3231,HOURS_REGISTER,*hours);
	
	printf("\nEnter minutes (Format 00) :");
	temp = getchar();
	if(temp != '\n')minH = asciiToHex(temp);
	temp = getchar();
	if(temp != '\n')minL = asciiToHex(temp);
	minH = (minH)<<4;
	*minutes = (minH|minL);
	I2C_WriteRegister(DS3231,MINUTES_REGISTER,*minutes);
	
	printf("\nEnter seconds (Format 00) :");
	temp = getchar();
	if(temp != '\n')secH = asciiToHex(temp);
	temp = getchar();
	if(temp != '\n')secL = asciiToHex(temp);
	secH = (secH)<<4;
	*seconds = (secH|secL);
	I2C_WriteRegister(DS3231,SECONDS_REGISTER,*seconds);
	
	printf("\nTime accepted\n");
}

void promptDate(byte *year, byte *month, byte *day, byte *dayOfWeek)
{
	byte yearH, yearL, monthH, monthL, dayH, dayL, dayWeek;
	byte temp = 'z';
	
	printf("\nEnter year (Format 00) :");
	temp = getchar();
	if(temp != '\n')yearH = asciiToHex(temp);
	temp = getchar();
	if(temp != '\n')yearL = asciiToHex(temp);
	yearH = (yearH)<<4;
	*year = (yearH|yearL);
	I2C_WriteRegister(DS3231,YEARS_REGISTER,*year);
	
	printf("\nEnter month (Format 00) :");
	temp = getchar();
	if(temp != '\n')monthH = asciiToHex(temp);
	temp = getchar();
	if(temp != '\n')monthL = asciiToHex(temp);
	monthH = (monthH)<<4;
	*month = (monthH|monthL);
	I2C_WriteRegister(DS3231,MONTHS_REGISTER,*month);
	
	printf("\nEnter day of month (Format 00) :");
	temp = getchar();
	if(temp != '\n')dayH = asciiToHex(temp);
	temp = getchar();
	if(temp != '\n')dayL = asciiToHex(temp);
	dayH = (dayH)<<4;
	*day = (dayH|dayL);
	I2C_WriteRegister(DS3231,DAYS_REGISTER,*day);
	
	printf("\nEnter day of week (Format 1-7) :");
	temp = getchar();
	if(temp != '\n')dayWeek = asciiToHex(temp);
	*dayOfWeek = (dayWeek);
	I2C_WriteRegister(DS3231,DAYS_REGISTER,*dayOfWeek);
	
	printf("\nDate accepted\n");
}