
#include "MK64F12.h"
#include "platform.h"
#include "gpio.h"

//static void (*port_callbacks[5])(int status) = { 0 };

void gpio_toggle(Pin pin) {
	GPIO_MemMapPtr p = GET_PORT(pin);
	uint32_t pin_index = GET_PIN_INDEX(pin);
	
	p->PTOR |= 1u << pin_index;
	
}

void gpio_set(Pin pin, int value) {
	GPIO_MemMapPtr p = GET_PORT(pin);
	uint32_t pin_index = GET_PIN_INDEX(pin);
	
	p->PDOR = (p->PDIR & ~(1u << pin_index)) | (((unsigned int)!!value) << pin_index);
}

int gpio_get(Pin pin) {
  GPIO_MemMapPtr p = GET_PORT(pin);
	uint32_t pin_index = GET_PIN_INDEX(pin);
	return (p->PDIR >> pin_index) & 0x1;
}

void gpio_set_range(Pin pin_base, int count, int value) {
	GPIO_MemMapPtr p = GET_PORT(pin_base);
	uint32_t pin_index = GET_PIN_INDEX(pin_base);
	uint32_t mask = ((1 << count) - 1) << pin_index;
	p->PDOR = (p->PDOR & ~mask) | ((value << pin_index) & mask);
}

unsigned int gpio_get_range(Pin pin_base, int count) {
	GPIO_MemMapPtr p = GET_PORT(pin_base);
	uint32_t pin_index = GET_PIN_INDEX(pin_base);
	return (p->PDIR >> pin_index) & ((1 << count) - 1);
}

void gpio_set_mode(Pin pin, PinMode mode, int value) {
	GPIO_MemMapPtr p = GET_PORT(pin);
//	uint32_t port_index = GET_PORT_INDEX(pin);
	uint32_t pin_index = GET_PIN_INDEX(pin);
	uint32_t* pPCR = PCR_INDEX(pin);

	// Enable the clock to the port.
	//SIM->SCGC5 |= 1u << (SIM_SCGC5_PORTA_SHIFT + (port_index));
	
	
	switch(mode) {
		case Reset:
			break;
		case Input:
			p->PDDR &= ~(1 << pin_index); // Set as input.
			*pPCR |= 1u << 8; // Pin mux GPIO.
			break;
		case Output:
			p->PDDR |= (1 << pin_index); // Set as output.
			*pPCR |= 0x1u << 8; // Pin mux GPIO.
			p->PDOR = (p->PDIR & ~(1u << pin_index)) | (((unsigned int)!!value) << pin_index);//上下拉
			break;
		case PullUp:
			p->PDDR |= 1 << pin_index; // Set as input.
		 *pPCR|= (0x1 << 8) | // Pin mux GPIO.
			       (0x1 << 1) | // Pin pull enable.
			       (0x1 << 0);  // Enable pullup resistor.
			gpio_set(pin, 1);
			break;
		case PullDown:
			p->PDDR |= 1 << pin_index; // Set as input.
		 *pPCR|= (0x1 << 8) | // Pin mux GPIO.
			       (0x1 << 1) | // Pin pull enable.
			       (0x0 << 0);  // Enable pulldown resistor.
			gpio_set(pin, 0);
			break;
	}
	
}

void gpio_set_trigger(Pin pin, TriggerMode trig) {

}

void gpio_set_callback(Pin pin, void (*callback)(int status)) {

}

void port_isr(int port) {

}

void port_isr0(void) {
	port_isr(0);
}

void port_isr1(void) {
	port_isr(1);
}

void port_isr2(void) {
	port_isr(2);
}

void port_isr3(void) {
	port_isr(3);
}

void port_isr4(void) {
	port_isr(4);
}

// *******************************ARM University Program Copyright © ARM Ltd 2014*************************************   
