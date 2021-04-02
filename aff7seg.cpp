#include "aff7seg.h"

void DesactiverLesAfficheurs(void);
void EteindreLesSegments(void);

//sur le port D
#define PD_SA   BIT2
#define PD_SB   BIT3
#define PD_SC   BIT4
#define PD_SD   BIT5
#define PD_SE   BIT6
#define PD_SF   BIT7
//sur le port B
#define PB_SG   BIT0
#define PB_SP   BIT1

//sur le port B
#define AFF1    BIT5
#define AFF2    BIT4
#define AFF3    BIT3

#define DESEL_AFF1  p_b_low(AFF1)
#define DESEL_AFF2  p_b_low(AFF2)
#define DESEL_AFF3  p_b_low(AFF3)

#define SEL_AFF1    p_b_high(AFF1)
#define SEL_AFF2    p_b_high(AFF2)
#define SEL_AFF3    p_b_high(AFF3)

#define ZERO    (PD_SA|PD_SB|PD_SC|PD_SD|PD_SE|PD_SF)
#define UN      (PD_SB|PD_SC)
#define DEUX    (PD_SA|PD_SB|PD_SD|PD_SE)
#define TROIS   (PD_SA|PD_SB|PD_SC|PD_SD)
#define QUATRE  (PD_SF|PD_SB|PD_SC)
#define CINQ    (PD_SA|PD_SF|PD_SC|PD_SD)
#define SIX     (PD_SA|PD_SF|PD_SC|PD_SD|PD_SE)
#define SEPT    (PD_SA|PD_SB|PD_SC)
#define HUIT    (PD_SA|PD_SB|PD_SC|PD_SD|PD_SE|PD_SF)
#define NEUF    (PD_SA|PD_SB|PD_SC|PD_SD|PD_SF)

byte NumAfficheur;
byte TabChiffreAfficher[3]={0,0,0};

byte TabDesChiffres[10]=
{
  ZERO,
  UN,
  DEUX,
  TROIS,
  QUATRE,
  CINQ,
  SIX,
  SEPT,
  HUIT,
  NEUF
};

void AffSegInit(void)
{
    p_b_low( AFF1 | AFF2 | AFF3 );
    p_b_high( PB_SG | PB_SP );
    p_b_out( AFF1 | AFF2 | AFF3 | PB_SG | PB_SP );

    p_d_high( PD_SA | PD_SB | PD_SC | PD_SD | PD_SE | PD_SF );
    p_d_out( PD_SA | PD_SB | PD_SC | PD_SD | PD_SE | PD_SF );

    NumAfficheur = 1;    
}

void AffMajAffichage(void) 
{ 
  byte chiffre;

  EteindreLesSegments();
  DesactiverLesAfficheurs();

  switch( NumAfficheur )
  {
    case 1:
      SEL_AFF1;
      chiffre = TabChiffreAfficher[0];  //centaine      
    break;

    case 2:
      SEL_AFF2;
      chiffre = TabChiffreAfficher[1];  //dizaine
    break;

    case 3:
      SEL_AFF3;
      chiffre = TabChiffreAfficher[2];  //unite
    break;
  }
  
  if( (chiffre!=0) && (chiffre!=1) && (chiffre!=7) )
  { p_b_low( PB_SG ); }
  
  p_d_low( TabDesChiffres[chiffre] );
  
  NumAfficheur++;
  if( NumAfficheur > 3 )
  { NumAfficheur = 1;  }
  
}

void AffSegExtraitCentDizUni(int nbre) //999
{   //init
    TabChiffreAfficher[0]=0; 
    TabChiffreAfficher[1]=0;
    TabChiffreAfficher[2]=0;
    
    //extraire centaine, dizaine et unité
    while(nbre>=100)
    { TabChiffreAfficher[0]++;
      nbre-=100;  }

    while(nbre>=10)
    { TabChiffreAfficher[1]++;
      nbre-=10;  }

    TabChiffreAfficher[2] = nbre;
}

void DesactiverLesAfficheurs(void)
{
  DESEL_AFF1;
  DESEL_AFF2;
  DESEL_AFF3;  
}

void EteindreLesSegments(void)
{
  p_d_high( PD_SA | PD_SB | PD_SC | PD_SD | PD_SE | PD_SF );
  p_b_high( PB_SG | PB_SP );
  
}
