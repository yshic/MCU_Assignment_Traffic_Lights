#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "main.h"

#define NORMAL_STATE SET
#define PRESSED_STATE RESET
#define NUM_BUTTONS 3

extern int BT_flag[NUM_BUTTONS];

int isBTPressed(int index);
void subKeyProcess(int index);
void getKeyInput();


#endif /* INC_BUTTON_H_ */
