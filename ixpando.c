/*
 *  ixpando -- an ixpando project API
 *
 *  Description:
 *    This file contains a simple API for initializing, reading from, and
 *  writing to the Boldport Club "Ixpando" project board.  It is assumed
 *  that the project was built as described on the project's web page, that
 *  is, the DIP switches are on portA and the LEDs are on portB.  See
 *  ixpando.h for descriptions of the APIs.
 *    
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <wiringPiI2C.h>
#include "ixpando.h"

int fd;

int Ixpando_Init(int i2cAddr)
{

	// get the fd
	if ((fd = wiringPiI2CSetup(i2cAddr)) == -1)
	{
		if (
			// invert portA and add pullups 
			wiringPiI2CWriteReg8(fd, IXPANDO_IPOLA,  0xff) < 0 ||
			wiringPiI2CWriteReg8(fd, IXPANDO_GPPUA,  0xff) < 0 ||

			// set portB as outputs
			wiringPiI2CWriteReg8(fd, IXPANDO_IODIRB, 0x00) < 0
		)
		{
			return errno;
		}
	}
	else
	{
		return errno;
	}

	return 0;
}

unsigned char Ixpando_Read()
{
	unsigned char input, value = 0;

	// get the raw value of the switches
	input = wiringPiI2CReadReg8(fd, IXPANDO_GPIOA);

	// reverse the bits in the value
	value |= (input & 0x01) << 7;
	value |= (input & 0x02) << 5;
	value |= (input & 0x04) << 3;
	value |= (input & 0x08) << 1;
	value |= (input & 0x10) >> 1;
	value |= (input & 0x20) >> 3;
	value |= (input & 0x40) >> 5;
	value |= (input & 0x80) >> 7;

	return value;
}

int Ixpando_Write(unsigned char value)
{
	// write the value to the portB output latch 
	if (wiringPiI2CWriteReg8(fd, IXPANDO_OLATB, value) < 0)
	{
		return errno;
	}

	return 0;
}

// end of ixpando.c

