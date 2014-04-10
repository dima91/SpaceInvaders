/**
 * \file enemy.cpp
 * \brief Source file of abstract class enemy_t
 * \author Luca Di Mauro
 */

#include "./Components.h"
/* *** */
/* *** */
/* *** */
enemy_t::enemy_t (int px, int py, enemy_t *prev, enemy_t *next, int type)
{
   x= px;
   y= py;

   this->prev=prev;
   this->next=next;

   timeStart= clock ();

   if (type==0)
   {
      bheaviour= &bigSpacecraft;
      life= BIGSPACECRAFT_LIFE;
   }
   else if (type==1)
   {
      bheaviour= &spacecraft;
      life= SPACECRAFT_LIFE;
   }
   else if (type==2)
   {
      bheaviour= &asteroid;
      life= ASTEROID_LIFE;
   }
   else
   {
      bheaviour= &rock;
      life= ROCK_SPEED;
   }

   this->type= type;
}
/* *** */
/* *** */
/* *** */
enemy_t::~enemy_t ()
{
   if (prev!=NULL)
      prev->setNext (next);

   if (next!=NULL)
      next->setPrev (prev);
}
/* *** */
/* *** */
/* *** */
bool enemy_t::isDie ()
{
   if (life>0)
      return false;

   return true;
}
/* *** */
/* *** */
/* *** */
enemy_t *enemy_t::getNext ()
{
   return next;
}
/* *** */
/* *** */
/* *** */
enemy_t *enemy_t::getPrev ()
{
   return prev;
}
/* *** */
/* *** */
/* *** */
int enemy_t::getX ()
{
   return x;
}
/* *** */
/* *** */
/* *** */
int enemy_t::getY ()
{
   return y;
}
/* *** */
/* *** */
/* *** */
void enemy_t::setNext (enemy_t *next)
{
   this->next=next;
}
/* *** */
/* *** */
/* *** */
void enemy_t::setPrev (enemy_t *prev)
{
   this->prev= prev;
}
/* *** */
/* *** */
/* *** */
bool enemy_t::move ()
{
   bool ret= false;

   // Check if there is another bullet after it
   if (next!=NULL)
      ret= next->move ();

   if (ret)
   {
      this->bheaviour (&timeStart, &y);
      return true;
   }
   else
   {
      ret= this->bheaviour (&timeStart, &y);
      return ret;
   }
}
/* *** */
/* *** */
/* *** */
bool enemy_t::decreaseLife (int dec)
{
   this->life=this->life -dec;

   if (this->life>0)
      return false;

   return true;
}
/* *** */
/* *** */
/* *** */
int enemy_t::getType ()
{
   return type;
}








/*
   // Calculates the time spent from last check
   timeTmp= clock ();
   diff= ((double) timeTmp - (double) timeStart);

   // Check if it have to move
   if (diff>= (double) BULLET_SPEED)
   {
      timeStart= timeTmp;
      y--;

      return true;
   }

   return ret;;
*/



// BHEAVIOURS
bool enemy_t::bigSpacecraft (clock_t *st, int *y)
{
   clock_t timeStart= *st, timeTmp;
   double diff=0;

   // Calculates the time spent from last check
   timeTmp= clock ();
   diff= (double) timeTmp - (double) timeStart;
   diff= diff/CLOCKS_PER_SEC;

   // Check if it have to move
   if (diff>= (double) BIGSPACECRAFT_SPEED)
   {
      *st= timeTmp;
      *y= *y+1;

      return true;
   }

   return false;
}
/* *** */
/* *** */
/* *** */
bool enemy_t::spacecraft (clock_t *st, int *y)
{
   clock_t timeStart= *st, timeTmp;
   double diff=0;

   // Calculates the time spent from last check
   timeTmp= clock ();
   diff= (double) timeTmp - (double) timeStart;
   diff= diff/CLOCKS_PER_SEC;

   // Check if it have to move
   if (diff>= (double) SPACECRAFT_SPEED)
   {
      *st= timeTmp;
      *y= *y+1;

      return true;
   }

   return false;
}
/* *** */
/* *** */
/* *** */
bool enemy_t::asteroid (clock_t *st, int *y)
{
   return false;
}
/* *** */
/* *** */
/* *** */
bool enemy_t::rock (clock_t *st, int *y)
{
   return false;
}
