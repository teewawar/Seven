#ifndef BUZ_H
#define BUZ_H

#include "gpio.h"

#define REPOS         0
#define BUZ_QUIET     1
#define BUZ_OK        2
#define BUZ_BP        3
#define BUZ_TIT_TIT   4
#define BUZ_TIT_TIT2  5

void BuzInit(void);
void BuzDemande(byte TypBip);
void BuzJoue(void);
void BuzToggle(void);
void BuzDec(void);

#endif
