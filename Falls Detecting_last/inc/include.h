/*#define ARM_MATH_CM4
#include "MK64F12.h"
#include "arm_math.h"


#include "i2c.h"
#include "i2s.h"
#include "dma.h"

#include "global.h"
#include "audio.h"*/

#include "fsl_debug_console.h"
#include "board.h"
#include "fsl_pit.h"
#include "pit.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "gpio.h"
#include "LED.h"
#include "MPU9250.h"
#include "global.h"
#include "delay.h"
#include "cmsis_usart.h"
#include "gpio_input_interrupt.h"
