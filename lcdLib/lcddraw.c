/** \file lcddraw.c
 *  \brief Adapted from RobG's EduKit
 */
#include "lcdutils.h"
#include "lcddraw.h"


/** Draw single pixel at x,row 
 *
 *  \param col Column to draw to
 *  \param row Row to draw to
 *  \param colorBGR Color of pixel in BGR
 */
void drawPixel(u_char col, u_char row, u_int colorBGR) 
{
  lcd_setArea(col, row, col, row);
  lcd_writeColor(colorBGR);
}

/** Fill rectangle
 *
 *  \param colMin Column start
 *  \param rowMin Row start
 *  \param width Width of rectangle
 *  \param height height of rectangle
 *  \param colorBGR Color of rectangle in BGR
 */
void fillRectangle(u_char colMin, u_char rowMin, u_char width, u_char height, 
		   u_int colorBGR)
{
  u_char colLimit = colMin + width, rowLimit = rowMin + height;
  lcd_setArea(colMin, rowMin, colLimit - 1, rowLimit - 1);
  u_int total = width * height;
  u_int c = 0;
  while ((c++) < total) {
    lcd_writeColor(colorBGR);
  }
}

/** Clear screen (fill with color)
 *  
 *  \param colorBGR The color to fill screen
 */
void clearScreen(u_int colorBGR) 
{
  u_char w = screenWidth;
  u_char h = screenHeight;
  fillRectangle(0, 0, screenWidth, screenHeight, colorBGR);
}

/** 5x7 font - this function draws background pixels
 *  Adapted from RobG's EduKit
 */
void drawChar5x7(u_char rcol, u_char rrow, char c, 
     u_int fgColorBGR, u_int bgColorBGR) 
{
  u_char col = 0;
  u_char row = 0;
  u_char bit = 0x01;
  u_char oc = c - 0x20;

  lcd_setArea(rcol, rrow, rcol + 4, rrow + 7); /* relative to requested col/row */
  while (row < 8) {
    while (col < 5) {
      u_int colorBGR = (font_5x7[oc][col] & bit) ? fgColorBGR : bgColorBGR;
      lcd_writeColor(colorBGR);
      col++;
    }
    col = 0;
    bit <<= 1;
    row++;
  }
}
//draw char 11x16
void drawChar11x16(u_char rcol, u_char rrow, char c, u_int fgColorBGR, u_int bgColorBGR) {
  u_char col = 0;
  u_char row = 0;
  u_int bit = 0x0001; //Changed from u_char to u_int
  u_char oc = c - 0x20;

  lcd_setArea(rcol, rrow, rcol+10, rrow+16); /*relatize to requested col/row*/
  while (row < 17) {
    while (col < 11) {
      u_int colorBGR = (font_11x16[oc][col] & bit) ? fgColorBGR : bgColorBGR;
      lcd_writeColor(colorBGR);
      col++;
    }
    col = 0;
    bit <<= 1;
    row++;
  }
}//end draw Char

/** Draw string at col,row
 *  Type:
 *  FONT_SM - small (5x8,) FONT_MD - medium (8x12,) FONT_LG - large (11x16)
 *  FONT_SM_BKG, FONT_MD_BKG, FONT_LG_BKG - as above, but with background color
 *  Adapted from RobG's EduKit
 *
 *  \param col Column to start drawing string
 *  \param row Row to start drawing string
 *  \param string The string
 *  \param fgColorBGR Foreground color in BGR
 *  \param bgColorBGR Background color in BGR
 */
void drawString5x7(u_char col, u_char row, char *string,
		u_int fgColorBGR, u_int bgColorBGR)
{
  u_char cols = col;
  while (*string) {
    drawChar5x7(cols, row, *string++, fgColorBGR, bgColorBGR);
    cols += 6;
  }
}

void drawString11x16(u_char col, u_char row, char *string, u_int fgColorBGR, u_int bgColorBGR) {
  u_char cols = col;
  while (*string) {
    drawChar11x16(cols, row, *string++, fgColorBGR, bgColorBGR);
    cols += 12;
  }
}//end drawString11x16


/** Draw rectangle outline
 *  
 *  \param colMin Column start
 *  \param rowMin Row start 
 *  \param width Width of rectangle
 *  \param height Height of rectangle
 *  \param colorBGR Color of rectangle in BGR
 */
void drawRectOutline(u_char colMin, u_char rowMin, u_char width, u_char height,
		     u_int colorBGR)
{
  /**< top & bot */
  fillRectangle(colMin, rowMin, width, 1, colorBGR);
  fillRectangle(colMin, rowMin + height, width, 1, colorBGR);

  /**< left & right */
  fillRectangle(colMin, rowMin, 1, height, colorBGR);
  fillRectangle(colMin + width, rowMin, 1, height, colorBGR);
}

void fillTriangle(u_char colMin, u_char rowMin, u_char width, u_char height, u_int colorBGR) {
  u_char colLimit = colMin + width, rowLimit = rowMin + height;
  lcd_setArea(colMin, rowMin, colLimit - 1, rowLimit - 1);
  u_int total = width * height;
  u_int c = 0;
  while ((c++) < total) {
    lcd_writeColor(colorBGR);
  }
}

void redrawTurtle(u_char ofc, u_char ofr) {
  u_char col = 0;
  u_char row = 0;
  while (row < 16) {
    col = 0;
    while (col < 16) {
      drawPixel(col+ofc, row+ofr, COLOR_BLUE);
      col++;
    }
    row++;
  }
}//end redrawTurtle

void drawTurtle(u_char ofc, u_char ofr) {
  u_char col = 0;
  u_char row = 0;
  while (row < 16) {
    col = 0;
    while (col < 16) {
      if (turtle[row][col] == 0) {
	drawPixel(col+ofc, row+ofr, COLOR_BLUE);
      }
      else if (turtle[row][col] == 1) {
	drawPixel(col+ofc, row+ofr, COLOR_DARK_GREEN);
      }
      else if (turtle[row][col] == 2) {
	drawPixel(col+ofc, row+ofr, COLOR_SPRING_GREEN);
      }
      else if (turtle[row][col] == 3) {
	drawPixel(col+ofc, row+ofr, COLOR_BLACK);
      }
      col++;
    }
    row++;
  }
}//end turtle

void drawTopTri(u_char row, u_char col) {
  u_char my_row, my_col;
  u_char middle = 10;
  for (my_row = 0; my_row <= 10; row++) {
    for (my_col = 10; my_col <= row; col++) {
      drawPixel(middle+my_col+55+col, my_row+60+row, COLOR_GREEN);
      drawPixel(middle-my_col+55+col, my_row+60+row, COLOR_GREEN);
    }
  }
}

void drawTree(u_char off_row, u_char off_col) {
    u_char row;
    u_char col;
    u_char middle = 10;

    for (row = 0; row <= 10; row++) {
      for (col=0; col<= row; col++) {
	drawPixel(middle+col+55+off_col, row+60+off_row, COLOR_GREEN);
	drawPixel(middle-col+55+off_col, row+60+off_row, COLOR_GREEN);
      }
    }
    //middle
    for(row = 0; row <= 20; row++){
      for(col = 0; col <= row; col++){
	drawPixel(middle+col+55+off_col, row+65+off_row, COLOR_GREEN);
	drawPixel(middle-col+55+off_col, row+65+off_row, COLOR_GREEN);
      }
    }
    //bottom
    for(row = 0; row <= 30; row++){
      for(col = 0; col <= row; col++){
	drawPixel(middle+col+55+off_col, row+73+off_row, COLOR_GREEN);
	drawPixel(middle-col+55+off_col, row+73+off_row, COLOR_GREEN);
      }
    }
    //bark
    for(row = 0; row <= 10; row++){
      for(col = 0; col <= 10; col++){
	drawPixel(col+60+off_col, row+104+off_row, COLOR_BROWN);
      }
    }
  }//end tree
