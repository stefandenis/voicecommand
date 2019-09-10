// TODO : optimize level to O1
#define F_CPU 8000000
#include <util/delay.h>

#include <atmel_start.h>
#include <avr/io.h>
 #include <avr/interrupt.h>
 #include <stdbool.h>
 
 #include <string.h>
 #include "winc_init.h"
 #include <stdio.h>
 #include "winc/driver/source/nmasic.h"
 #include "winc/socket/include/socket.h"
 #include "winc/socket/include/m2m_socket_host_if.h"
 #include "motoare.h"

 #include "cloud/cloud.h"
 
 
 #define PUBLISH_INTERVAL 1000
 
 
 
 int usart_putchar_printf(char var, FILE *stream);
 
 static FILE mystdout = FDEV_SETUP_STREAM(usart_putchar_printf, NULL, _FDEV_SETUP_WRITE);


int usart_putchar_printf(char var, FILE *stream){
	
	USART_1_write(var);
}



// void get_command(char *str,tstrSocketRecvMsg *pCommand){
// 
// int i=0;
// for(i=0;i<sizeof(order);i++){
// 	order[i]=0x00;
// }
// i=0;
// while(*(pCommand->pu8Buffer+i) != 0x0D){
//  	
// 	*(str+i)=*(pCommand->pu8Buffer+i);
// 	i++;
// 	
// }

//}






	





absolutetime_t publishChar(void *payload)
{



	return PUBLISH_INTERVAL;
}



int main(void){
	
	
	// Redirect stream to Tera Term
	stdout = &mystdout;
// 	/* Initializes MCU, drivers and middleware */
	
	atmel_start_init();
 	motor_dir_port_init();
 	LEFT_WHEEL_TCB3_PWM_init();
	RIGHT_WHEEL_TCB1_PWM_init();
	ENABLE_INTERRUPTS();
		 
	CLOUD_setSendFunction(publishChar);
	
	CLOUD_startApp();




	
	
while (1) {
	
	CLOUD_runTask();
		
}














}




