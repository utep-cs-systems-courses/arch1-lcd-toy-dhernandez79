#include <msp430.h>
#include "buzzer.h"
#include "led.h"
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "p2switches.h"
#include "stateMachines.h"

void main() {

  //Text on top of screen
  drawString5x7(5, 5, "Demetrius Hernandez", COLOR_WHITE, COLOR_BLACK);
  

}
