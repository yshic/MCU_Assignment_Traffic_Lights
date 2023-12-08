#include "buzzer.h"
#include "main.h"
#include "global.h"
#include "software_timer.h"

uint8_t idx = 0;
uint32_t tempPSC = 0;
int buzzer_state = 0;

int ped_green[8] = {NOTE_E7, NOTE_C7, NOTE_E7, NOTE_C7, NOTE_E7, NOTE_C7, NOTE_E7, NOTE_C7};

//Used timer: timer 4

void buzzer_init(TIM_TypeDef *tim){
	tempPSC = tim->PSC;
	setTimer(10, 4);
}

void buzzer_sound(TIM_HandleTypeDef htim ,int volume){
	TIM_CCxChannelCmd(TIM3, TIM_CHANNEL_1, TIM_CCx_ENABLE);
	__HAL_TIM_SET_COMPARE(&htim,TIM_CHANNEL_1,volume);
	TIM3->PSC = 64000/ped_green[idx%8];
	idx++;
}

void buzzer_run(){
	if(buzzer_state == 0){
		TIM_CCxChannelCmd(TIM3, TIM_CHANNEL_1, TIM_CCx_DISABLE);
		idx = 0;
		TIM3->PSC = tempPSC;
	}
	if(timer_flag[4] == 1){
		if(buzzer_state == 2){
			buzzer_sound(htim3, 20);
			setTimer(100, 4);
		}
		if(buzzer_state == 1){
			buzzer_sound(htim3, 20);
			setTimer(250, 4);
		}
	}
}


void buzzer_set(int value){
	switch(value){
	case 0:
		buzzer_state = 0;
		break;
	case 1:
		buzzer_state = 1;
		break;
	case 2:
		buzzer_state = 2;
		break;
	default:
		buzzer_state = 0;
		break;
	}
}
