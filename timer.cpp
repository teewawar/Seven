#include "led.h"
#include "buz.h"
#include "aff7seg.h"
#include "app.h"

#include "timer.h"

//Timer 1 pour différentes temporisations
void TimerInit25ms_T1(void)
{ 
  noInterrupts();
  // Réglage de l'interruption timer 1 à 40Hz pour la réalisation de différentes temporisation
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0; // compteur à 0
  
  // Calcul valeur du reg de comparaison pour avoir 40Hz
  //(16000000 / (40*1024)) - 1; //(doit être <65536)
  OCR1A = 389;
  
  // turn on CTC mode
  TCCR1B |= 0x08;
  // Set CS12 and CS10 bits for 1024 prescaler
  TCCR1B |= 0x05;
  // enable timer compare interrupt
  TIMSK1 |= 0x02;
  
  interrupts();
}

ISR(TIMER1_COMPA_vect)
{ //toutes les 25ms le programme va se brancher ici
  LedDec();
  BuzDec();
  AppDec();
}

//Timer 2 pour le buzzer
void TimerInit8Khz_T2(void)
{  
  //set timer2 interrupt at 8kHz
  TCCR2A = 0;
  TCCR2B = 0;
  TCNT2  = 0; // compteur à 0
  
  // set compare match register for 8khz increments
  // = (16*10^6) / (8000*8) - 1 //(must be <256)
  OCR2A = 249;
  // turn on CTC mode
  TCCR2A |= 0x02;
  // Set CS21 bit for 8 prescaler
  TCCR2B |= 0x02;  
}

void TimerInit8Khz_T2_Start(void)
{ 
  TIMSK2 |= 0x02;
}

void TimerInit8Khz_T2_Stop(void)
{ 
  TIMSK2 &= ~(0x02);
}

ISR(TIMER2_COMPA_vect)
{ //toutes les 125us le programme va se brancher ici
  BuzToggle();  
}


void TimerInit270Hz_T0(void)
{
  noInterrupts();
  
  // Réglage de l'interruption timer 0 à 3.6ms (274Hz) pour le rafraichissment des afficheurs 7 segments 
  TCCR0A = 0;
  TCCR0B = 0;
  TCNT0  = 0; // compteur à 0
  
  // Calcul valeur du reg de comparaison pour avoir 274Hz
  OCR0A = 56;// = (16*10^6) / (274*1024) - 1 (doit être < 256)
  // turn on CTC mode
  TCCR0A |= 0x02;
  // Set CS02 and CS00 bits for 1024 prescaler
  TCCR0B |= 0x05;
  // enable timer compare interrupt
  TIMSK0 |= (1 << OCIE0A);
  
  interrupts();
}

ISR(TIMER0_COMPA_vect)
{ //toutes les 3.6 ms les afficheurs sont traités
  AffMajAffichage();
}
