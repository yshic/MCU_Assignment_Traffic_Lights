#include "global.h"

int red = 5;
int green = 3;
int yellow = 2;
int isPed;
char message[MAX_MESSAGE_LENGTH];
enum TRAFFIC_STATE status = INIT;

void controlTrafficLights(int color1, int color2){
//	index = 0 -> W-E Traffic light
//  index = 1 -> N-S Traffic light
	switch(color1){
	case RED:
		HAL_GPIO_WritePin(D2_TF1_LED1_GPIO_Port, D2_TF1_LED1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(D3_TF1_LED2_GPIO_Port, D3_TF1_LED2_Pin, GPIO_PIN_RESET);
		break;
	case GREEN:
		HAL_GPIO_WritePin(D2_TF1_LED1_GPIO_Port, D2_TF1_LED1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(D3_TF1_LED2_GPIO_Port, D3_TF1_LED2_Pin, GPIO_PIN_SET);
		break;
	case YELLOW:
		HAL_GPIO_WritePin(D2_TF1_LED1_GPIO_Port, D2_TF1_LED1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(D3_TF1_LED2_GPIO_Port, D3_TF1_LED2_Pin, GPIO_PIN_SET);
		break;
	default:
		HAL_GPIO_WritePin(D2_TF1_LED1_GPIO_Port, D2_TF1_LED1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(D3_TF1_LED2_GPIO_Port, D3_TF1_LED2_Pin, GPIO_PIN_RESET);
		break;
	}
	switch(color2){
	case RED:
		HAL_GPIO_WritePin(D4_TF2_LED1_GPIO_Port, D4_TF2_LED1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(D5_TF2_LED2_GPIO_Port, D5_TF2_LED2_Pin, GPIO_PIN_RESET);
		break;
	case GREEN: // GREEN
		HAL_GPIO_WritePin(D4_TF2_LED1_GPIO_Port, D4_TF2_LED1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(D5_TF2_LED2_GPIO_Port, D5_TF2_LED2_Pin, GPIO_PIN_SET);
		break;
	case YELLOW: // YELLOW
		HAL_GPIO_WritePin(D4_TF2_LED1_GPIO_Port, D4_TF2_LED1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(D5_TF2_LED2_GPIO_Port, D5_TF2_LED2_Pin, GPIO_PIN_SET);
		break;
	default:
		HAL_GPIO_WritePin(D4_TF2_LED1_GPIO_Port, D4_TF2_LED1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(D5_TF2_LED2_GPIO_Port, D5_TF2_LED2_Pin, GPIO_PIN_RESET);
		break;
	}
}

void controlPedLights(int color){
	switch(color){
	case RED: // RED
		HAL_GPIO_WritePin(D6_PDL_LED1_GPIO_Port, D6_PDL_LED1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(D7_PDL_LED2_GPIO_Port, D7_PDL_LED2_Pin, GPIO_PIN_RESET);
		break;
	case GREEN: // GREEN
		HAL_GPIO_WritePin(D6_PDL_LED1_GPIO_Port, D6_PDL_LED1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(D7_PDL_LED2_GPIO_Port, D7_PDL_LED2_Pin, GPIO_PIN_SET);
		break;
	case YELLOW: // YELLOW
		HAL_GPIO_WritePin(D6_PDL_LED1_GPIO_Port, D6_PDL_LED1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(D7_PDL_LED2_GPIO_Port, D7_PDL_LED2_Pin, GPIO_PIN_SET);
		break;
	case YELLOW_BLINK:
		HAL_GPIO_TogglePin(D6_PDL_LED1_GPIO_Port, D6_PDL_LED1_Pin);
		HAL_GPIO_TogglePin(D7_PDL_LED2_GPIO_Port, D7_PDL_LED2_Pin);
		break;
	case OFF: // OFF
		HAL_GPIO_WritePin(D6_PDL_LED1_GPIO_Port, D6_PDL_LED1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(D7_PDL_LED2_GPIO_Port, D7_PDL_LED2_Pin, GPIO_PIN_RESET);
		break;
	default:
		break;
	}
}

void clearTrafficLights(){
	//Main TL
	HAL_GPIO_WritePin(D2_TF1_LED1_GPIO_Port, D2_TF1_LED1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(D3_TF1_LED2_GPIO_Port, D3_TF1_LED2_Pin, GPIO_PIN_RESET);

	//Other TL
	HAL_GPIO_WritePin(D4_TF2_LED1_GPIO_Port, D4_TF2_LED1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(D5_TF2_LED2_GPIO_Port, D5_TF2_LED2_Pin, GPIO_PIN_RESET);
}

void toggleRedLED(){
	HAL_GPIO_WritePin(D3_TF1_LED2_GPIO_Port, D3_TF1_LED2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(D5_TF2_LED2_GPIO_Port, D5_TF2_LED2_Pin, GPIO_PIN_RESET);

	HAL_GPIO_TogglePin(D2_TF1_LED1_GPIO_Port, D2_TF1_LED1_Pin);
	HAL_GPIO_TogglePin(D4_TF2_LED1_GPIO_Port, D4_TF2_LED1_Pin);
}

void toggleGreenLED(){
	HAL_GPIO_WritePin(D2_TF1_LED1_GPIO_Port, D2_TF1_LED1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(D4_TF2_LED1_GPIO_Port, D4_TF2_LED1_Pin, GPIO_PIN_RESET);

	HAL_GPIO_TogglePin(D3_TF1_LED2_GPIO_Port, D3_TF1_LED2_Pin);
	HAL_GPIO_TogglePin(D5_TF2_LED2_GPIO_Port, D5_TF2_LED2_Pin);
}

void toggleYellowLED(){
		HAL_GPIO_TogglePin(D2_TF1_LED1_GPIO_Port, D2_TF1_LED1_Pin);
		HAL_GPIO_TogglePin(D3_TF1_LED2_GPIO_Port, D3_TF1_LED2_Pin);
		HAL_GPIO_TogglePin(D4_TF2_LED1_GPIO_Port, D4_TF2_LED1_Pin);
		HAL_GPIO_TogglePin(D5_TF2_LED2_GPIO_Port, D5_TF2_LED2_Pin);
}


