/*
 *  ixpando_demo -- a demo of the Bolport Club "Ixpando" project for the RPi
 *
 *  Synopsis: ixpando [<value>]
 *
 *  Description:
 *    If there is no value provided on the command line, the value of the
 *  switches are continually displayed on the LEDs.  In this mode, the program
 *  can either be run in the background by appending an ampersand to the 
 *  command line and killing the process later with "kill <pid>" or
 *  "pkill ixpando_demo" or run in the foreground then typing "<ctrl>-C" to
 *  terminate it.  Otherwise the given value is displayed once on the LEDs, 
 *  the value of the switches is printed to the stdout device, then the program
 *  exits.
 *    This program uses an API, described in ixpando.h, that abstracts access
 *  to the Ixpando board.  It was meant to be built and run on a Raspberry Pi;
 *  no other platforms have been tested.
 *
 *    It is important to note that the switch values are interpreted
 *  such that the least significant bit is the one next to the LEDS,
 *  as shown:
 *
 *      DIP switch (portA)    LEDs (portB)
 *      +-----------------+
 *      | s s s s s s s s |  o o o o o o o o
 *      +-----------------+
 *                      ^                  ^
 *                      |                  |
 *                     LSB                LSB
 *
 *  This orientation is more natural.
 *
 *  NOTE: this program relies on the wiringPi library available from
 *    wiringpi.com.  Their web site describes how to download, build,
 *    and install the library.
 *
 *  Hardware interface:
 *    rpi pin 3 = SDA
 *    rpi pin 4 = +5v
 *    rpi pin 5 = SCL
 *    rpi pin 6 = GND
 */

#include <stdio.h>
#include <stdlib.h>
#include "ixpando.h"

const char* usage = "usage: ixpando_demo [<hex value between 00-ff>]\n";

int main(int argc, char** argv)
{
	unsigned char value;

	// init Ixpando at default I2C bus address
	if ((Ixpando_Init(IXPANDO_I2C_ADDR_DEFAULT)) < 0)
	{
		perror("Ixpando_Init(): ");
	}

	// parse the command line:
	switch (argc)
	{
		case 1:
			// continually read and display the switch values
			while (1)
			{
				if (Ixpando_Write(Ixpando_Read()) < 0)
				{
					perror("writing LEDs: ");
					exit(EXIT_FAILURE);
				}
			}
			break;

		case 2:
			// display the command line value on the LEDs
			if ((value = (int)strtol(argv[1], NULL, 16)) < 0x100)
			{
				if (Ixpando_Write(value) < 0)
				{
					perror("writing LEDs: ");
					exit(EXIT_FAILURE);
				}
			}
			else
			{
				fprintf(stderr, "%s", usage);
				exit(EXIT_FAILURE);
			}

			// print the switch values to stdout
			printf("0x%x\n", Ixpando_Read());
			break;

		default:
			fprintf(stderr, "%s", usage);
			break;
		
	}

	return 0;
}

