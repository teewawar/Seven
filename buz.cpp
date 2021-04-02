#include "timer.h"

#include "buz.h"

#define BUZ BIT2

byte BuzTimer;
byte QuelTypBip;
byte BuzCompteur;

void BuzInit(void)
{
  p_b_out(BUZ);
  p_b_low(BUZ);
}

void BuzDemande(byte TypBip)
{ 
  QuelTypBip = TypBip;

  switch(TypBip)
  {
    case BUZ_OK:
      TimerInit8Khz_T2_Start();
      BuzTimer = _400ms;
    break;

    case BUZ_BP:
      TimerInit8Khz_T2_Start();
      BuzTimer = _50ms;
    break;

    case BUZ_TIT_TIT:
      BuzCompteur = 4;
      TimerInit8Khz_T2_Start();
      BuzTimer = _50ms;
    break;
    
  }
  
}

void BuzJoue(void)
{
  switch(QuelTypBip)
  {
    case REPOS:
    break;

    case BUZ_QUIET:
      TimerInit8Khz_T2_Stop();
      p_b_low(BUZ);
      QuelTypBip = REPOS;
    break;
    
    case BUZ_OK:
    case BUZ_BP:
      if( BuzTimer==0 )
      { QuelTypBip = BUZ_QUIET;   }
    break;

    case BUZ_TIT_TIT:
      if( BuzTimer==0 )
      {
        TimerInit8Khz_T2_Stop();
        p_b_low(BUZ);
        BuzCompteur--;
        if( BuzCompteur==0 )
        { QuelTypBip = REPOS; }
        else
        { BuzTimer = _50ms;
          QuelTypBip = BUZ_TIT_TIT2; }        
      }
    break;
    
    case BUZ_TIT_TIT2:
      if( BuzTimer==0 )
      { TimerInit8Khz_T2_Start();
        BuzTimer = _50ms;
        QuelTypBip = BUZ_TIT_TIT;   }
      
    break;
  }
}

void BuzToggle(void)
{
  p_b_toggle(BUZ);
}

void BuzDec(void)
{
  if( BuzTimer ) BuzTimer--;
}
