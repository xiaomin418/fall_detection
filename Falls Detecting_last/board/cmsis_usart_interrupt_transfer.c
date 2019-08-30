/*
 * The Clear BSD License
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted (subject to the limitations in the disclaimer below) provided
 *  that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE GRANTED BY THIS LICENSE.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "board.h"
#include "cmsis_usart.h"
#include "pin_mux.h"
#include "clock_config.h"

#include "stdarg.h"
#include "global.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define ECHO_BUFFER_LENGTH 8
/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/* USART user SignalEvent */
//void USART_SignalEvent_t(uint32_t event);
/*******************************************************************************
 * Variables
 ******************************************************************************/
const uint8_t g_tipString[] =
    "USART CMSIS interrupt example\r\nBoard receives 8 characters then sends them out\r\nNow please input:\r\n";
uint8_t g_txBuffer[ECHO_BUFFER_LENGTH] = {0};

volatile bool rxBufferEmpty = true;
volatile bool txBufferFull = false;
volatile bool txOnGoing = false;
volatile bool rxOnGoing = false;

/*******************************************************************************
 * Code
 ******************************************************************************/

uint32_t UART0_GetFreq(void)
{
    return CLOCK_GetFreq(UART0_CLK_SRC);
}

uint32_t UART4_GetFreq(void)
{
    return CLOCK_GetFreq(UART4_CLK_SRC);
}

uint32_t UART2_GetFreq(void)
{
    return CLOCK_GetFreq(UART2_CLK_SRC);
}

void USART0_SignalEvent_t(uint32_t event)
{
    if (ARM_USART_EVENT_SEND_COMPLETE == event)
    {
        txOnGoing = false;
    }

    if (ARM_USART_EVENT_RECEIVE_COMPLETE == event)
    {
				Driver_USART0.Receive(&g_rxBuffer0, 1);
				switch(g_rxBuffer0){
					case 'a':
						LED_Color=(LED_Color+1)%8;
					break;
					case 's':
						LED_Color=(LED_Color+7)%8;
					break;
					case 'd':
						LED_Color=6;
						//uart0_Printf("À§µπ¡À£°");
						//uart2_Printf("À§µπ¡À£°");
					break;
					default:
						LED_Color=5;
					break;
				}
    }
}

void USART4_SignalEvent_t(uint32_t event)
{
    if (ARM_USART_EVENT_SEND_COMPLETE == event)
    {
        txOnGoing = false;
    }

    if (ARM_USART_EVENT_RECEIVE_COMPLETE == event)
    {
				Driver_USART4.Receive(&g_rxBuffer4, 1);
				switch(g_rxBuffer4){
					case 'a':
						LED_Color=(LED_Color+1)%8;
					break;
					case 's':
						LED_Color=(LED_Color+7)%8;
					break;
					default:
						LED_Color=5;
					break;
				}
    }
}

void USART2_SignalEvent_t(uint32_t event)
{
    if (ARM_USART_EVENT_SEND_COMPLETE == event)
    {
        txOnGoing = false;
    }

    if (ARM_USART_EVENT_RECEIVE_COMPLETE == event)
    {
				Driver_USART2.Receive(&g_rxBuffer2, 1);
				/*switch(g_rxBuffer2){
					case 'a':
						LED_Color=(LED_Color+1)%8;
					break;
					case 's':
						LED_Color=(LED_Color+7)%8;
					break;
					default:
						LED_Color=5;
					break;
				}*/
    }
}
/*!
 * @brief Main function
 */
void uart0_init(void)
{
    Driver_USART0.Initialize(USART0_SignalEvent_t);
    Driver_USART0.PowerControl(ARM_POWER_FULL);

    /* Set baudrate. */
    Driver_USART0.Control(ARM_USART_MODE_ASYNCHRONOUS, BOARD_DEBUG_UART_BAUDRATE);

    txOnGoing = true;
    Driver_USART0.Send(g_tipString, sizeof(g_tipString) - 1);

    /* Wait send finished */
    while (txOnGoing)
    {
    }
		Driver_USART0.Receive(&g_rxBuffer0, 1);
}

void uart4_init(void)
{
    Driver_USART4.Initialize(USART4_SignalEvent_t);
    Driver_USART4.PowerControl(ARM_POWER_FULL);

    /* Set baudrate. */
    Driver_USART4.Control(ARM_USART_MODE_ASYNCHRONOUS, BOARD_DEBUG_UART_BAUDRATE);

    txOnGoing = true;
    Driver_USART4.Send(g_tipString, sizeof(g_tipString) - 1);

    /* Wait send finished */
    while (txOnGoing)
    {
    }
		Driver_USART4.Receive(&g_rxBuffer4, 1);
}

void uart2_init(void)
{
    Driver_USART2.Initialize(USART2_SignalEvent_t);
    Driver_USART2.PowerControl(ARM_POWER_FULL);

    /* Set baudrate. */
    Driver_USART2.Control(ARM_USART_MODE_ASYNCHRONOUS, BOARD_DEBUG_UART_BAUDRATE);

    txOnGoing = false;
    //Driver_USART2.Send(g_tipString, sizeof(g_tipString) - 1);

    /* Wait send finished */
    //while (txOnGoing)
    //{
    //}
		Driver_USART2.Receive(&g_rxBuffer2, 1);
}

void uart0_Printf(char *pcFmt,...){
		 va_list ap;
		 char pbString[256];
		 char* ptr=pbString;
		 va_start(ap,pcFmt);
		 vsprintf(pbString,pcFmt,ap);
     
      while(*ptr){
				if (!txOnGoing){
					txOnGoing = true;
					Driver_USART0.Send(ptr,1);
					*ptr++;
				}
			}
     va_end(ap);
}

void uart4_Printf(char *pcFmt,...){
		 va_list ap;
		 char pbString[256];
		 char* ptr=pbString;
	   char r='\r';
 		 va_start(ap,pcFmt);
		 vsprintf(pbString,pcFmt,ap);
     
      while(*ptr){
				if (!txOnGoing){
					txOnGoing = true;
					if(*ptr=='\n'){
					Driver_USART4.Send(&r,1);
					while(txOnGoing);
					txOnGoing = true;
					}						
					Driver_USART4.Send(ptr,1);
					*ptr++;
				}
			}
     va_end(ap);
}

void uart2_Printf(char *pcFmt,...){
		 va_list ap;
		 char pbString[256];
		 char* ptr=pbString;
	   char r='\r';
 		 va_start(ap,pcFmt);
		 vsprintf(pbString,pcFmt,ap);
     
      while(*ptr){
				if (!txOnGoing){
					txOnGoing = true;
					if(*ptr=='\n'){
					Driver_USART2.Send(&r,1);
					while(txOnGoing);
					txOnGoing = true;
					}						
					Driver_USART2.Send(ptr,1);
					*ptr++;
				}
			}
     va_end(ap);
}
