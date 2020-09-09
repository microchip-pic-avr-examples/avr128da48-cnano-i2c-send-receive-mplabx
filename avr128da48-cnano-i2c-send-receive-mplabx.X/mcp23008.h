/*
    \file   mcp23008.h

    \brief  8-bit I/O Expander I2C Slave Driver - header file

    (c) 2020 Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip software and any
    derivatives exclusively with Microchip products. It is your responsibility to comply with third-party
    license terms applicable to your use of third-party software (including open source software) that
    may accompany Microchip software.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS
    FOR A PARTICULAR PURPOSE.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS
    SOFTWARE.
*/

#ifndef MCP23008_H_INCLUDED
#define	MCP23008_H_INCLUDED

#include <xc.h> 
#include <stdbool.h>
#include <stdlib.h>
#include "i2c.h"

#define MCP23008_SLAVE_ADDR         0x20    /* IO Expander slave device address */ 
#define MCP23008_IODIR_REG          0x00    /* IO Expander IODIR register address */
#define MCP23008_PORT_REG           0x09    /* IO Expander PORT register address */
#define MCP23008_IODIR_OUTPUT_CMD   0x00    /* Used to set all pins as outputs */

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

/* Sends a command to the IO Expander I2C slave device 
 * - returns true if 2 bytes have been sent 
 * - return false if slave did not ACK/an unexpected number of bytes have been 
 * sent
 * The arguments are the address of the I2C slave device register and the data 
 * to be written to that register
 */
bool MCP23008_Write(uint8_t address, uint8_t data);

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* MCP23008_H */

