#include "led.h"
#include "MK70F12.h"

void led_init()
{
	// Enable clock gating to the correct pin port
	SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;
	
	// Configure the LED pins to be GPIOs
	PORTA_PCR11 = PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
	PORTA_PCR10 = PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;

	PORTA_PCR28 = PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
	PORTA_PCR29 = PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
	
	// Set the LED GPIO pins as outputs, and set them by default
	// (the LEDs are 'active-low')
	GPIOA_PDDR = (1 << 11) | (1 << 10) | (1 << 28) | (1 << 29);
	GPIOA_PDOR = (1 << 11) | (1 << 10) | (1 << 28) | (1 << 29);
}

void led_on(int led_id)
{
	switch(led_id)
	{
		case LED_RED:
			GPIOA_PCOR = BIT_RED;
			break;
		case LED_BLUE:
			GPIOA_PCOR = BIT_BLUE;
			break;
		case LED_YELLOW:
			GPIOA_PCOR = BIT_YELLOW;
			break;
		case LED_GREEN:
			GPIOA_PCOR = BIT_GREEN;
			break;
	}
}

void led_off(int led_id)
{
	switch(led_id)
	{
		case LED_RED:		
			GPIOA_PSOR = BIT_RED;
			break;
		case LED_BLUE:
			GPIOA_PSOR = BIT_BLUE;
			break;
		case LED_YELLOW:
			GPIOA_PSOR = BIT_YELLOW;
			break;
		case LED_GREEN:
			GPIOA_PSOR = BIT_GREEN;
			break;
	}
}

void led_toggle(int led_id)
{
	switch(led_id)
	{
		case LED_RED:		
			GPIOA_PTOR = BIT_RED;
			break;
		case LED_BLUE:
			GPIOA_PTOR = BIT_BLUE;
			break;
		case LED_YELLOW:
			GPIOA_PTOR = BIT_YELLOW;
			break;
		case LED_GREEN:
			GPIOA_PTOR = BIT_GREEN;
			break;
	}
}
