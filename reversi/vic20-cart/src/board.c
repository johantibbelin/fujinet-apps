/**
 * @brief #FujiNet Reversi
 * @author  Thomas Cherryhomes
 * @email   thom dot cherryhomes at gmail dot com
 * @license gpl v. 3
 */

#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "csram.h"
#include "video.h"
#include "board.h"

unsigned char count_white, count_black;

/**
 * @brief board positions to check in color RAM
 */
unsigned short board_pos[64]=
    {
      25,27,29,31,33,35,37,39,
      69,71,73,75,77,79,81,83,
      113,115,117,119,121,123,125,127,
      157,159,161,163,165,167,169,171,
      201,203,205,207,209,211,213,215,
      245,247,249,251,253,255,257,259,
      289,291,293,295,297,299,301,303,
      333,335,337,339,341,343,345,347
    };

/**
 * @brief initial board video RAM (as screen codes)
 */
char board_char[] =
  {
    0x20,0x20,0x41,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x48,0x20,0x20,
    
    0x20,0x20,0x3F,0x42,0x43,0x42,0x43,0x42,0x43,0x42,0x43,0x42,0x43,0x42,0x43,0x42,0x43,0x42,0x43,0x47,0x20,0x20,
    0x20,0x20,0x3F,0x44,0x45,0x44,0x45,0x44,0x45,0x44,0x45,0x44,0x45,0x44,0x45,0x44,0x45,0x44,0x45,0x47,0x20,0x20,

    0x20,0x20,0x3F,0x42,0x43,0x42,0x43,0x42,0x43,0x42,0x43,0x42,0x43,0x42,0x43,0x42,0x43,0x42,0x43,0x47,0x20,0x20,
    0x20,0x20,0x3F,0x44,0x45,0x44,0x45,0x44,0x45,0x44,0x45,0x44,0x45,0x44,0x45,0x44,0x45,0x44,0x45,0x47,0x20,0x20,

    0x20,0x20,0x3F,0x42,0x43,0x42,0x43,0x42,0x43,0x42,0x43,0x42,0x43,0x42,0x43,0x42,0x43,0x42,0x43,0x47,0x20,0x20,
    0x20,0x20,0x3F,0x44,0x45,0x44,0x45,0x44,0x45,0x44,0x45,0x44,0x45,0x44,0x45,0x44,0x45,0x44,0x45,0x47,0x20,0x20,

    0x20,0x20,0x3F,0x42,0x43,0x42,0x43,0x42,0x43,0x42,0x43,0x42,0x43,0x42,0x43,0x42,0x43,0x42,0x43,0x47,0x20,0x20,
    0x20,0x20,0x3F,0x44,0x45,0x44,0x45,0x44,0x45,0x44,0x45,0x44,0x45,0x44,0x45,0x44,0x45,0x44,0x45,0x47,0x20,0x20,

    0x20,0x20,0x3F,0x42,0x43,0x42,0x43,0x42,0x43,0x42,0x43,0x42,0x43,0x42,0x43,0x42,0x43,0x42,0x43,0x47,0x20,0x20,
    0x20,0x20,0x3F,0x44,0x45,0x44,0x45,0x44,0x45,0x44,0x45,0x44,0x45,0x44,0x45,0x44,0x45,0x44,0x45,0x47,0x20,0x20,

    0x20,0x20,0x3F,0x42,0x43,0x42,0x43,0x42,0x43,0x42,0x43,0x42,0x43,0x42,0x43,0x42,0x43,0x42,0x43,0x47,0x20,0x20,
    0x20,0x20,0x3F,0x44,0x45,0x44,0x45,0x44,0x45,0x44,0x45,0x44,0x45,0x44,0x45,0x44,0x45,0x44,0x45,0x47,0x20,0x20,

    0x20,0x20,0x3F,0x42,0x43,0x42,0x43,0x42,0x43,0x42,0x43,0x42,0x43,0x42,0x43,0x42,0x43,0x42,0x43,0x47,0x20,0x20,
    0x20,0x20,0x3F,0x44,0x45,0x44,0x45,0x44,0x45,0x44,0x45,0x44,0x45,0x44,0x45,0x44,0x45,0x44,0x45,0x47,0x20,0x20,

    0x20,0x20,0x3F,0x42,0x43,0x42,0x43,0x42,0x43,0x42,0x43,0x42,0x43,0x42,0x43,0x42,0x43,0x42,0x43,0x47,0x20,0x20,
    0x20,0x20,0x3F,0x44,0x45,0x44,0x45,0x44,0x45,0x44,0x45,0x44,0x45,0x44,0x45,0x44,0x45,0x44,0x45,0x47,0x20,0x20,

    0x20,0x20,0x4A,0x46,0x46,0x46,0x46,0x46,0x46,0x46,0x46,0x46,0x46,0x46,0x46,0x46,0x46,0x46,0x46,0x49,0x20,0x20    
  };

/**
 * @brief footer display (as screen codes)
 */
const char footer[]={0xA0,0xA0,0xA0,0xA3,0x86,0x95,0x8A,0x89,0x8E,0x85,0x94,0xA0,0x92,0x85,0x96,0x85,0x92,0x93,0x89,0xA0,0xA0,0xA0};

/**
 * @brief count # of pieces to white/black
 */
void board_count(void)
{
  unsigned char i;

  count_white=
    count_black=0;
  
  for (i=0;i<64;i++)
    {
      unsigned char c = video_ram_color(board_pos[i]);
      
      if (c==0x08)
	count_black++;
      else if (c==0x09)
	count_white++;
    }
}

/**
 * @brief return disc at board position
 */
Disc board_get_disc(Position p)
{
  unsigned char c = video_ram_color(board_pos[p]);

  switch(c)
    {
    case 0x08:
      return BLACK;
    case 0x09:
      return WHITE;
    case 0x0d:
      return NONE;
    }
}

/**
 * @brief place a piece on board
 * @param p board position to place piece
 * @param d Disc color
 */
void board_place_disc(Position p, Disc d)
{
  unsigned short o = board_pos[p];
  char s[3];
  
  // Set the characters
  VIDEO_RAM[o]=DISC_CHAR_1;
  VIDEO_RAM[o+1]=DISC_CHAR_2;
  VIDEO_RAM[o+22]=DISC_CHAR_3;
  VIDEO_RAM[o+23]=DISC_CHAR_4;

  // Set the color
  COLOR_RAM[o]=
    COLOR_RAM[o+1]=
    COLOR_RAM[o+22]=
    COLOR_RAM[o+23]=d+COLOR_RAM_BIAS;

  // Update count, and display
  board_count();

  gotoxy(2,18);
  print("\x05tschak");
  gotoxy(18,18);
  itoa(count_white,s,10);
  print(s);
  gotoxy(2,19);
  print("\x90""mozzwald");
  gotoxy(18,19);
  itoa(count_black,s,10);
  print(s);
}

/**
 * @brief assuming valid move, flip discs until there are no more opponent discs in direction.
 * @param p board position
 * @param dx delta x
 * @param dy delta y
 * @param m my piece
 * @param o opponent piece
 */
void board_flip(Position p, signed char dx, signed char dy, Disc m, Disc o)
{
  int x,y;

  // Convert position to x,y coordinates to make edge checking easier
  y = p / BOARD_SIZE;
  x = p % BOARD_SIZE;

  while (board_get_disc(p) == o)
    {
      board_place_disc(p,m);
      x += dx;
      y += dy;
      p = dy * BOARD_SIZE + dx;
    }
}

/**
 * @brief are we inside board?
 * @param x derived X coordinate
 * @param y derived Y coordinate
 */
bool board_inside(int x, int y)
{
  bool ix = (x >= 0) && (x < 8);
  bool iy = (y >= 0) && (y < 8);

  return (ix && iy);
}

/**
 * @brief walk board
 * @param p board position
 * @param dx delta x
 * @param dy delta y
 * @param m my piece
 * @param o opponent piece
 * @return true = we can flip, otherwise false.
 */
bool board_walk(Position p, int dx, int dy, Disc m, Disc o)
{
  int x,y;

  // Convert position to x,y coordinates to make edge checking easier
  y = p / BOARD_SIZE;
  x = p % BOARD_SIZE;
  
  if (board_get_disc(p) == o)
    {
      while (board_inside(x,y))
	{
	  x += dx;
	  y += dy;
	  p = y * BOARD_SIZE + x;
	  
	  if (board_get_disc(p) == NONE)
	    return false;
	  else if (board_get_disc(p) == m)
	    return true;
	}
    }
  else
    {
      // Opponent disc, keep walking.
    }

  // Either no consecutive opponent disc, or hit the edge;
  return false;
}

/**
 * @brief Check for valid move in all directions, set bit.
 * @param p selected board position
 * @param m color of my piece
 * @param o color of opponent piece
 * @return bit 0 = left, bit 1 = right, bit 2 = down, bit 3 = up
 *         bit 4 = down-left, bit 5 = down-right, bit 6 = up-left, bit 7 = up-right
 */
ValidMoves board_check_move(Position p, Disc m, Disc o)
{
  unsigned char ret = 0;

  // Check left
  if (board_walk(p-1,-1,0,m,o))
    ret |= 0x01;

  // Check right
  if (board_walk(p+1,-1,0,m,o))
    ret |= 0x02;

  // Check down
  if (board_walk(p+BOARD_SIZE,-1,0,m,o))
    ret |= 0x04;

  // Check up
  if (board_walk(p-BOARD_SIZE,-1,0,m,o))
    ret |= 0x08;

  // Check down-left
  if (board_walk(p+BOARD_SIZE-1,-1,0,m,o))
    ret |= 0x10;

  // Check down-right
  if (board_walk(p+BOARD_SIZE+1,-1,0,m,o))
    ret |= 0x20;

  // Check up-left
  if (board_walk(p-BOARD_SIZE-1,-1,0,m,o))
    ret |= 0x40;

  // Check up-right
  if (board_walk(p-BOARD_SIZE+1,-1,0,m,o))
    ret |= 0x80;

  return ret;
}

/**
 * @brief attempt board move
 * @param p Position to try
 * @param m color of my disc
 * @param o color of opponent disc
 * @return true if move successful, otherwise false.
 */
bool board_move(Position p, Disc m, Disc o)
{
  ValidMoves v;

  v = board_check_move(p,m,o);
  
  /* Return if no valid moves */
  if (!v)
    return false;
  else
    board_place_disc(p,m);

  if (v & 0x01) // left
    board_flip(p-1,-1,0,m,o);
  if (v & 0x02) // right
    board_flip(p+1,1,0,m,o);
  if (v & 0x04) // down
    board_flip(p+BOARD_SIZE,0,-1,m,o);
  if (v & 0x08) // up
    board_flip(p-BOARD_SIZE,0,1,m,o);
  if (v & 0x10) // down-left
    board_flip(p+BOARD_SIZE-1,-1,1,m,o);
  if (v & 0x20) // down-right
    board_flip(p+BOARD_SIZE+1,1,1,m,o);
  if (v & 0x40) // up-left
    board_flip(p-BOARD_SIZE-1,-1,-1,m,o);
  if (v & 0x80) // up right
    board_flip(p-BOARD_SIZE+1,1,1,m,o);
  
  return true;
}

/**
 * @brief reset the board
 */
void board_reset(void)
{
  // Reset color ram
  memset(COLOR_RAM,COLOR_NONE,sizeof(board_char));

  // and place board background characters
  memcpy(VIDEO_RAM,board_char,sizeof(board_char));

  // Now place initial discs
  board_place_disc(START_POS_1,BLACK);
  board_place_disc(START_POS_2,WHITE);
  board_place_disc(START_POS_3,WHITE);
  board_place_disc(START_POS_4,BLACK);

  // Place footer
  memcpy(&VIDEO_RAM[FOOTER_OFFSET],&footer[0],sizeof(footer));
  memset(&COLOR_RAM[FOOTER_OFFSET],0x00,sizeof(footer));
}
