#include "RTC.h"


/************************************************************************/
/*                                                                      */
/************************************************************************/
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

/************************************************************************/
/*                                                                      */
/************************************************************************/
void DS3231_GetTime(byte *hours, byte *minutes, byte *seconds)
{
	*hours = I2C_ReadRegister(DS3231,HOURS_REGISTER);
	*minutes = I2C_ReadRegister(DS3231,MINUTES_REGISTER);
	*seconds = I2C_ReadRegister(DS3231,SECONDS_REGISTER);
	if (*hours & 0x40) // 12hr mode:
	*hours &= 0x1F; // use bottom 5 bits (pm bit = temp & 0x20)
	else *hours &= 0x3F; // 24hr mode: use bottom 6 bits
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
void DS3231_GetDate(byte *months, byte *days, byte *years, byte *dayOfWeek)
{
	*months = I2C_ReadRegister(DS3231,MONTHS_REGISTER);
	*days = I2C_ReadRegister(DS3231,DAYS_REGISTER);
	*years = I2C_ReadRegister(DS3231,YEARS_REGISTER);
	*dayOfWeek = I2C_ReadRegister(DS3231,DAYOFWK_REGISTER);
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
void SetTime(byte *hours, byte *minutes, byte *seconds)
{
	I2C_WriteRegister(DS3231,HOURS_REGISTER, *hours); // add 0x40 for PM
	I2C_WriteRegister(DS3231,MINUTES_REGISTER, *minutes);
	I2C_WriteRegister(DS3231,SECONDS_REGISTER, *seconds);
	
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
void SetDate(byte *months, byte *days, byte *years, byte *dayOfWeek)
{
	I2C_WriteRegister(DS3231,MONTHS_REGISTER, *months);
	I2C_WriteRegister(DS3231,DAYS_REGISTER, *days);
	I2C_WriteRegister(DS3231,YEARS_REGISTER, *years);
	I2C_WriteRegister(DS3231,DAYOFWK_REGISTER, *dayOfWeek);
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
byte asciiToHex(char input)
{
	return (input - 0x30);
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
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

/************************************************************************/
/*                                                                      */
/************************************************************************/
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