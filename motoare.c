#include "motoare.h"
#include <avr/io.h>

#define WHEEL_PWM_PERIOD 0xFA
#define LEFT_WHEEL_DUTY 0xC8
#define RIGHT_WHEEL_DUTY 0xC8



void motor_dir_port_init(){
	
	/* left wheel */
	PORTE.DIR |= PIN3_bm;
	PORTE.DIR |= PIN2_bm;
	
	PORTE.OUT &= ~PIN2_bm;
	PORTE.OUT |= PIN3_bm;
	
	/* right wheel */
	PORTF.DIR |= PIN6_bm;
	PORTF.DIR |= PIN4_bm;
	
	PORTF.OUT &= ~PIN6_bm;
	PORTF.OUT |= PIN4_bm;
}

void LEFT_WHEEL_TCB3_PWM_init (void)
{
	PORTB_DIR |= PIN5_bm;
	PORTB_OUT |= PIN5_bm;
	/* Load CCMP register with the period and duty cycle of the PWM */
	//TCB3.CCMP = TCB_CMP_EXAMPLE_VALUE;
	TCB3.CCMPL = WHEEL_PWM_PERIOD; // period of pwm
	TCB3.CCMPH = LEFT_WHEEL_DUTY; // duty cycle
	/* Enable TCB3 and Divide CLK_PER by 2 */
	TCB3.CTRLA |= TCB_ENABLE_bm;
	

	/* Enable Pin Output and configure TCB in 8-bit PWM mode */
	TCB3.CTRLB |= TCB_CCMPEN_bm;
	TCB3.CTRLB |= TCB_CNTMODE_PWM8_gc;
}

void RIGHT_WHEEL_TCB1_PWM_init(void){
		PORTF.DIR |= PIN5_bm;
		PORTF.OUT |= PIN5_bm;
		/* Load CCMP register with the period and duty cycle of the PWM */

		TCB1.CCMPL = WHEEL_PWM_PERIOD; // period of pwm
		TCB1.CCMPH = RIGHT_WHEEL_DUTY; // duty cycle
		/* Enable TCB3 and Divide CLK_PER by 2 */
		TCB1.CTRLA |= TCB_ENABLE_bm;
		
		/* Enable Pin Output and configure TCB in 8-bit PWM mode */
		TCB1.CTRLB |= TCB_CCMPEN_bm;
		TCB1.CTRLB |= TCB_CNTMODE_PWM8_gc;
		PORTMUX.TCBROUTEA |= PIN1_bm;
	
}

void motor_start_left_wheel(){
	
	TCB3.CTRLA &= ~PIN0_bm;  // disable TCB3
	TCB3.CCMPL = 0xFA;
	TCB3.CCMPH = 0xC8; // change duty cycle
	TCB3.CNT = 0x00;
	TCB3.CTRLA |=  TCB_ENABLE_bm; // re-enable TCB3;
}


void motor_stop_left_wheel(){
	
	TCB3.CTRLA &= ~PIN0_bm;  // disable TCB3
	TCB3.CCMPL = 0xFA;
	TCB3.CCMPH = 0x00; // change duty cycle
	TCB3.CNT = 0x00;
	TCB3.CTRLA |= TCB_ENABLE_bm; // re-enable TCB3;
}


void motor_start_right_wheel(){
	
	TCB1.CTRLA &= ~PIN0_bm;  // disable TCB3
	TCB1.CCMPL = 0xFA;
	TCB1.CCMPH = 0xC8; // change duty cycle
	TCB1.CNT = 0x00;
	TCB1.CTRLA |= TCB_ENABLE_bm; // re-enable TCB3;
}


void motor_stop_right_wheel(){
	
	TCB1.CTRLA &= ~PIN0_bm;  // disable TCB3
	TCB1.CCMPL = 0xFA;
	TCB1.CCMPH = 0x00; // change duty cycle
	TCB1.CNT = 0x00;
	TCB1.CTRLA |= TCB_ENABLE_bm; // re-enable TCB3;
}

void motor_reverse_left_wheel(){
	
	PORTE.OUT ^= PIN3_bm;
	PORTE.OUT ^= PIN2_bm;
}

void motor_reverse_right_wheel(){
	
	PORTF.OUT ^= PIN5_bm;
	PORTF.OUT ^= PIN4_bm;
}