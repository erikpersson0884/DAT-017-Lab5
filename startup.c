/*
 * startup.c
 *
 */

#define portModer *((volatile unsigned int*)PORT_E)
#define PORT_E 0x40021000

#include "GPIO.h"
#include "delay.h"
#include "keypad.h"
#include "pong.h"

__attribute__((naked)) __attribute__((section (".start_section")) )
void startup ( void )
{
__asm__ volatile(" LDR R0,=0x2001C000\n"); /* set stack */
__asm__ volatile(" MOV SP,R0\n");
__asm__ volatile(" BL main\n"); /* call main */
__asm__ volatile(".L1: B .L1\n"); /* never return */
}
__attribute__((naked))
void graphic_initalize(void)
{
    __asm volatile (" .HWORD 0xDFF0\n");
    __asm volatile (" BX LR\n");
}
__attribute__((naked))
void graphic_clear_screen(void)
{
    __asm volatile (" .HWORD 0xDFF1\n");
    __asm volatile (" BX LR\n");
}
__attribute__((naked))
void graphic_pixel_set(int x, int y)
{
    __asm volatile (" .HWORD 0xDFF2\n");
    __asm volatile (" BX LR\n");
}
__attribute__((naked))
void graphic_pixel_clear(int x, int y)
{
    __asm volatile (" .HWORD 0xDFF3\n");
    __asm volatile (" BX LR\n");
}
void init_app( void )
{
    portModer = 0x55555555;
    *((unsigned long *) 0x40023830) = 0x18;
    * GPIO_D = 0x55005555; 
    * GPIO_PUPDR = 0x00AA0000; 
    * GPIO_OTYPER = 0x0; 
    * GPIO_OSPEEDR = 0x55555555; 
}



static OBJECT ballobject ={
    &ball_geometry,
    3,-3,
    64,32,
    draw_object,
    clear_object,
    move_ballobject,
    set_object_speed
};
static OBJECT paddleobject ={
    &paddle_geometry,
    0,0,
    120,32,
    draw_object,
    clear_object,
    move_paddleobject,
    set_object_speed
};
   
int main(void)
{
    OBJECT ball = ballobject;
    OBJECT paddle = paddleobject;
    
    char c;
    POBJECT ptrball = &ball;
    POBJECT ptrpaddle = &paddle;
    
    init_app();
    graphic_initalize();
    graphic_clear_screen();
    while(1)
    {
        ptrball->move(ptrball);
        ptrpaddle->move(ptrpaddle);
        check_contact_with_ball_and_paddle(ptrball,ptrpaddle);
        delay_milli(20);
        c = keyb();
        switch(c)
        {
            // Up
            case 3: ptrpaddle->set_speed(ptrpaddle,0,-3); break; 
            // Down
            case 9: ptrpaddle->set_speed(ptrpaddle,0,3); break; 
            // New game
            case 6: {
                reset_pong(ptrball,ptrpaddle);
                break;
            }
            default: ptrpaddle->set_speed(ptrpaddle,0,0); break;
        }
    }
}