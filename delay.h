#ifndef DELAY_H
#define DELAY_H

#define MILLI_TO_MIKRO 1000
#define STK_CTRL ((volatile unsigned int *) 0xE000E010   )
#define STK_LOAD ((volatile unsigned int *) 0xE000E014   )
#define STK_VAL ((volatile unsigned int *) 0xE000E018    )
#define COUNT_VAL ((unsigned int)(42))

void delay_milli(unsigned int ms);

void delay_mikro(unsigned int us);
void delay_250ns(void);

#endif