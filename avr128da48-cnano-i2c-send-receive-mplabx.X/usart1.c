/*
    \file   usart1.c

    \brief  USART1 Driver

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

#include "usart1.h"

#if defined(__GNUC__)

int USART1_printCHAR(char character, FILE *stream)
{
    USART1_Write(character);
    return 0;
}

FILE USART1_stream = FDEV_SETUP_STREAM(USART1_printCHAR, NULL, _FDEV_SETUP_WRITE);

#elif defined(__ICCAVR__)

int putchar(int outChar)
{
    USART0_Write(outChar);
    return outChar;
}
#endif

void USART1_Init(void)
{
    /* Set the TX pin as output */
    PORTC.DIR = PIN0_bm;
    
    /* Configure Baud Rate - 115200 */
    USART1.BAUD = (uint16_t)USART1_BAUD_RATE(115200);
	
    /* Enable TX */
    USART1.CTRLB =  USART_TXEN_bm;

#if defined(__GNUC__)
    stdout = &USART1_stream;
#endif
}

void USART1_Write(const uint8_t data)
{
    while (!(USART1.STATUS & USART_DREIF_bm))
            ;
    USART1.TXDATAL = data;
}