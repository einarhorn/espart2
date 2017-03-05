#include "button.h"

#include "MK70F12.h"
void btn_init()
{
	// Enable clock gating to the correct pin port
	SIM_SCGC5 |= SIM_SCGC5_PORTD_MASK;
	SIM_SCGC5 |= SIM_SCGC5_PORTE_MASK;
	
	// Configure the LED pins to be GPIOs
	PORTD_PCR0 = PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
	PORTE_PCR26 = PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
	
	// Set the LED GPIO pins as outputs, and set them by default
	// (the LEDs are 'active-low')
	GPIOD_PDDR &= (0 << 0);
	GPIOE_PDDR &= (0 << 26);
}




int btn_pushed(int btn_id){
	switch(btn_id)
	{
		case BTN_1:
			return ( (GPIOD_PDIR & BTN_BIT_1) != BTN_BIT_1 );
		case BTN_2:
			return ( (GPIOE_PDIR & BTN_BIT_2) != BTN_BIT_2 );
	
	}

	return 0;

}

/*
void btn_push(int btn_id)
{
	switch(btn_id)
	{
		case BTN_1:
			GPIOD_PCOR = BTN_BIT_1;
			break;
		case BTN_2:
			GPIOE_PCOR = BTN_BIT_2;
			break;
	}
}

void btn_release(int btn_id)
{
	switch(btn_id)
	{
		case BTN_1:		
			GPIOD_PSOR = BTN_BIT_1;
			break;
		case BTN_2:
			GPIOE_PSOR = BTN_BIT_2;
			break;
	}
}
*/

/*
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
}*/
