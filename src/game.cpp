/**
 * \file game.cpp
 * \brief Source file of class game_t
 * \author Luca Di Mauro
 */


#include "./SpaceInvaders.h"
#include "./Components.h"
/* *** */
/* *** */
/* *** */
game_t::game_t (int col, int lin, int posx, int posy, int h)
{
   nCol= col;
   nLin= lin;

   cannon= new cannon_t (posx, posy, col-1, -1, h);

   bullist= new bullist_t *[col];
   enelist= new enelist_t *[col];

   for (int i=0;i<col;i++)
   {
      bullist[i]= new bullist_t ();
      enelist [i]= new enelist_t ();
   }
}
/* *** */
/* *** */
/* *** */
game_t::~game_t ()
{
   int i=0;

   delete (this->cannon);

   for (i=0;i<nCol;i++)
   {
      delete (bullist[i]);
      delete (enelist[i]);
   }
}
/* *** */
/* *** */
/* *** */
void game_t::startMessage ()
{
   mvprintw (10, 10, "**************************************************\n");
   mvprintw (11, 10, "*************     SPACE INVADERS     *************\n");
   mvprintw (12, 10, "**************************************************\n");
   mvprintw (13, 10, "****         press 's' to start game          ****\n");
   mvprintw (14, 10, "****         press 'h' to print help          ****\n");
   mvprintw (15, 10, "****            press 'q' to quit             ****\n");
   mvprintw (16, 10, "****                                          ****\n");
   mvprintw (17, 10, "****              powered by dima             ****\n");
   mvprintw (18, 10, "**************************************************\n");

   refresh ();
}
/* *** */
/* *** */
/* *** */
bool game_t::moveLeft (int off)
{   
   if ((cannon->getX()-off-OFF_SX)<0)
      return false;

   return cannon->moveLeft (off);
}
/* *** */
/* *** */
/* *** */
bool game_t::moveRight (int off)
{
   if ((cannon->getX()+off+OFF_DX)>nCol)
      return false;

   return cannon->moveRight (off);
}
/* *** */
/* *** */
/* *** */
void game_t::print ()
{
   int i=0, type;

   // Clean screen
   erase ();

   // Print cannon
   mvprintw (cannon->getY()-1, cannon->getX(), "^");
   mvprintw (cannon->getY(), cannon->getX()-1, "###");

   // Print bullets && enemies
   for (i=0;i<nCol;i++)
   {
      enemy_t *app0=enelist[i]->begin ();
      bullet_t *app1= bullist[i]->begin ();

      while (app1!=NULL || app0!=NULL)
      {
	 if (app0!=NULL)
	 {
	    if (!(app0->isDie ()))
	    {
	       type= app0->getType();
	       if (type==0)
		  mvprintw (app0->getY(), app0->getX(), "B");
	       else if (type==1)
		  mvprintw (app0->getY(), app0->getX(), "s");
	       else if (type==2)
		  mvprintw (app0->getY(), app0->getX(), "A");
	       else if (type==3)
		  mvprintw (app0->getY(), app0->getX(), "+");

	       app0=enelist[i]->next ();
	    }
	 }

	 if (app1!=NULL)
	 {
	    mvprintw (app1->getY(), app1->getX(), "*");
	    app1= bullist[i]->next();
	 }
      }
   }      
}
/* *** */
/* *** */
/* *** */
bool game_t::shoot ()
{
   int i=cannon->getX();
   bullist[i]->addBullet (i, (cannon->getY ())-1/* HEIGHT */-1);
   return true;
}
/* *** */
/* *** */
/* *** */
void game_t::moveBullet ()
{
   int i=0;

   for (i=0;i<nCol;i++)
      bullist[i]->moveBullet ();
}
/* *** */
/* *** */
/* *** */
void game_t::moveEnemies ()
{
   int i=0;

   for (i=0;i<nCol;i++)
   {
      enelist[i]->moveEnemies();
      if (((enelist[i]->begin ()) != NULL) && ((enelist[i]->getIter()->getY())>nLin))
	 enelist[i]->removeFirst ();
   }
}
/* *** */
/* *** */
/* *** */
bool game_t::checkCollision ()
{
   int i=0;
   bool ret=false;

   for (i=0;i<nCol;i++)
   {
      if (bullist[i]->isModified () || enelist[i]->isModified ())
      {
	 // Check if bullet collide with enemy (delete bullet and enemy if its life <=0)
	 if (((enelist[i]->begin ())!= NULL) && ((bullist[i]->begin ())!= NULL) && ((bullist[i]->getIter()->getY()) == (enelist[i]->getIter()->getY())))
	 {
	    bullist[i]->removeFirst ();
	    if (enelist[i]->getIter()->decreaseLife (1))
	    {
	       enelist[i]->removeFirst ();
	    }
	    ret= true;
	 }
      }
   }
   return ret;
}
/* *** */
/* *** */
/* *** */
bool game_t::addEnemy (int px, int py, int type)
{
   return enelist[px]->addEnemy (px, py, type);
}
/* *** */
/* *** */
/* *** */
bool game_t::checkCollision (int px, int py)
{
   enemy_t *app= enelist[px]->begin ();

   while (app!=NULL && (app->getY () > py))
      app= enelist[px]->next ();

   if (app!=NULL && app->getY () == py)
      return true;

   return false;
}
/* *** */
/* *** */
/* *** */
bool game_t::checkCannonCollision ()
{
   int x= cannon->getX();
   int y= cannon->getY();

   if ((checkCollision (x-1, y)) || (checkCollision (x, y)) || (checkCollision (x+1, y)) || (checkCollision (x, y-1)))
      return true;

   return false;
}
