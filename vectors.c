#include <stdint.h>

#include "vectors.h"
#include "MK70F12.h"
#include "led.h"

// __thumb_startup is provided by the Freescale C library
//
extern void __thumb_startup();

// __SP_INIT is provided by the linker script and places the initial stack 
// pointer into RAM
//
extern uint32_t __SP_INIT[];

// The flash storage on the K70 board contains a single configuration field 
// which is 'conveniently' positioned halfway up the first page of flash. 
// This #pragma and data field does some basic configuration of the flash 
// storage
//
#pragma define_section cfmconfig ".cfmconfig" ".cfmconfig" ".cfmconfig" far_abs R
#pragma explicit_zero_data on
__declspec(cfmconfig) uint32_t _cfm[4] = {0xffffffff, 0xffffffff, 0xffffffff, 0xfffffffe};

// A default interrupt handler which causes the device to hang and flash two
// of the LEDs. If the LED ports aren't configured correctly, the device will
// likely reset.
//
// Note to students who have developed for embedded systems before: The ARMv7-M
// architecture allows any ABI-conforming function to be used as an ISR, 
// meaning that no special decoration or entry/exit sequence is required 
// for ISRs.
//
static void default_isr()
{
	while(1) 
	{
		int i = 10000000;
		GPIOA_PTOR = (1 << 28) | (1 << 29);
		while(i--);
	}
}



static void test_isr() {
	led_on(LED_GREEN);
	/*while(1) 
	{
		int i = 10000000;
		GPIOA_PTOR = (1 << 0) | (1 << 29) | (1 << 28);
		while(i--);
	}*/




}
// The interrupt vector table. The #pragma line puts it in the correct text 
// section (defined in the linker script). The table then consists of the 
// initial stack pointer, followed by the vectors.
//
#pragma define_section vectortable ".vectortable" ".vectortable" ".vectortable" far_abs R
volatile __declspec(vectortable) vt_with_sp_t __vect_table = {
	__SP_INIT,
	{
		//Exception Vectors
		__thumb_startup, // 0x01 Reset vector
		default_isr,     // 0x02 NMI Vector
		default_isr,     // 0x03 Hard Fault Vector
		default_isr,     // 0x04 Mem Manage Fault Vector
		default_isr,     // 0x05 Bus Fault Vector
		default_isr,     // 0x06 Usage Fault Vector
		default_isr,     // 0x07 Reserved
		default_isr,     // 0x08 Reserved
		default_isr,     // 0x09 Reserved
		default_isr,     // 0x0A Reserved
		default_isr,     // 0x0B SVCall
		default_isr,     // 0x0C Debug Monitor
		default_isr,     // 0x0D Reserved
		default_isr,     // 0x0E PendableSrv
		default_isr,     // 0x0F SysTick

		//External Interrupt Vectors
		default_isr,     // 0x10 DMA0 
		default_isr,     // 0x11 DMA1
		default_isr,     // 0x12 DMA2
		default_isr,     // 0x13 DMA3
		default_isr,     // 0x14 DMA4
		default_isr,     // 0x15 DMA5
		default_isr,     // 0x16 DMA6
		default_isr,     // 0x17 DMA7
		default_isr,     // 0x18 DMA8
		default_isr,     // 0x19 DMA9
		default_isr,     // 0x1A DMA10
		default_isr,     // 0x1B DMA11
		default_isr,     // 0x1C DMA12
		default_isr,     // 0x1D DMA13
		default_isr,     // 0x1E DMA14
		default_isr,     // 0x1F DMA15
		default_isr,     // 0x20 DMA Error
		default_isr,     // 0x21 MCM
		default_isr,     // 0x22 FTFL
		default_isr,     // 0x23 Read Collusion
		default_isr,     // 0x24 LVD LVW
		default_isr,     // 0x25 LLW
		default_isr,     // 0x26 Watchdog
		default_isr,     // 0x27 RNG
		default_isr,     // 0x28 I2C0
		default_isr,     // 0x29 I2C1
		default_isr,     // 0x2A SPI0
		default_isr,     // 0x2B SPI1
		default_isr,     // 0x2C SPI2 
		default_isr,     // 0x2D CAN0
		default_isr,     // 0x2E CAN0
		default_isr,     // 0x2F CAN0
		default_isr,     // 0x30 CAN0
		default_isr,     // 0x31 CAN0
		default_isr,     // 0x32 CAN0
		default_isr,     // 0x33 Reserved
		default_isr,     // 0x34 Reserved
		default_isr,     // 0x35 CAN1
		default_isr,     // 0x36 CAN1
		default_isr,     // 0x37 CAN1
		default_isr,     // 0x38 CAN1
		default_isr,     // 0x39 CAN1
		default_isr,     // 0x3A CAN1
		default_isr,     // 0x3B Reserved
		default_isr,     // 0x3C Reserved
		test_isr,     // 0x3D UART0_RX_TX
		default_isr,     // 0x3E UART0_ERR
		test_isr,     // 0x3F UART1_RX_TX
		default_isr,     // 0x40 UART1_ERR 
		test_isr,     // 0x41 UART2_RX_TX
		default_isr,     // 0x42 UART2_ERR
		test_isr,     // 0x43 UART3_RX_TX
		default_isr,     // 0x44 UART3_ERR
		test_isr,     // 0x45 UART4_RX_TX
		default_isr,     // 0x46 UART4_ERR
		test_isr,     // 0x47 UART5_RX_TX
		default_isr,     // 0x48 UART5_ERR
		default_isr,     // 0x49 ADC0
		default_isr,     // 0x4A ADC1
		default_isr,     // 0x4B CMP0
		default_isr,     // 0x4C CMP1
		default_isr,     // 0x4D CMP2
		default_isr,     // 0x4E FTM0
		default_isr,     // 0x4F FTM1
		default_isr,     // 0x50 FTM2
		default_isr,     // 0x51 CMT
		default_isr,     // 0x52 RTC
		default_isr,     // 0x53 Reserved
		default_isr,     // 0x54 PIT0
		default_isr,     // 0x55 PIT1
		default_isr,     // 0x56 PIT2
		default_isr,     // 0x57 PIT3
		default_isr, 
		default_isr, 
		default_isr, 
		default_isr, 
		default_isr, 
		default_isr, 
		default_isr, 
		default_isr, 
		default_isr, 
		default_isr, 
		default_isr, 
		default_isr, 
		default_isr, 
		default_isr, 
		default_isr, 
		default_isr, 
		default_isr, 
		default_isr, 
		default_isr, 
		default_isr, 
		default_isr, 
		default_isr, 
		default_isr, 
		default_isr, 
		default_isr, 
		default_isr, 
		default_isr, 
		default_isr, 
		default_isr, 
		default_isr, 
		default_isr, 
		default_isr, 
		default_isr 
	}
};

