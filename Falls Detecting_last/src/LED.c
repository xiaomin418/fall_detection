#include "include.h"


void init_LED() {  // init leds
gpio_set_mode(LEDR, Output, 1);
gpio_set_mode(LEDG, Output, 1);
gpio_set_mode(LEDB, Output, 1);
gpio_set_mode(PTC4, Output, 0);
gpio_set(LEDR, HIGH);
gpio_set(LEDG, HIGH);
gpio_set(LEDB, HIGH);
}

void set_LED(short color){
	switch(color){
		case 0:
			gpio_set(LEDR, HIGH);
			gpio_set(LEDG, HIGH);
			gpio_set(LEDB, HIGH);
			break;
		case 1:
			gpio_set(LEDR, LOW);
			gpio_set(LEDG, HIGH);
			gpio_set(LEDB, HIGH);
			break;
		case 2:
			gpio_set(LEDR, HIGH);
			gpio_set(LEDG, LOW);
			gpio_set(LEDB, HIGH);
			break;
		case 3:
			gpio_set(LEDR, LOW);
			gpio_set(LEDG, LOW);
			gpio_set(LEDB, HIGH);
			break;
		case 4:
			gpio_set(LEDR, HIGH);
			gpio_set(LEDG, HIGH);
			gpio_set(LEDB, LOW);
			break;
		case 5:
			gpio_set(LEDR, LOW);
			gpio_set(LEDG, HIGH);
			gpio_set(LEDB, LOW);
			break;
		case 6:
			gpio_set(LEDR, HIGH);
			gpio_set(LEDG, LOW);
			gpio_set(LEDB, LOW);
			break;
		case 7:
			gpio_set(LEDR, LOW);
			gpio_set(LEDG, LOW);
			gpio_set(LEDB, LOW);
			break;
		default:
			break;
	}
}



