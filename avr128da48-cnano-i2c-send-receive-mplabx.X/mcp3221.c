/*
    \file   mcp3221.c

    \brief  12-bit ADC I2C Slave Driver

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

#include "mcp3221.h"

/* Reads the ADC conversion result from the 12-bit ADC I2C slave device
 * - returns true if 2 bytes have been received
 * - returns false if slave did not ACK/an unexpected number of bytes have been 
 * received
 * Only one single word (uint16_t) variable must be allocated
 */
bool MCP3221_Read (uint16_t *pData)
{
    uint8_t ret;
    uint8_t *pDataTemp = (uint8_t *)pData;
    
    if(pData == NULL)
    {
        return false;
    }
    
    ret = I2C_0_GetData((MCP3221_SLAVE_ADDR << 1),  pDataTemp, 2);
    I2C_0_EndSession();
    
    if(ret == 2)
    {
        /* Change received bytes order */
        pDataTemp[0] = pDataTemp[0] + pDataTemp[1];
        pDataTemp[1] = pDataTemp[0] - pDataTemp[1];
        pDataTemp[0] = pDataTemp[0] - pDataTemp[1];
        return true;
    }
    
    return false;
}
