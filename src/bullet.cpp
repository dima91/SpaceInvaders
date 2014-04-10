/**
 * \file bullet.cpp
 * \brief Source file of class bullet_t
 * \author Luca Di Mauro
 */
 
#include "./Components.h"
/* *** */
/* *** */
/* *** */
bullet_t::bullet_t (int pX, int pY, bullet_t *pp, bullet_t *pn)
{
   x=pX;
   y=pY;
   
   next=pn;
   prev=pp;

   timeStart= clock ();
}
/* *** */
/* *** */
/* *** */
bullet_t::~bullet_t ()
{
   if (prev!=NULL)
      prev->setNext (next);

   if (next!=NULL)
      next->setPrev (prev);
}
/* *** */
/* *** */
/* *** */
bullet_t *bullet_t::getNext ()
{
   return next;
}
/* *** */
/* *** */
/* *** */
bullet_t *bullet_t::getPrev ()
{
   return prev;
}	
/* *** */
/* *** */
/* *** */
int bullet_t::getX ()
{
   return x;
}
/* *** */
/* *** */
/* *** */
int bullet_t::getY ()
{
   return y;
}
/* *** */
/* *** */
/* *** */
bool bullet_t::move ()
{
   clock_t timeTmp;
   double diff=0;
   bool ret= false;

   // Check if there is another bullet after it
   if (next!=NULL)
      ret= next->move ();

   // Calculates the time spent from last check
   timeTmp= clock ();
   diff= ((double) timeTmp - (double) timeStart);
   diff= diff/CLOCKS_PER_SEC;

   // Check if it have to move
   if (diff>= (double) BULLET_SPEED)
   {
      timeStart= timeTmp;
      y--;

      return true;
   }

   return ret;
}
/* *** */
/* *** */
/* *** */
void bullet_t::setNext (bullet_t *n)
{
   next=n;
}
/* *** */
/* *** */
/* *** */
void bullet_t::setPrev (bullet_t *p)
{
   prev=p;
}
