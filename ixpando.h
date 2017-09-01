/*
 * This file contains the definitions and descriptions of an API for the 
 * Bolport "Ixpando" project.  It is meant to be used in any Ixpando program.
 *
 */

// MCP23017 addresses
#define IXPANDO_I2C_ADDR_DEFAULT 0x20
#define IXPANDO_I2C_ADDR_21      0x21
#define IXPANDO_I2C_ADDR_22      0x22
#define IXPANDO_I2C_ADDR_23      0x23
#define IXPANDO_I2C_ADDR_24      0x24
#define IXPANDO_I2C_ADDR_25      0x25
#define IXPANDO_I2C_ADDR_26      0x26
#define IXPANDO_I2C_ADDR_27      0x27

// MCP23017 registers
#define IXPANDO_IODIRB 0x01
#define IXPANDO_IPOLA  0x02
#define IXPANDO_GPPUA  0x0c
#define IXPANDO_GPIOA  0x12
#define IXPANDO_OLATB  0x15


// Ixpando API

/*
 * Initializes the Ixpando board to the given I2C address.  
 * Returns a negative number on error or 0 on success.
 */
int Ixpando_Init(int i2cAddr);

/* 
 * Reads the ixpando switches from portA.
 * Returns the value read.
 *
 */
unsigned char Ixpando_Read();

/*
 * Writes a value to the ixpando LEDs on portB.
 * Returns a negative number on error or 0 on success.
 *
 */
int Ixpando_Write(unsigned char value);

