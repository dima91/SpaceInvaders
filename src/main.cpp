/**
 * \file main.cpp
 * \brief Main file for the project "Space Invaders"
 * \author Luca Di Mauro
 */

#include "./SpaceInvaders.h"
#include "Components.h"
#include <cstdlib>
#include <iostream>


/** \brief Function that print on stdscr start messge */
void startMessage ();


/** \brief Main function of game */
int main ()
{
   int direction;
   bool end= FALSE;

   initscr ();
   keypad (stdscr, TRUE);
   curs_set (0);
   noecho ();
   nodelay(stdscr,TRUE);
   srand (time(NULL));

   game_t *game= new game_t (COLS, LINES, COLS/2, LINES-1, 1);

   // Print start message
   move (0,0);
   game->startMessage ();
   while ((direction=getch ()) != (int)'s')
   {
      if (direction== (int) 'q')
	 {
	    end=TRUE;
	    break ;
	 }
   }

   move(0, 0);
   erase ();

   direction=0;

   // GAME LOOP:
   // (1.a)..GET A COMMAND______(1.b)..PARSE COMMAND______(2.a)..MOVE BULLIST______(2.b)..MOVE ENEMIES______(3.a-b)..CHECK COLLISION______(4)..GENERATE ENEMIES______(5)..PRINT
   while (!end)
   {
      // ..(1.a)..
      direction= getch ();

      // ..(1.b)..
      switch (direction)
      {
	 case KEY_RIGHT:
	    game->moveRight (1);
	    break ;
	 case KEY_LEFT:
	    game->moveLeft (1);
	    break;
	 case (int) 's':
	    game->shoot ();
	    break ;
	 case (int) 'q':
	    end=TRUE;
	    break ;
	 case (int) 'p':
	    break;
      }

      // ..(2.a)..
      game->moveBullet ();
      // ..(2.b)..
      game->moveEnemies ();

      // ..(3.a)..
      // Check if there are collision between bullets and enemies and, possibly, manages them
      game->checkCollision ();

      // ..(3.b)..
      // Check if there are collision between enemies and cannon
      if (game->checkCannonCollision ())
      {
	 erase ();
	 mvprintw (20, 20, "************** SEI MORTO!!!!!! **************");
	 refresh ();
	 napms (3000);
	 end=TRUE;
      }
      
      // ..(4)..
      if ((rand() % 19813)==0)
	 // I create new enemy
	 game->addEnemy (((rand ())%(COLS)), 1, ((rand())%4));
      

      // ..(5).. print on stdscr and refresh
      game->print ();
      direction=0;
      refresh ();
   }


   endwin ();
   return 0;
}
