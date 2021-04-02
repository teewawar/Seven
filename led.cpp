#include "timer.h"

#include "led.h"

#define LED BIT5

byte TempoLed;

void LedInit(void)
{
  p_c_out(LED);
  p_c_high(LED);  
}

void LedBlink(void)
{
  if( TempoLed==0 )
  {
    p_c_toggle(LED);
    TempoLed = UNE_SEC;
  }
}

void LedDec(void)
{
  if( TempoLed ) TempoLed--;  
}
