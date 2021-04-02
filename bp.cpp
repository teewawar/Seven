#include "bp.h"

#define BP1 BIT0
#define BP2 BIT1

byte BpAppuye;
bool FoDetectRelache;

byte BpRecupBpAppuye(void)
{ return BpAppuye;   }

void BpInit(void)
{
  p_c_in( BP1 | BP2 );
  FoDetectRelache = false;  
}

void BpDetectAppui(void)
{
  if( FoDetectRelache==true )
  {
   if( p_c_read(BP1) && p_c_read(BP2) )  
   {  FoDetectRelache = false;  }

   return;   
  }
  
  BpAppuye = NO_KEY;
  
  if( p_c_read(BP1)==0 )
  {
    BpAppuye = KEY_UP;    
  }
  else if( p_c_read(BP2)==0 )
  {
    BpAppuye = KEY_DOWN;    
  }

  if( BpAppuye!=NO_KEY )
  { FoDetectRelache=true; }
  
}
