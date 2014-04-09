/**
 * \file cannon.cpp
 * \brief Source file of class cannon_t
 * \author Luca Di Mauro
 */

#include "./Components.h"
/* *** */
/* *** */
/* *** */
cannon_t::cannon_t (int x, int y, int maxLimit, int minLimit, int heigth)
{
   this->x= x;
   this->y= y;

   this->heigth= heigth;

   this->maxLimit= maxLimit;
   this->minLimit= minLimit;
}
/* *** */
/* *** */
/* *** */
cannon_t::~cannon_t ()
{
}
/* *** */
/* *** */
/* *** */
bool cannon_t::moveLeft (int off)
{
   if ((x-off)<(this->minLimit))
      return false;

   x-=off;
   return true;
}
/* *** */
/* *** */
/* *** */
bool cannon_t::moveRight (int off)
{
   if ((x+off)>=(this->maxLimit))
      return false;

   x+=off;
   return true;
}
/* *** */
/* *** */
/* *** */
bullet_t *cannon_t::shoot (bullet_t *prec, bullet_t *next)
{
   return (new bullet_t (this->x, (this->y)-(heigth), prec, next));
}
/* *** */
/* *** */
/* *** */
bullet_t *cannon_t::shoot ()
{
   return (new bullet_t(this->x, (this->y)-(heigth), NULL, NULL));
}
/* *** */
/* *** */
/* *** */
int cannon_t::getX ()
{
   return x;
}
/* *** */
/* *** */
/* *** */
int cannon_t::getY ()
{
   return y;
}
