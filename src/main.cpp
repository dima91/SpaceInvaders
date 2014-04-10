/**
 * \file main.cpp
 * \brief Main file for the project "Space Invaders"
 * \author Luca Di Mauro
 */
#include "./SpaceInvaders.h"
#include "Components.h"
#include <cstdlib>


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
   // (1.a)..GET A COMMAND______(1.b)..PARSE COMMAND______(2.a)..MOVE BULLIST______(2.b)..MOVE ENEMIES______(3)..CHECK COLLISION______(4)..GENERATE ENEMIES______(5)..PRINT
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
      }

      // ..(2.a)..
      game->moveBullet ();
      // ..(2.b)..
      game->moveEnemies ();

      // ..(3)..
      game->checkCollision ();
      
      // ..(4)..
      if ((rand() % 10759)==0)
	 // I create new enemy
	 game->addEnemy (((rand ())%COLS), 1, ((rand())%2) /*((rand())%4)*/);
      

      // ..(5).. print on stdscr and refresh
      game->print ();
      direction=0;
      refresh ();
   }


   //napms(5000);

   endwin ();
   return 0;
}
