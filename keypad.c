
#include "keypad.h"
#include "GPIO.h"

void kbdActivate(unsigned int row){
    switch (row){
        case 0: //row 1
            *GPIO_D_ODR_HIGH=0x10;
            break;
        case 1: //row 2
            *GPIO_D_ODR_HIGH=0x20;
            break;
        case 2: //row 3
            *GPIO_D_ODR_HIGH=0x40;
            break;
        case 3: //row 4
            *GPIO_D_ODR_HIGH=0x80;
            break;
        default:    //reset all rows
            *GPIO_D_ODR_HIGH=0x0;
    }
}

int kbdGetCol(){
    unsigned int column=*GPIO_D_IDR_HIGH;
    if(column&0x1){
        return 0;
    } else if (column&0x2){
        return 1;
    } else if (column&0x4){
        return 2;
    } else if (column&0x8){
        return 3;
    } else {
        return 4;
    }
}

unsigned char keyb(void)
{
    unsigned char key[] = { 0x1,0x2,0x3,0xA,
                            0x4,0x5,0x6,0xB,
                            0x7,0x8,0x9,0xC,
                            0xE,0x0,0xF,0xD };
    for(int i=0; i<4;i++){
        kbdActivate(i);
        
        unsigned char col =kbdGetCol();
        kbdActivate(4);     //turn off
        if(col!=4){
            return key[4*i+col];
        }
    }
    return 0xFF;
}