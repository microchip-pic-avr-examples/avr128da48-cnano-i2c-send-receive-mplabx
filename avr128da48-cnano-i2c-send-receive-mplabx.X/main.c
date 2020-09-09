/*
    \file   main.c

    \brief  I2C Read Write Example

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

#include <xc.h>
#include "clkctrl.h"
#include "i2c.h"
#include "usart1.h"
#include "mcp23008.h"
#include "mcp3221.h"
#include <util/delay.h>

#define LEDS_NUMBER         8
#define BINARY_PATTERN      "%c%c%c%c%c%c%c%c"
#define BINARY_CONVERT(x) \
  (x & 0x80 ? '1' : '0'), \
  (x & 0x40 ? '1' : '0'), \
  (x & 0x20 ? '1' : '0'), \
  (x & 0x10 ? '1' : '0'), \
  (x & 0x08 ? '1' : '0'), \
  (x & 0x04 ? '1' : '0'), \
  (x & 0x02 ? '1' : '0'), \
  (x & 0x01 ? '1' : '0') 

void main_i2c_scan(uint8_t addr_min, uint8_t addr_max);
uint8_t getLedSequence(uint16_t value);

int main(void) 
{
    uint16_t result = 0;
    uint8_t LED_seq = 0;
    
    /* Initialize all the required modules */
    CLKCTRL_Init();
    I2C_0_Init();
    USART1_Init();
    
    _delay_ms(2000);
    
    main_i2c_scan(0x00, 0x7F);
    
    _delay_ms(500);
    
    /* Configure the IO Expander PORT pins as outputs */
    if (MCP23008_Write(MCP23008_IODIR_REG, MCP23008_IODIR_OUTPUT_CMD))
    {
        printf("\n\r MCP23008 PORT direction command sent");
    }
    else
    {
        printf("\n\r MCP23008_Write failed!");
    }
    
    while (1)
    {
        /* Read the ADC result */
        if (MCP3221_Read(&result))
        {
            LED_seq = getLedSequence(result);
            printf("\n\r MCP3221 ADC result %u | LED bar: "BINARY_PATTERN, result, BINARY_CONVERT(LED_seq));
        }
        else
        {
            printf("\n\r MCP3221_Read failed!");
        }
        
        /* Drive the IO Expander outputs */
        if (!MCP23008_Write(MCP23008_PORT_REG, LED_seq))
        {
            printf("   MCP23008_Write failed!");
        }
        
        _delay_ms(100);
    }
}

/* Scans for I2C slave devices on the bus - that have an address within the 
 *specified range [addr_min, addr_max]
 */
void main_i2c_scan(uint8_t addr_min, uint8_t addr_max)
{
    uint8_t slave_address, ret;
    printf("\n\r I2C Scan started from 0x%02X to 0x%02X:", addr_min, addr_max);
    for (slave_address = addr_min; slave_address <= addr_max; slave_address++)
    {
        printf("\n\r Scanning slave address = 0x%02X", (int)slave_address);
        ret = I2C_0_SendData((slave_address<<1), NULL, 0);
        I2C_0_EndSession();
        if(ret != 0xFF)
        {
            printf(" --> slave ACKED");
        }
        _delay_ms(10);
    }
    printf("\n\r I2C Scan ended\n\r");
}

/* Returns the LED sequence to be sent to the IO Expander */
uint8_t getLedSequence(uint16_t value)
{
    uint8_t seq = 0;
    
    value = value >> 9;
    
    for (uint8_t i = 0; i <= value; i++)
    {
        seq = (seq << 1) + 1;
    }
    
    return seq;
}
