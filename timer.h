#ifndef TIMER_MINUT_H
#define TIMER_MINUT_H

#include <Arduino.h>

#define _50ms   2
#define _100ms  4
#define _200ms  _100ms*2
#define _300ms  _100ms*3
#define _400ms  _100ms*4
#define _500ms  _100ms*5

#define UNE_SEC  _500ms*2

void TimerInit25ms_T1(void);

void TimerInit8Khz_T2(void);
void TimerInit8Khz_T2_Start(void);
void TimerInit8Khz_T2_Stop(void);

void TimerInit270Hz_T0(void);

#endif
