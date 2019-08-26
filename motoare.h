#include <avr/io.h>


#ifndef	motoare_h
#define motoare_h

void motor_dir_port_init();
void LEFT_WHEEL_TCB3_PWM_init (void);
void RIGHT_WHEEL_TCB1_PWM_init(void);
void motor_start_left_wheel();
void motor_stop_left_wheel();
void motor_reverse_left_wheel();
void motor_start_right_wheel();
void motor_stop_right_wheel();
void motor_reverse_right_wheel();


#endif /* INCFILE1_H_ */