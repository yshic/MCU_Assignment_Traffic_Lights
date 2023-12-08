#include "fsm_manual.h"
#include "main.h"
#include <stdio.h>
#include "global.h"
#include "software_timer.h"
#include "button.h"
#include "buzzer.h"

// Used timers: timer[2]: Ped timeout(5000)

void fsm_manual_run(){
	switch(status){
	case MANUAL_INIT:
		status = MANUAL_RED;
		buzzer_set(0);
		HAL_UART_Transmit(&huart2, (void *)message, sprintf(message, "!MANUAL#\r\n"), 1000);
	break;
	case MANUAL_RED:
		controlTrafficLights(RED, GREEN);
		if(timer_flag[2] == 1 && isPed == 1){
			isPed = 0;
			controlPedLights(OFF);
			HAL_UART_Transmit(&huart2, (void *)message, sprintf(message, "!PEDESTRIAN_OFF#\r\n"), 1000);
		}
		if(isBTPressed(0) == 1){
			status = TUNING_INIT;
			if(isPed == 1){
				isPed = 0;
				controlPedLights(OFF);
				HAL_UART_Transmit(&huart2, (void *)message, sprintf(message, "!PEDESTRIAN_OFF#\r\n"), 1000);
			}
		}
		if(isBTPressed(1) == 1){
			status = MANUAL_RED1_YELLOW2;
		}
		if(isBTPressed(3) == 1){
			isPed = 1;
			setTimer(PEDESTRIAN_TIMER, 2);
			HAL_UART_Transmit(&huart2, (void *)message, sprintf(message, "!PEDESTRIAN_GREEN#\r\n"), 1000);
		}
		if(isPed == 1){
			controlPedLights(GREEN);
		}
		if(isPed == 0){
			controlPedLights(OFF);
		}
		break;
	case MANUAL_GREEN:
		controlTrafficLights(GREEN, RED);
		if(timer_flag[2] == 1 && isPed == 1){
			isPed = 0;
			controlPedLights(OFF);
			HAL_UART_Transmit(&huart2, (void *)message, sprintf(message, "!PEDESTRIAN_OFF#\r\n"), 1000);
		}
		if(isBTPressed(0) == 1){
			status = TUNING_INIT;
			if(isPed == 1){
				isPed = 0;
				controlPedLights(OFF);
				HAL_UART_Transmit(&huart2, (void *)message, sprintf(message, "!PEDESTRIAN_OFF#\r\n"), 1000);
			}
		}
		if(isBTPressed(1) == 1){
			status = MANUAL_YELLOW;
		}
		if(isBTPressed(3) == 1){
			isPed = 1;
			setTimer(PEDESTRIAN_TIMER, 2);
			HAL_UART_Transmit(&huart2, (void *)message, sprintf(message, "!PEDESTRIAN_RED#\r\n"), 1000);
		}
		if(isPed == 1){
			controlPedLights(RED);
		}
		if(isPed == 0){
			controlPedLights(OFF);
		}
		break;
	case MANUAL_YELLOW:
		controlTrafficLights(YELLOW, RED);
		if(timer_flag[2] == 1){
			isPed = 0;
			controlPedLights(OFF);
			HAL_UART_Transmit(&huart2, (void *)message, sprintf(message, "!PEDESTRIAN_OFF#\r\n"), 1000);
		}
		if(isBTPressed(0) == 1){
			status = TUNING_INIT;
			if(isPed == 1){
				isPed = 0;
				controlPedLights(OFF);
				HAL_UART_Transmit(&huart2, (void *)message, sprintf(message, "!PEDESTRIAN_OFF#\r\n"), 1000);
			}
		}
		if(isBTPressed(1) == 1){
			status = MANUAL_RED;
		}
		if(isBTPressed(3) == 1){
			isPed = 1;
			setTimer(PEDESTRIAN_TIMER, 2);
			HAL_UART_Transmit(&huart2, (void *)message, sprintf(message, "!PEDESTRIAN_RED#\r\n"), 1000);
		}
		if(isPed == 1){
			controlPedLights(RED);
		}
		if(isPed == 0){
			controlPedLights(OFF);
		}
		break;
	case MANUAL_RED1_YELLOW2:
		controlTrafficLights(RED, YELLOW);
		if(timer_flag[2] == 1 && isPed == 1){
			isPed = 0;
			controlPedLights(OFF);
			HAL_UART_Transmit(&huart2, (void *)message, sprintf(message, "!PEDESTRIAN_OFF#\r\n"), 1000);
		}
		if(isBTPressed(0) == 1){
			status = TUNING_INIT;
			if(isPed == 1){
				isPed = 0;
				controlPedLights(OFF);
				HAL_UART_Transmit(&huart2, (void *)message, sprintf(message, "!PEDESTRIAN_OFF#\r\n"), 1000);
			}
		}
		if(isBTPressed(1) == 1){
			status = MANUAL_GREEN;
		}
		if(isBTPressed(3) == 1){
			isPed = 1;
			setTimer(PEDESTRIAN_TIMER, 2);
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
