#ifndef switches_included
#define switches_included

#define SW1 BIT0
#define SW2 BIT1
#define SW3 BIT2
#define SW4 BIT3
#define SWITCHES (SW1 | SW2 | SW3 | SW4)

#include "msp430.h"

unsigned int p2sw_read();
void p2sw_init(unsigned char mask);
void switch_interrupt_handler();

extern char state1, state2, state3, state4, button_state;

#endif // included
