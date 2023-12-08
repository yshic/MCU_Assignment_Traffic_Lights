#ifndef INC_BUZZER_H_
#define INC_BUZZER_H_

#include "main.h"

extern int green_ped[9];
extern int buzzer_state;

void buzzer_init(TIM_TypeDef *tim);
void buzzer_sound(TIM_HandleTypeDef htim ,int volume);
void buzzer_run();
void buzzer_set(int value);

#endif /* INC_BUZZER_H_ */
