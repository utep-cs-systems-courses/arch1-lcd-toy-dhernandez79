#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "buzzer.h"
#include "p2switches.h"
#include "stateMachines.h"
#include "led.h"

#define LED_GREEN BIT6             // P1.6


short redrawScreen = 1;
u_int fontFgColor = COLOR_GREEN;

u_char shapeCol = 60;
u_char nextShapeCol = 60;
signed char shapeVelocity = 1;

void wdt_c_handler()
{
  static int secCount = 0;
  static int dsecCount = 0;

  secCount ++;
  dsecCount++;
  if (secCount == 250) {		/* once/sec */
    secCount = 0;
    //fontFgColor = (fontFgColor == COLOR_GREEN) ? COLOR_BLACK : COLOR_GREEN;
    redrawScreen = 1;
  }
  if (dsecCount == 50) {
    dsecCount = 0;
    nextShapeCol += shapeVelocity;
    if (nextShapeCol >= 100 || nextShapeCol <= 60) {
      shapeVelocity = -shapeVelocity;
      nextShapeCol += shapeVelocity;
    }
    redrawScreen = 1;
  }
}//running every interrupt
  

void main()
{
  P1DIR |= LED_GREEN;		/**< Green led on when CPU on */		
  P1OUT |= LED_GREEN;
  configureClocks();
  lcd_init();
  buzzer_init();
  p2sw_init(15);
  
  enableWDTInterrupts();      /**< enable periodic interrupt */
  or_sr(0x8);	              /**< GIE (enable interrupts) */
  
  clearScreen(COLOR_BLUE);
  while (1) {			/* forever */
    if (redrawScreen) { //we redraw screen if needed
      redrawScreen = 0;
      drawString5x7(50,20, "Demetrius Hernandez", fontFgColor, COLOR_WHITE);
      redrawTurtle(20,shapeCol);
      drawTurtle(20,nextShapeCol);
      
      shapeCol = nextShapeCol;

      switch(button_state) {
      case 1:
	buzzer_set_period(2000);
	break;
      case 2:
	myTestMethod();
	break;
      case 3:
	assembly_stuff();
	break;
      case 4:
	reset();
	break;
      }//end switch
    }
    P1OUT &= ~LED_GREEN;	/* green off */
    or_sr(0x10);		/**< CPU OFF */
    /*------------------------------------------*/
    //Goes to assembly file. wdt_handler.s
    P1OUT |= LED_GREEN;		/* green on */
  }
}

    
    



