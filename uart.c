#include "uart.h"

#include "MK70F12.h"
void uart_init(UART_MemMapPtr uartChannel, int clockInKHz, int baud){


	uint16_t sbr, brfa;
	uint8_t temp;
	
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

	                             
    /* Make sure that the transmitter and receiver are disabled while we 
     * change settings.
     */
    UART_C2_REG(uartChannel) &= ~(UART_C2_TE_MASK | UART_C2_RE_MASK );
    /* Configure the UART for 8-bit mode, no parity */
    UART_C1_REG(uartChannel) = 0;	/* We need all default settings, so entire register is cleared */
    
    /* Calculate baud settings */
    sbr = (uint16_t)((clockInKHz * 1000)/(baud * 16));
        
    /* Save off the current value of the UARTx_BDH except for the SBR field */
    temp = UART_BDH_REG(uartChannel) & ~(UART_BDH_SBR(0x1F));
    
    UART_BDH_REG(uartChannel) = temp |  UART_BDH_SBR(((sbr & 0x1F00) >> 8));
    UART_BDL_REG(uartChannel) = (uint8_t)(sbr & UART_BDL_SBR_MASK);
    
    /* Determine if a fractional divider is needed to get closer to the baud rate */
    brfa = ((((uint32_t)clockInKHz*32000)/(baud * 16)) - (sbr * 32));
    
    /* Save off the current value of the UARTx_C4 register except for the BRFA field */
    temp = UART_C4_REG(uartChannel) & ~(UART_C4_BRFA(0x1F));
    
    UART_C4_REG(uartChannel) = temp |  UART_C4_BRFA(brfa);    
    /* Enable receiver and transmitter */
	UART_C2_REG(uartChannel) |= (UART_C2_TE_MASK | UART_C2_RE_MASK );               
}

int uart_getchar_present (UART_MemMapPtr channel)
{
    return (UART_S1_REG(channel) & UART_S1_RDRF_MASK);
}

char uart_getchar (UART_MemMapPtr channel)
{
    /* Wait until character has been received */
    while (!(UART_S1_REG(channel) & UART_S1_RDRF_MASK));
    /* Return the 8-bit data from the receiver */
    return UART_D_REG(channel);
}

void uart_putchar (UART_MemMapPtr channel, char ch)
{
    /* Wait until space is available in the FIFO */
    while(!(UART_S1_REG(channel) & UART_S1_TDRE_MASK));
    /* Send the character */
    UART_D_REG(channel) = (uint8_t)ch;
}


