#ifndef GPIO_H
#define GPIO_H

#define GPIO_D_IDR_LOW ((volatile unsigned char *) (0x40020c10))
#define GPIO_D_IDR_HIGH ((volatile unsigned char *) (0x40020c11))
#define GPIO_D_ODR_LOW ((volatile unsigned char *) (0x40020c14))
#define GPIO_D_ODR_HIGH ((volatile unsigned char *) (0x40020c15))
#define GPIO_D (volatile unsigned int *) 0x40020C00
#define GPIO_OTYPER ((volatile unsigned short *) (0x40020c04))
#define GPIO_OSPEEDR ((volatile unsigned int *) (0x40020c08))
#define GPIO_PUPDR ((volatile unsigned int *) (0x40020c0C))

#endif