#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include "main.h"

#define RED 					100
#define GREEN					101
#define YELLOW					102
#define OFF						103
#define PEDESTRIAN_TIMER		8000

#define MAX_MESSAGE_LENGTH		50

enum TRAFFIC_STATE {INIT, AUTO_RED, AUTO_GREEN, AUTO_YELLOW, AUTO_RED1_YELLOW2,
					MANUAL_INIT, MANUAL_RED, MANUAL_GREEN, MANUAL_YELLOW, MANUAL_RED1_YELLOW2,
					TUNING_INIT, TUNING_RED, TUNING_GREEN, TUNING_YELLOW};


extern enum TRAFFIC_STATE status;
extern const int MAX_LED;
extern int red;
extern int green;
extern int yellow;
extern int isPed;
extern char message[MAX_MESSAGE_LENGTH];

extern UART_HandleTypeDef huart2;

//7segment

//void display7SEG(int);
//void update7SEG (int);
//void updateCounterBuffer(int, int);

//Traffic lights
void clearTrafficLights();
void controlTrafficLights(int color1, int color2);
void controlPedLights(int color);

//LEDS
void toggleRedLED();
void toggleGreenLED();
void toggleYellowLED();

#endif /* INC_GLOBAL_H_ */
