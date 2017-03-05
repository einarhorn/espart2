/*
 * Bare metal template created by Harry Wagstaff
 * Based on Freescale Codewarrior Bareboard project template
 * Edited by Stan Manilov
 */

#include "MK70F12.h"

#include "led.h"
#include "button.h"


void uart_init(UART_MemMapPtr uartChannel);
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

/*	//uart
	SIM_SCGC5 |= SIM_SCGC5_PORTE_MASK;

	SIM_SCGC4 |= SIM_SCGC4_UART2_MASK;

	PORTE_PCR16 = PORT_PCR_MUX(0x3); // UART is ALT3 function for this pin

    	PORTE_PCR17 = PORT_PCR_MUX(0x3); 

	UART_C2_REG(UART2_BASE_PTR) |= (UART_C2_TE_MASK | UART_C2_RE_MASK );
*/

    	uart_init(UART2_BASE_PTR);

	btn_init();

	led_init();
}

void uart_init(UART_MemMapPtr uartChannel){
	if(uartChannel == UART0_BASE_PTR) {
    	/* Enable clock for PORTF */
    	SIM_SCGC5 |= SIM_SCGC5_PORTF_MASK;

    	/* Enable clock for UART0 */
		SIM_SCGC4 |= SIM_SCGC4_UART0_MASK;

    	/* Pin G1/PTF18 (See 10.3.1 on page 275 of the K70 Sub-Family Reference
		 * Manual, Rev. 2, Dec 2011).  Select the UART0_TXD function on PTF18 using the
		 * Pin Control Register (PORTx_PCRn) */
    	PORTF_PCR18 = PORT_PCR_MUX(0x4); // UART is ALT4 function for this pin

    	/* Pin F1/PTF17 */
       	/* Enable the UART0_RXD function on PTF17 */
    	PORTF_PCR17 = PORT_PCR_MUX(0x4); // UART is ALT4 function for this pin
    } else if (uartChannel == UART1_BASE_PTR) {
    	/* Enable clock for PORTE */
    	SIM_SCGC5 |= SIM_SCGC5_PORTE_MASK;

    	/* Enable clock for UART1 */
		SIM_SCGC4 |= SIM_SCGC4_UART1_MASK;

    	/* Pin E2/PTE0 */
		/* Enable the UART1_TXD function on PTE0 */
		PORTE_PCR0 = PORT_PCR_MUX(0x3); // UART is ALT3 function for this pin

    	/* Pin F2/PTE1 */
		/* Enable the UART1_RXD function on PTE1 */
		PORTE_PCR1 = PORT_PCR_MUX(0x3); // UART is ALT3 function for this pin
    } else if (uartChannel == UART2_BASE_PTR) {
    	/* Enable clock for PORTE */
    	SIM_SCGC5 |= SIM_SCGC5_PORTE_MASK;

    	/* Enable clock for UART2 */
    	SIM_SCGC4 |= SIM_SCGC4_UART2_MASK;

    	/* Pin J3/PTE16 */
    	/* Enable the UART2_TXD function on PTE16 */
    	PORTE_PCR16 = PORT_PCR_MUX(0x3); // UART is ALT3 function for this pin

    	/* Pin K2/PTE17 */
    	/* Enable the UART2_RXD function on PTE17 */
    	PORTE_PCR17 = PORT_PCR_MUX(0x3); // UART is ALT3 function for this pin
    } else if(uartChannel == UART3_BASE_PTR) {
    	/* Enable clock for PORTC */
    	SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;

    	/* Enable clock for UART3 */
    	SIM_SCGC4 |= SIM_SCGC4_UART3_MASK;
    	
    	/* Pin E9/PTC17 */
        /* Enable the UART3_TXD function on PTC17 */
    	PORTC_PCR17 = PORT_PCR_MUX(0x3); // UART is ALT3 function for this pin

    	/* Pin F9/PTC16 */
    	/* Enable the UART3_RXD function on PTC16 */
    	PORTC_PCR16 = PORT_PCR_MUX(0x3); // UART is ALT3 function for this pin
    } else if(uartChannel == UART4_BASE_PTR) {
    	/* Enable clock for PORTC */
    	SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;

    	/* Enable clock for UART4 */
    	SIM_SCGC1 |= SIM_SCGC1_UART4_MASK;
    	
    	/* Pin P7/PTE24 */
        /* Enable the UART4_TXD function on PTE24 */
    	PORTE_PCR24 = PORT_PCR_MUX(0x3); // UART is ALT3 function for this pin

    	/* Pin R7/PTE25 */
    	/* Enable the UART4_RXD function on PTE25 */
    	PORTE_PCR25 = PORT_PCR_MUX(0x3); // UART is ALT3 function for this pin
    } else {
    	/* Enable clock for PORTE */
    	SIM_SCGC5 |= SIM_SCGC5_PORTE_MASK;

    	/* Enable clock for UART5 */
    	SIM_SCGC1 |= SIM_SCGC1_UART5_MASK;

    	/* Pin H4/PTE8 */
        /* Enable the UART5_TXD function on PTE8 */
    	PORTE_PCR8 = PORT_PCR_MUX(0x3); // UART is ALT3 function for this pin

    	/* Pin J1/PTE9 */
    	/* Enable the UART5_RXD function on PTE9 */
    	PORTE_PCR9 = PORT_PCR_MUX(0x3); // UART is ALT3 function for this pin
    }
               
	UART2_C1 |= UART_C1_M_MASK;
	UART2_C2 |= (UART_C2_TE_MASK | UART_C2_RE_MASK );


	NVICICPR1 = NVIC_ICPR_CLRPEND(1 << 17);
	// Enable interrupts from UART2 module
	NVICISER1 = NVIC_ISER_SETENA(1 << 17);
}


void main()
{
	int timer;
	while(1)
	{
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

	}
}


