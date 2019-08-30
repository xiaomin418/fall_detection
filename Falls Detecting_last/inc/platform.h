#ifndef PLATFORM_H
#define PLATFORM_H

#include "MK64F12.h"



typedef enum {
	PTA0 = (0 << 16) | 0,
	PTA1 = (0 << 16) | 1,
	PTA2 = (0 << 16) | 2,
	PTA3 = (0 << 16) | 3,
	PTA4 = (0 << 16) | 4,
	PTA5 = (0 << 16) | 5,
	PTA6 = (0 << 16) | 6,
	PTA7 = (0 << 16) | 7,
	PTA8 = (0 << 16) | 8,
	PTA9 = (0 << 16) | 9,
	PTA10= (0 << 16) | 10,
	PTA11= (0 << 16) | 11,
	PTA12= (0 << 16) | 12,
	PTA13= (0 << 16) | 13,
	PTA14= (0 << 16) | 14,
	PTA15= (0 << 16) | 15,
	PTA16= (0 << 16) | 16,
	PTA17= (0 << 16) | 17,
	PTA18= (0 << 16) | 18,
	PTA19= (0 << 16) | 19,
	PTA20= (0 << 16) | 20,
	PTA21= (0 << 16) | 21,
	PTA22= (0 << 16) | 22,
	PTA23= (0 << 16) | 23,
	PTA24= (0 << 16) | 24,
	PTA25= (0 << 16) | 25,
	PTA26= (0 << 16) | 26,
	PTA27= (0 << 16) | 27,
	PTA28= (0 << 16) | 28,
	PTA29= (0 << 16) | 29,
	PTA30= (0 << 16) | 30,
	PTA31= (0 << 16) | 31,

	
	PTB0 = (1 << 16) | 0,
	PTB1 = (1 << 16) | 1,
	PTB2 = (1 << 16) | 2,
	PTB3 = (1 << 16) | 3,
	PTB4 = (1 << 16) | 4,
	PTB5 = (1 << 16) | 5,
	PTB6 = (1 << 16) | 6,
	PTB7 = (1 << 16) | 7,
	PTB8 = (1 << 16) | 8,
	PTB9 = (1 << 16) | 9,
	PTB10= (1 << 16) | 10,
	PTB11= (1 << 16) | 11,
	PTB12= (1 << 16) | 12,
	PTB13= (1 << 16) | 13,
	PTB14= (1 << 16) | 14,
	PTB15= (1 << 16) | 15,
	PTB16= (1 << 16) | 16,
	PTB17= (1 << 16) | 17,
	PTB18= (1 << 16) | 18,
	PTB19= (1 << 16) | 19,
	PTB20= (1 << 16) | 20,
	PTB21= (1 << 16) | 21,
	PTB22= (1 << 16) | 22,
	PTB23= (1 << 16) | 23,
	PTB24= (1 << 16) | 24,
	PTB25= (1 << 16) | 25,
	PTB26= (1 << 16) | 26,
	PTB27= (1 << 16) | 27,
	PTB28= (1 << 16) | 28,
	PTB29= (1 << 16) | 29,
	PTB30= (1 << 16) | 30,
	PTB31= (1 << 16) | 31,
	
	PTC0 = (2 << 16) | 0,
	PTC1 = (2 << 16) | 1,
	PTC2 = (2 << 16) | 2,
	PTC3 = (2 << 16) | 3,
	PTC4 = (2 << 16) | 4,
	PTC5 = (2 << 16) | 5,
	PTC6 = (2 << 16) | 6,
	PTC7 = (2 << 16) | 7,
	PTC8 = (2 << 16) | 8,
	PTC9 = (2 << 16) | 9,
	PTC10= (2 << 16) | 10,
	PTC11= (2 << 16) | 11,
	PTC12= (2 << 16) | 12,
	PTC13= (2 << 16) | 13,
	PTC14= (2 << 16) | 14,
	PTC15= (2 << 16) | 15,
	PTC16= (2 << 16) | 16,
	PTC17= (2 << 16) | 17,
	PTC18= (2 << 16) | 18,
	PTC19= (2 << 16) | 19,
	PTC20= (2 << 16) | 20,
	PTC21= (2 << 16) | 21,
	PTC22= (2 << 16) | 22,
	PTC23= (2 << 16) | 23,
	PTC24= (2 << 16) | 24,
	PTC25= (2 << 16) | 25,
	PTC26= (2 << 16) | 26,
	PTC27= (2 << 16) | 27,
	PTC28= (2 << 16) | 28,
	PTC29= (2 << 16) | 29,
	PTC30= (2 << 16) | 30,
	PTC31= (2 << 16) | 31,	
	
	PTD0 = (3 << 16) | 0,
	PTD1 = (3 << 16) | 1,
	PTD2 = (3 << 16) | 2,
	PTD3 = (3 << 16) | 3,
	PTD4 = (3 << 16) | 4,
	PTD5 = (3 << 16) | 5,
	PTD6 = (3 << 16) | 6,
	PTD7 = (3 << 16) | 7,
	PTD8 = (3 << 16) | 8,
	PTD9 = (3 << 16) | 9,
	PTD10= (3 << 16) | 10,
	PTD11= (3 << 16) | 11,
	PTD12= (3 << 16) | 12,
	PTD13= (3 << 16) | 13,
	PTD14= (3 << 16) | 14,
	PTD15= (3 << 16) | 15,
	PTD16= (3 << 16) | 16,
	PTD17= (3 << 16) | 17,
	PTD18= (3 << 16) | 18,
	PTD19= (3 << 16) | 19,
	PTD20= (3 << 16) | 20,
	PTD21= (3 << 16) | 21,
	PTD22= (3 << 16) | 22,
	PTD23= (3 << 16) | 23,
	PTD24= (3 << 16) | 24,
	PTD25= (3 << 16) | 25,
	PTD26= (3 << 16) | 26,
	PTD27= (3 << 16) | 27,
	PTD28= (3 << 16) | 28,
	PTD29= (3 << 16) | 29,
	PTD30= (3 << 16) | 30,
	PTD31= (3 << 16) | 31,

	PTE0 = (4 << 16) | 0,
	PTE1 = (4 << 16) | 1,
	PTE2 = (4 << 16) | 2,
	PTE3 = (4 << 16) | 3,
	PTE4 = (4 << 16) | 4,
	PTE5 = (4 << 16) | 5,
	PTE6 = (4 << 16) | 6,
	PTE7 = (4 << 16) | 7,
	PTE8 = (4 << 16) | 8,
	PTE9 = (4 << 16) | 9,
	PTE10= (4 << 16) | 10,
	PTE11= (4 << 16) | 11,
	PTE12= (4 << 16) | 12,
	PTE13= (4 << 16) | 13,
	PTE14= (4 << 16) | 14,
	PTE15= (4 << 16) | 15,
	PTE16= (4 << 16) | 16,
	PTE17= (4 << 16) | 17,
	PTE18= (4 << 16) | 18,
	PTE19= (4 << 16) | 19,
	PTE20= (4 << 16) | 20,
	PTE21= (4 << 16) | 21,
	PTE22= (4 << 16) | 22,
	PTE23= (4 << 16) | 23,
	PTE24= (4 << 16) | 24,
	PTE25= (4 << 16) | 25,
	PTE26= (4 << 16) | 26,
	PTE27= (4 << 16) | 27,
	PTE28= (4 << 16) | 28,
	PTE29= (4 << 16) | 29,
	PTE30= (4 << 16) | 30,
	PTE31= (4 << 16) | 31,
	
	// Other Pin Names
	LEDR = PTB22,
	LEDB = PTB21,
	LEDG = PTE26,

	BUTTON = PTC6,
	BUTTON2 = PTA4,
	LED1 = LEDR,
	TEST_PIN = PTE24, //J2 #24

	// Not connected
	NC = (int)0xFFFFFFFF


} Pin;


#define CLK_FREQ 120000000UL

#define HIGH 1
#define LOW 0

#define GET_PORT_INDEX(pin) ((pin) >> 16)
#define GET_PIN_INDEX(pin) ((pin) & 0xFF)

#define GET_PORT(pin) (GPIO_MemMapPtr)(PTA_BASE  + 0x40 * GET_PORT_INDEX(pin))
#define PCR_INDEX(pin) ((uint32_t*)(PORTA_BASE + (0x1000 * GET_PORT_INDEX(pin)) + 0x04 * GET_PIN_INDEX(pin) ))


#endif

// *******************************ARM University Program Copyright � ARM Ltd 2014*************************************