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
/*
 void display7SEG(int num){
	// 0/RESET = ON, 1/SET = OFF
	switch(num){
	case 0:
		HAL_GPIO_WritePin(GPIOB, SEG_A_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, SEG_B_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, SEG_C_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, SEG_D_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, SEG_E_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, SEG_F_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, SEG_G_Pin, GPIO_PIN_SET);
		break;
	case 1:
		HAL_GPIO_WritePin(GPIOB, SEG_A_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB, SEG_B_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, SEG_C_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, SEG_D_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB, SEG_E_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB, SEG_F_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB, SEG_G_Pin, GPIO_PIN_SET);
		break;
	case 2:
		HAL_GPIO_WritePin(GPIOB, SEG_A_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, SEG_B_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, SEG_C_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB, SEG_D_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, SEG_E_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, SEG_F_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB, SEG_G_Pin, GPIO_PIN_RESET);
		break;
	case 3:
		HAL_GPIO_WritePin(GPIOB, SEG_A_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, SEG_B_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, SEG_C_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, SEG_D_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, SEG_E_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB, SEG_F_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB, SEG_G_Pin, GPIO_PIN_RESET);
		break;
	case 4:
		HAL_GPIO_WritePin(GPIOB, SEG_A_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB, SEG_B_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, SEG_C_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, SEG_D_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB, SEG_E_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB, SEG_F_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, SEG_G_Pin, GPIO_PIN_RESET);
		break;
	case 5:
		HAL_GPIO_WritePin(GPIOB, SEG_A_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, SEG_B_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB, SEG_C_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, SEG_D_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, SEG_E_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB, SEG_F_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, SEG_G_Pin, GPIO_PIN_RESET);
		break;
	case 6:
		HAL_GPIO_WritePin(GPIOB, SEG_A_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, SEG_B_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB, SEG_C_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, SEG_D_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, SEG_E_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, SEG_F_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, SEG_G_Pin, GPIO_PIN_RESET);
		break;
	case 7:
		HAL_GPIO_WritePin(GPIOB, SEG_A_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, SEG_B_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, SEG_C_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, SEG_D_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB, SEG_E_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB, SEG_F_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB, SEG_G_Pin, GPIO_PIN_SET);
		break;
	case 8:
		HAL_GPIO_WritePin(GPIOB, SEG_A_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, SEG_B_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, SEG_C_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, SEG_D_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, SEG_E_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, SEG_F_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, SEG_G_Pin, GPIO_PIN_RESET);
		break;
	case 9:
		HAL_GPIO_WritePin(GPIOB, SEG_A_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, SEG_B_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, SEG_C_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, SEG_D_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, SEG_E_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB, SEG_F_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, SEG_G_Pin, GPIO_PIN_RESET);
		break;
	default: //OFF
		HAL_GPIO_WritePin(GPIOB, SEG_A_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB, SEG_B_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB, SEG_C_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB, SEG_D_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB, SEG_E_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB, SEG_F_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB, SEG_G_Pin, GPIO_PIN_SET);
		break;
	}
}

void update7SEG(int index){
	switch(index){
	case 0:
		HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(EN1_GPIO_Port, EN2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(EN1_GPIO_Port, EN3_Pin, GPIO_PIN_SET);
		display7SEG(led_buffer[index]);
		break;
	case 1:
		HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(EN1_GPIO_Port, EN2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(EN1_GPIO_Port, EN3_Pin, GPIO_PIN_SET);
		display7SEG(led_buffer[index]);
		break;
	case 2:
		HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(EN1_GPIO_Port, EN2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(EN1_GPIO_Port, EN3_Pin, GPIO_PIN_SET);
		display7SEG(led_buffer[index]);
		break;
	case 3:
		HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(EN1_GPIO_Port, EN2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(EN1_GPIO_Port, EN3_Pin, GPIO_PIN_RESET);
		display7SEG(led_buffer[index]);
		break;
	default:
		break;
	}
}

void updateCounterBuffer(int counter1, int counter2){
	led_buffer[0] = counter1 / 10;
	led_buffer[1] = counter1 % 10;
	led_buffer[2] = counter2 / 10;
	led_buffer[3] = counter2 % 10;
}
*/


