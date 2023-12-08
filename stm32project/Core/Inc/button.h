#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#define NORMAL_STATE SET
#define PRESSED_STATE RESET
#define NUM_BUTTONS 4

extern int BT_flag[NUM_BUTTONS];
extern int BT_hold_flag[NUM_BUTTONS];

void getKeyInput();
int isBTPressed(int index);
int isBTHold(int index);


#endif /* INC_BUTTON_H_ */
