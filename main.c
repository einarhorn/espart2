/*
 * Bare metal template created by Harry Wagstaff
 * Based on Freescale Codewarrior Bareboard project template
 * Edited by Stan Manilov
 */

#include "MK70F12.h"

#include "led.h"
#include "button.h"
#include "uart.h"



// __init_hardware is called by the Freescale __thumb_startup function (see 
// vectors.c)
void __init_hardware()
{
	// Disable the Watchdog module. This module is designed to reset
	// the board in case it crashes for some reason. We don't need it,
	// so we disable it here.
	WDOG_UNLOCK = 0xC520;
	WDOG_UNLOCK = 0xD928;
	WDOG_STCTRLH = 0xD2;

	// Configure the MCG - set up clock dividers on 
	SIM_CLKDIV1 = SIM_CLKDIV1_OUTDIV1(0) | SIM_CLKDIV1_OUTDIV2(0) | SIM_CLKDIV1_OUTDIV3(1) | SIM_CLKDIV1_OUTDIV4(1);
	MCG_C1 = MCG_C1_CLKS(2);

	
	// use a baud rate of 115200
    	uart_init(UART_2, UART_2_CLK, 115200);

	btn_init();

	led_init();
}

void main()
{
	int timer;

	while(1)
	{
	//	uart_putchar(UART_2, 'h');
	//	uart_putchar(UART_2, 'i');

		timer = 500000; 
		while(timer--) ;
		/*
		if ((GPIOD_PDIR & (1 << 0)) != (1 << 0)) {
			led_off(LED_RED);		
		}else{
			led_on(LED_RED);
		}
		if ((GPIOE_PDIR & (1 << 26)) != (1 << 26)) {
			led_off(LED_BLUE);		
		}else{
			led_on(LED_BLUE);
		}*/

		if ( btn_pushed(BTN_1) ) {
			led_off(LED_RED);
		} else {
			led_on(LED_RED);
		}

		if ( btn_pushed(BTN_2) ) {
			led_off(LED_BLUE);
		} else {
			led_on(LED_BLUE);
		}

		if ( uart_getchar_present(UART_2) ){
			char currChar = uart_getchar(UART_2);
			uart_putchar(UART_2, currChar);
			//uart_putchar(UART_2, 'h');
			//uart_putchar(UART_2, 'i');
		//	led_on(LED_GREEN);
		}

	}
}


