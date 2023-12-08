#include "main.h"
#include "fsm_tuning.h"
#include "global.h"
#include "fsm_automatic.h"
#include "software_timer.h"
#include "button.h"
#include <stdio.h>

int redTemp = 1;
int greenTemp = 1;
int yellowTemp = 1;

void ledBalance(){
	if(red == (green + yellow)) return;
	else if(red > (green + yellow)){
		red = green + yellow;
	}
	else{
		yellow = red - green;
	}
}

//Used timers: timer[3]: led blinking
void fsm_tuning_run(){
	switch(status){
	case TUNING_INIT:
		status = TUNING_RED;
		setTimer(250, 3);		//timer for led blinking
		HAL_UART_Transmit(&huart2, (void *)message, sprintf(message, "!TUNING#\r\n"), 1000);
		int buffer1 = redTemp / 10;
		int buffer2 = redTemp % 10;
		HAL_UART_Transmit(&huart2, (void *)message, sprintf(message, "!7SEG:%d%d#TUNING_RED\r\n", buffer1, buffer2), 1000);
		break;
	case TUNING_RED:
		if(timer_flag[3] == 1){
			toggleRedLED();
			setTimer(250, 3);
		}
		if(isBTPressed(0) == 1){
			status = TUNING_YELLOW;
			redTemp = 1;
			clearTrafficLights();
			int buffer1 = yellowTemp / 10;
			int buffer2 = yellowTemp % 10;
			HAL_UART_Transmit(&huart2, (void *)message, sprintf(message, "!7SEG:%d%d#TUNING_YELLOW\r\n", buffer1, buffer2), 1000);
		}
		if(isBTHold(0) == 1){
			status = INIT;
			redTemp = 1; greenTemp = 1; yellowTemp = 1;
			ledBalance();
			clearTrafficLights();
		}
		if(isBTPressed(1) == 1){
			redTemp++;
			if(redTemp > 99) redTemp = 1;
			int buffer1 = redTemp / 10;
			int buffer2 = redTemp % 10;
			HAL_UART_Transmit(&huart2, (void *)message, sprintf(message, "!7SEG:%d%d#TUNING_RED(+1)\r\n", buffer1, buffer2), 1000);
		}
		if(isBTHold(1) == 1){
			redTemp += 10;
			if(redTemp > 99) redTemp = 1;
			int buffer1 = redTemp / 10;
			int buffer2 = redTemp % 10;
			HAL_UART_Transmit(&huart2, (void *)message, sprintf(message, "!7SEG:%d%d#TUNING_RED(+10)\r\n", buffer1, buffer2), 1000);
		}
		if(isBTPressed(2) == 1){
			red = redTemp;
			int buffer1 = red / 10;
			int buffer2 = red % 10;
			HAL_UART_Transmit(&huart2, (void *)message, sprintf(message, "!7SEG:%d%d#RED_SET\r\n", buffer1, buffer2), 1000);
		}
		break;
	case TUNING_GREEN:
		if(timer_flag[3] == 1){
			toggleGreenLED();
			setTimer(250, 3);
		}
		if(isBTPressed(0) == 1){
			ledBalance();
			status = TUNING_RED;
			greenTemp = 1;
			clearTrafficLights();
			int buffer1 = redTemp / 10;
			int buffer2 = redTemp % 10;
			HAL_UART_Transmit(&huart2, (void *)message, sprintf(message, "!7SEG:%d%d#TUNING_RED\r\n", buffer1, buffer2), 1000);
		}
		if(isBTHold(0) == 1){
			status = INIT;
			redTemp = 1; greenTemp = 1; yellowTemp = 1;
			ledBalance();
			clearTrafficLights();
		}
		if(isBTPressed(1) == 1){
			greenTemp++;
			if(greenTemp > 99) greenTemp = 1;
			int buffer1 = greenTemp / 10;
			int buffer2 = greenTemp % 10;
			HAL_UART_Transmit(&huart2, (void *)message, sprintf(message, "!7SEG:%d%d#TUNING_GREEN(+1)\r\n", buffer1, buffer2), 1000);
		}
		if(isBTHold(1) == 1){
			greenTemp += 10;
			if(greenTemp > 99) greenTemp = 1;
			int buffer1 = greenTemp / 10;
			int buffer2 = greenTemp % 10;
			HAL_UART_Transmit(&huart2, (void *)message, sprintf(message, "!7SEG:%d%d#TUNING_GREEN(+10)\r\n", buffer1, buffer2), 1000);
		}
		if(isBTPressed(2) == 1){
			green = greenTemp;
			int buffer1 = green / 10;
			int buffer2 = green % 10;
			HAL_UART_Transmit(&huart2, (void *)message, sprintf(message, "!7SEG:%d%d#GREEN_SET\r\n", buffer1, buffer2), 1000);
		}
		break;
	case TUNING_YELLOW:
		if(timer_flag[3] == 1){
			toggleYellowLED();
			setTimer(250, 3);
		}
		if(isBTPressed(0) == 1){
			status = TUNING_GREEN;
			yellowTemp = 1;
			clearTrafficLights();
			int buffer1 = greenTemp / 10;
			int buffer2 = greenTemp % 10;
			HAL_UART_Transmit(&huart2, (void *)message, sprintf(message, "!7SEG:%d%d#TUNING_GREEN\r\n", buffer1, buffer2), 1000);
		}
		if(isBTHold(0) == 1){
			status = INIT;
			redTemp = 1; greenTemp = 1; yellowTemp = 1;
			ledBalance();
			clearTrafficLights();
		}
		if(isBTPressed(1) == 1){
			yellowTemp++;
			if(yellowTemp > 99) yellowTemp = 1;
			int buffer1 = yellowTemp / 10;
			int buffer2 = yellowTemp % 10;
			HAL_UART_Transmit(&huart2, (void *)message, sprintf(message, "!7SEG:%d%d#TUNING_YELLOW(+1)\r\n", buffer1, buffer2), 1000);
		}
		if(isBTHold(1) == 1){
			yellowTemp += 10;
			if(yellowTemp > 99) yellowTemp = 1;
			int buffer1 = yellowTemp / 10;
			int buffer2 = yellowTemp % 10;
			HAL_UART_Transmit(&huart2, (void *)message, sprintf(message, "!7SEG:%d%d#TUNING_YELLOW(+10)\r\n", buffer1, buffer2), 1000);
		}
		if(isBTPressed(2) == 1){
			yellow = yellowTemp;
			int buffer1 = yellow / 10;
			int buffer2 = yellow % 10;
			HAL_UART_Transmit(&huart2, (void *)message, sprintf(message, "!7SEG:%d%d#YELLOW_SET\r\n", buffer1, buffer2), 1000);
		}
		break;
	default:
		break;
	}
}

