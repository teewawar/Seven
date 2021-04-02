#include "bp.h"
#include "timer.h"
#include "led.h"
#include "buz.h"
#include "aff7seg.h"
#include "app.h"

void setup()
{
  Serial.begin(115200);
  BpInit();
  LedInit();
  BuzInit();
  AffSegInit();
  AppInit();

  TimerInit270Hz_T0();
  TimerInit25ms_T1();
  TimerInit8Khz_T2();
  
  BuzDemande(BUZ_OK);  
  
}

void loop()
{
  BpDetectAppui();
  LedBlink();
  BuzJoue();

  //Minuteur 1 à 999 sec.
  AppReglage();
  AppMinuteur();
  
}
