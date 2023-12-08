#include "fsm_automatic.h"
#include "main.h"
#include "global.h"
#include "software_timer.h"
#include "button.h"
#include "buzzer.h"
#include <stdio.h>

int counter1 = 0;
int counter2 = 0;
int counter1_buffer1;
int counter1_buffer2;
int counter2_buffer1;
int counter2_buffer2;

// Used timers: timer[0]: counter decrease (1000)
//				timer[1]: ped timeout (5000)
void fsm_automatic_run(){
	switch(status){
	case INIT:
		clearTrafficLights();
		status = AUTO_RED;
		setTimer(1000, 0);						//timer for counters
		counter1 = red;
		counter2 = green;
		HAL_UART_Transmit(&huart2, (void *)message, sprintf(message, "!AUTOMATIC#\r\n"), 1000);
		HAL_UART_Transmit(&huart2, (void *)message, sprintf(message, "!7SEG:%d||%d#\r\n",counter1, counter2), 1000);
		break;
	case AUTO_RED:
		controlTrafficLights(RED, GREEN);
		if(timer_flag[0] == 1){
			counter1--;
			counter2--;
			if(counter2 == 0){
				status = AUTO_RED1_YELLOW2;
				if(isPed == 1){
					buzzer_set(2);
				}
				counter2 = yellow;
			}
			counter1_buffer1 = counter1 / 10;
			counter1_buffer2 = counter1 % 10;
			counter2_buffer1 = counter2 / 10;
			counter2_buffer2 = counter2 % 10;
			HAL_UART_Transmit(&huart2, (void *)message, sprintf(message, "!7SEG:%d%d||%d%d#\r\n",
								counter1_buffer1, counter1_buffer2, counter2_buffer1, counter2_buffer2), 1000);
			setTimer(1000, 0);
		}
		if(timer_flag[1] == 1){ //ped timeout
			if(isPed == 1){
				isPed = 0;
				buzzer_set(0);
				controlPedLights(OFF);
				HAL_UART_Transmit(&huart2, (void *)message, sprintf(message, "!PEDESTRIAN_OFF#\r\n"), 1000);
			}
		}
		if(isBTPressed(0) == 1){
			status = MANUAL_INIT;
			clearTrafficLights();
			if(isPed == 1){
				isPed = 0;
				buzzer_set(0);
				controlPedLights(OFF);
				HAL_UART_Transmit(&huart2, (void *)message, sprintf(message, "!PEDESTRIAN_OFF#\r\n"), 1000);
			}
		}
		if(isBTPressed(3) == 1){
			isPed = 1;
			setTimer(PEDESTRIAN_TIMER, 1);
			HAL_UART_Transmit(&huart2, (void *)message, sprintf(message, "!PEDESTRIAN_GREEN#\r\n"), 1000);
			buzzer_set(1);
		}
		if(isPed == 1){
			controlPedLights(GREEN);
		}
		if(isPed == 0){
			controlPedLights(OFF);
		}
		break;
	case AUTO_GREEN:
		controlTrafficLights(GREEN, RED);
		if(timer_flag[0] == 1){
			counter1--;
			counter2--;
			if(counter1 == 0){
				status = AUTO_YELLOW;
				counter1 = yellow;
			}
			counter1_buffer1 = counter1 / 10;
			counter1_buffer2 = counter1 % 10;
			counter2_buffer1 = counter2 / 10;
			counter2_buffer2 = counter2 % 10;
			HAL_UART_Transmit(&huart2, (void *)message, sprintf(message, "!7SEG:%d%d||%d%d#\r\n",
													counter1_buffer1, counter1_buffer2, counter2_buffer1, counter2_buffer2), 1000);
			setTimer(1000, 0);
		}
		if(timer_flag[1] == 1){
			if(isPed == 1){
				isPed = 0;
				controlPedLights(OFF);
				HAL_UART_Transmit(&huart2, (void *)message, sprintf(message, "!PEDESTRIAN_OFF#\r\n"), 1000);
			}
		}
		if(isBTPressed(0) == 1){
			status = MANUAL_INIT;
			clearTrafficLights();
			if(isPed == 1){
				isPed = 0;
				controlPedLights(OFF);
				HAL_UART_Transmit(&huart2, (void *)message, sprintf(message, "!PEDESTRIAN_OFF#\r\n"), 1000);
			}
		}
		if(isBTPressed(3) == 1){
			isPed = 1;
			setTimer(PEDESTRIAN_TIMER, 1);
			HAL_UART_Transmit(&huart2, (void *)message, sprintf(message, "!PEDESTRIAN_RED#\r\n"), 1000);
		}
		if(isPed == 1){
			controlPedLights(RED);
		}
		if(isPed == 0){
			controlPedLights(OFF);
		}
		break;
	case AUTO_YELLOW:
		controlTrafficLights(YELLOW, RED);
		if(timer_flag[0] == 1){
			counter1--;
			counter2--;
			if(counter1 <= 0){
				status = AUTO_RED;
				counter1 = red;
				counter2 = green;
				if(isPed == 1){
					buzzer_set(1);
				}
			}
			counter1_buffer1 = counter1 / 10;
			counter1_buffer2 = counter1 % 10;
			counter2_buffer1 = counter2 / 10;
			counter2_buffer2 = counter2 % 10;
			HAL_UART_Transmit(&huart2, (void *)message, sprintf(message, "!7SEG:%d%d||%d%d#\r\n",
																counter1_buffer1, counter1_buffer2, counter2_buffer1, counter2_buffer2), 1000);
			setTimer(1000, 0);
		}
		if(timer_flag[1] == 1){
			if(isPed == 1){
				isPed = 0;
				controlPedLights(OFF);
				HAL_UART_Transmit(&huart2, (void *)message, sprintf(message, "!PEDESTRIAN_OFF#\r\n"), 1000);
			}
		}
		if(isBTPressed(0) == 1){
			status = MANUAL_INIT;
			clearTrafficLights();
			if(isPed == 1){
				isPed = 0;
				controlPedLights(OFF);
				HAL_UART_Transmit(&huart2, (void *)message, sprintf(message, "!PEDESTRIAN_OFF#\r\n"), 1000);
			}
		}
		if(isBTPressed(3) == 1){
			isPed = 1;
			setTimer(PEDESTRIAN_TIMER, 1);
			HAL_UART_Transmit(&huart2, (void *)message, sprintf(message, "!PEDESTRIAN_RED#\r\n"), 1000);
		}
		if(isPed == 1){
			controlPedLights(RED);
		}
		if(isPed == 0){
			controlPedLights(OFF);
		}
		break;
	case AUTO_RED1_YELLOW2:
		controlTrafficLights(RED, YELLOW);
		if(timer_flag[0] == 1){
			counter1--;
			counter2--;
			if(counter2 == 0){
				counter1 = green;
				counter2 = red;
				status = AUTO_GREEN;
				buzzer_set(0);
			}
			counter1_buffer1 = counter1 / 10;
			counter1_buffer2 = counter1 % 10;
			counter2_buffer1 = counter2 / 10;
			counter2_buffer2 = counter2 % 10;
			HAL_UART_Transmit(&huart2, (void *)message, sprintf(message, "!7SEG:%d%d||%d%d#\r\n",
																counter1_buffer1, counter1_buffer2, counter2_buffer1, counter2_buffer2), 1000);

			setTimer(1000, 0);
		}
		if(timer_flag[1] == 1){
			if(isPed == 1){
				isPed = 0;
				buzzer_set(0);
				controlPedLights(OFF);
				HAL_UART_Transmit(&huart2, (void *)message, sprintf(message, "!PEDESTRIAN_OFF#\r\n"), 1000);
			}
		}
		if(isBTPressed(0) == 1){
			status = MANUAL_INIT;
			clearTrafficLights();
			if(isPed == 1){
				isPed = 0;
				buzzer_set(0);
				controlPedLights(OFF);
				HAL_UART_Transmit(&huart2, (void *)message, sprintf(message, "!PEDESTRIAN_OFF#\r\n"), 1000);
			}
		}
		if(isBTPressed(3) == 1){
			isPed = 1;
			setTimer(PEDESTRIAN_TIMER, 1);
			HAL_UART_Transmit(&huart2, (void *)message, sprintf(message, "!PEDESTRIAN_YELLOW#\r\n"), 1000);
		}
		if(isPed == 1){
			controlPedLights(YELLOW);
		}
		if(isPed == 0){
			controlPedLights(OFF);
		}
		break;
	default:
		break;
	}
}

