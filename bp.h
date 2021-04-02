#ifndef BP_H
#define BP_H

#include "gpio.h"

#define NO_KEY        0
#define KEY_UP        1 
#define KEY_DOWN      2

void BpInit(void);
void BpDetectAppui(void);
byte BpRecupBpAppuye(void);


#endif
