#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

#define TICK 10
#define MAX_TIMERS 8

extern int timer_flag[MAX_TIMERS];

void setTimer(int duration, int id);

void timerRun();

void setTimerFlag(int id, int value);


#endif /* INC_SOFTWARE_TIMER_H_ */
