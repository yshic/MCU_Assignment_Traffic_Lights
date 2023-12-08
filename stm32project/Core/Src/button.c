#include "main.h"
#include "button.h"

uint16_t btArr[NUM_BUTTONS] = {A1_BT1_Pin, A2_BT2_Pin, A3_BT3_Pin, A0_PD_BT_Pin};
GPIO_TypeDef *btPort[NUM_BUTTONS] = {A1_BT1_GPIO_Port, A2_BT2_GPIO_Port, A3_BT3_GPIO_Port, A0_PD_BT_GPIO_Port};

int KeyReg0[NUM_BUTTONS] = {NORMAL_STATE};
int KeyReg1[NUM_BUTTONS] = {NORMAL_STATE};
int KeyReg2[NUM_BUTTONS] = {NORMAL_STATE};
int KeyReg3[NUM_BUTTONS] = {NORMAL_STATE};

int TimeOutForKeyPress[NUM_BUTTONS] = {200};
int BT_flag[NUM_BUTTONS] = {0};
int BT_hold_flag[NUM_BUTTONS] = {0};


void getKeyInput(){
	for (int i = 0; i < NUM_BUTTONS; i++){
		KeyReg2[i] = KeyReg1[i];
		KeyReg1[i] = KeyReg0[i];
		//Add your button here
		KeyReg0[i] = HAL_GPIO_ReadPin(btPort[i], btArr[i]);

		if ((KeyReg1[i] == KeyReg0[i]) && (KeyReg1[i] == KeyReg2[i])){
			if (KeyReg2[i] != KeyReg3[i]){
				KeyReg3[i] = KeyReg2[i];
				if (KeyReg3[i] == PRESSED_STATE){
						TimeOutForKeyPress[i] = 200;
						BT_flag[i] = 1;				}
			}else{
				TimeOutForKeyPress[i]--;
				if (TimeOutForKeyPress[i] == 0){
					TimeOutForKeyPress[i] = 200;
					if(KeyReg0[i] == PRESSED_STATE){
						BT_hold_flag[i] = 1;
					}
				}
			}
		}
	}
}


int isBTPressed(int index){
	if(BT_flag[index] == 1){
		BT_flag[index] = 0;
		return 1;
	}
	return 0;
}

int isBTHold(int index){
	if(BT_hold_flag[index] == 1){
		BT_hold_flag[index] = 0;
		return 1;
	}
	return 0;
}
