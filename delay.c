
#include "delay.h"

void delay_250ns(void)
{
    /* SystemCoreClock = 168000000 */
    *STK_CTRL = 0;
    // 168 klockcykler motsvarar 1 mikrosekund, så vi laddar med 168/4 klockcykler
    *STK_LOAD = ( (168/4) -1 );
    *STK_VAL = 0;
    // Sätter igång räknaren
    *STK_CTRL = 5;
    // Så länge countflaggan är 0 sker denna while-loop
    while( (*STK_CTRL & 0x10000 )== 0 );
    *STK_CTRL = 0;
}
// Rutinen tar cirka, dock minst us mikrosekunder, att utföra
void delay_mikro(unsigned int us)
{
    while(us > 0)
    {
        delay_250ns();
        delay_250ns();
        delay_250ns();
        delay_250ns();
        us--;
    }
}
// Rutinen tar cirka, dock minst ms millisekunder, att utföra
void delay_milli(unsigned int ms)
{
    // Annars tar det för långt för att testa programmet i simulatorn
    ms = ms/1000;
   
    while(ms > 0)
    {
        delay_mikro(1000);
        ms--;
    }
}