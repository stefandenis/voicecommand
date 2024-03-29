/**
 * \file
 *
 * \brief Driver initialization.
 *
 (c) 2018 Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms,you may use this software and
    any derivatives exclusively with Microchip products.It is your responsibility
    to comply with third party license terms applicable to your use of third party
    software (including open source software) that may accompany Microchip software.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 */

/*
 * Code generated by START.
 *
 * This file will be overwritten when reconfiguring your START project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */

#include "driver_init.h"
#include <system.h>

/* configure the pins and initialize the registers */
void USART_0_initialization(void)
{

	//PORTMUX.USARTROUTEA = PORTMUX_USART10_bm

	// Set pin direction to input
	PC1_set_dir(PORT_DIR_IN);

	PC1_set_pull_mode(
	    // <y> Pull configuration
	    // <id> pad_pull_config
	    // <PORT_PULL_OFF"> Off
	    // <PORT_PULL_UP"> Pull-up
	    PORT_PULL_OFF);

	// Set pin direction to output
	PC0_set_dir(PORT_DIR_OUT);

	PC0_set_level(
	    // <y> Initial level
	    // <id> pad_initial_level
	    // <false"> Low
	    // <true"> High
	    true);

	USART_0_init();
}

/* configure the pins and initialize the registers */
void SPI_0_initialization(void)
{

	// Set pin direction to input
	CONF_WIFI_M2M_SPI_MISO_PIN_set_dir(PORT_DIR_IN);

	CONF_WIFI_M2M_SPI_MISO_PIN_set_pull_mode(
	    // <y> Pull configuration
	    // <id> pad_pull_config
	    // <PORT_PULL_OFF"> Off
	    // <PORT_PULL_UP"> Pull-up
	    PORT_PULL_OFF);

	// Set pin direction to output
	CONF_WIFI_M2M_SPI_MOSI_PIN_set_dir(PORT_DIR_OUT);

	CONF_WIFI_M2M_SPI_MOSI_PIN_set_level(
	    // <y> Initial level
	    // <id> pad_initial_level
	    // <false"> Low
	    // <true"> High
	    false);

	// Set pin direction to output
	CONF_WIFI_M2M_SPI_SCK_PIN_set_dir(PORT_DIR_OUT);

	CONF_WIFI_M2M_SPI_SCK_PIN_set_level(
	    // <y> Initial level
	    // <id> pad_initial_level
	    // <false"> Low
	    // <true"> High
	    false);

	SPI_0_init();
}

void ADC_0_initialization(void)
{

	// Disable digital input buffer
	PD6_set_isc(PORT_ISC_INPUT_DISABLE_gc);
	// Disable pull-up resistor
	PD6_set_pull_mode(PORT_PULL_OFF);

	ADC_0_init();
}

/**
 * \brief System initialization
 */
void system_init()
{
	mcu_init();
//	ADC_0_initialization();


	CLKCTRL_init();

//	scheduler_timeout_init();

	USART_0_initialization();
	//return;
	/* PORT setting on PA2 */

	// Set pin direction to output
	CONF_WIFI_M2M_RESET_PIN_set_dir(PORT_DIR_OUT);

	CONF_WIFI_M2M_RESET_PIN_set_level(
	    // <y> Initial level
	    // <id> pad_initial_level
	    // <false"> Low
	    // <true"> High
	    false);

	/* PORT setting on PA3 */

	// Set pin direction to output
	CONF_WIFI_M2M_WAKE_PIN_set_dir(PORT_DIR_OUT);

	CONF_WIFI_M2M_WAKE_PIN_set_level(
	    // <y> Initial level
	    // <id> pad_initial_level
	    // <false"> Low
	    // <true"> High
	    false);

	/* PORT setting on PA7 */

	// Set pin direction to output
	CONF_WIFI_M2M_SPI_CS_PIN_set_dir(PORT_DIR_OUT);

	CONF_WIFI_M2M_SPI_CS_PIN_set_level(
	    // <y> Initial level
	    // <id> pad_initial_level
	    // <false"> Low
	    // <true"> High
	    true);

	/* PORT setting on PB2 */

	// Set pin direction to input
	SW0_set_dir(PORT_DIR_IN);

	SW0_set_pull_mode(
	    // <y> Pull configuration
	    // <id> pad_pull_config
	    // <PORT_PULL_OFF"> Off
	    // <PORT_PULL_UP"> Pull-up
	    PORT_PULL_UP);

	/* PORT setting on PB5 */

	// Set pin direction to output
	LED0_set_dir(PORT_DIR_OUT);

	LED0_set_level(
	    // <y> Initial level
	    // <id> pad_initial_level
	    // <false"> Low
	    // <true"> High
	    false);

	/* PORT setting on PC6 */

	CONF_WIFI_M2M_INT_PIN_set_dir(
	    // <y> Pin direction
	    // <id> pad_dir
	    // <PORT_DIR_OFF"> Off
	    // <PORT_DIR_IN"> In
	    // <PORT_DIR_OUT"> Out
	    PORT_DIR_IN);

	CONF_WIFI_M2M_INT_PIN_set_level(
	    // <y> Initial level
	    // <id> pad_initial_level
	    // <false"> Low
	    // <true"> High
	    false);

	CONF_WIFI_M2M_INT_PIN_set_pull_mode(
	    // <y> Pull configuration
	    // <id> pad_pull_config
	    // <PORT_PULL_OFF"> Off
	    // <PORT_PULL_UP"> Pull-up
	    PORT_PULL_UP);

	CONF_WIFI_M2M_INT_PIN_set_inverted(
	    // <y> Invert I/O on pin
	    // <id> pad_invert
	    // <false"> Not inverted
	    // <true"> Inverted
	    false);

	CONF_WIFI_M2M_INT_PIN_set_isc(
	    // <y> Pin Input/Sense Configuration
	    // <id> pad_isc
	    // <PORT_ISC_INTDISABLE_gc"> Interrupt disabled but input buffer enabled
	    // <PORT_ISC_BOTHEDGES_gc"> Sense Both Edges
	    // <PORT_ISC_RISING_gc"> Sense Rising Edge
	    // <PORT_ISC_FALLING_gc"> Sense Falling Edge
	    // <PORT_ISC_INPUT_DISABLE_gc"> Digital Input Buffer disabled
	    // <PORT_ISC_LEVEL_gc"> Sense low Level
	    PORT_ISC_FALLING_gc);

	/* PORT setting on PC7 */

	// Set pin direction to output
	CONF_WIFI_M2M_CHIP_ENABLE_PIN_set_dir(PORT_DIR_OUT);

	CONF_WIFI_M2M_CHIP_ENABLE_PIN_set_level(
	    // <y> Initial level
	    // <id> pad_initial_level
	    // <false"> Low
	    // <true"> High
	    false);

	CLKCTRL_init();

	scheduler_timeout_init();

	USART_0_initialization();

	SPI_0_initialization();

	CPUINT_init();

	SLPCTRL_init();

	BOD_init();
}
