#include "buz.h"
#include "bp.h"
#include "aff7seg.h"
#include "timer.h"

#include "app.h"

void MinuteurRepos(void);

int nbre;

#define COMPTEUR_MAX  999
#define COMPTEUR_MIN  0

byte PhaseAppRegl;
  #define ATT_APPUI_BP    1
  #define ATT_RELACHE_BP  2

byte PhaseAppMinuteur;
  #define ATT_AV_DEC      1
  #define DECOMPTE        2

byte TempoAvValide,TempoAvDec;
        
void AppInit(void)
{
  PhaseAppRegl = ATT_APPUI_BP;
  MinuteurRepos();
}

void AppReglage(void)
{ 
  byte bp;

  bp = BpRecupBpAppuye();
  
  switch( PhaseAppRegl )
  {
    case REPOS:
    break;

    case ATT_APPUI_BP:
      if( bp==KEY_UP )
      {
        if( nbre<COMPTEUR_MAX )
        { nbre++; }
      }
      else if( bp==KEY_DOWN )
      {
        if( nbre>COMPTEUR_MIN )
        { nbre--; }
      }

      if( bp!=NO_KEY )
      { 
        MinuteurRepos();
        AffSegExtraitCentDizUni(nbre);
        BuzDemande(BUZ_BP);
        TempoAvValide = UNE_SEC;
        PhaseAppRegl = ATT_RELACHE_BP;
      }
    break;

    case ATT_RELACHE_BP:
      if( bp==NO_KEY )
      { PhaseAppRegl = ATT_APPUI_BP;  }
    break;
        
  }
}

void MinuteurRepos(void)
{ PhaseAppMinuteur = REPOS;  }

void AppMinuteur(void)
{
  switch( PhaseAppMinuteur )
  {
      case REPOS:
        if( (nbre>0) && (TempoAvValide==0) )
        { BuzDemande(BUZ_TIT_TIT);
          TempoAvDec = UNE_SEC;
          PhaseAppMinuteur = ATT_AV_DEC;
        }
      break;

      case ATT_AV_DEC:
        if( TempoAvDec==0 )
        { PhaseAppMinuteur = DECOMPTE;  }
      break;

      case DECOMPTE:
        if( TempoAvDec ) break;
        
        nbre--;
        AffSegExtraitCentDizUni(nbre);
        
        if( nbre==0 )
        { 
          BuzDemande(BUZ_OK);
          PhaseAppMinuteur = REPOS;
        }
        else
        {
          if( nbre>10 )
          {
            if( (nbre%10)==0 )
            { BuzDemande(BUZ_BP); }
          }
          else
          {
            BuzDemande(BUZ_BP);
          }
        }
        TempoAvDec = UNE_SEC;        
      break;
  }
}

void AppDec(void)
{
  if( TempoAvDec>0 )  TempoAvDec--;
  if( TempoAvValide ) TempoAvValide--;
}
