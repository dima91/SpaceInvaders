/**
 * \file enelist.cpp
 * \brief Source file of class enelist_t
 * \author Luca Di Mauro
 */

#include "./Components.h"
/* *** */
/* *** */
/* *** */
enelist_t::enelist_t ()
{
   start=NULL;
   end=NULL;

   iter= NULL;

   modified= false;
}    
/* *** */
/* *** */
/* *** */
enelist_t::~enelist_t ()
{
   enemy_t *app0=start, *app1=NULL;

   while (app0!=NULL)
   {
      app1=app0->getNext ();
      delete (app0);
      app0=app1;
   }
}
/* *** */
/* *** */
/* *** */
bool enelist_t::addEnemy (int px, int py, int type)
{
   enemy_t *N= new enemy_t (px, py, NULL, NULL, type);

   // List is empty
   if (start==NULL)
   {
      start= N;
      end= start;

      N->setPrev (NULL);
      N->setNext (NULL);

      return true;
   }

   // I insert enemy at the end of list
   end->setNext (N);
   N->setPrev (end);
   end=N;

   return true;
}
/* *** */
/* *** */
/* *** */
bool enelist_t::removeFirst ()
{
   enemy_t *app=NULL;

   if (start==NULL)
      return false;

   // The list has one element
   if ((start->getNext ())==NULL)
   {
      delete (start);

      start=NULL;
      end=NULL;

      return true;
   }

   app=start;
   start=start->getNext ();
   start->setPrev (NULL);

   delete (app);

   return true;
}
/* *** */
/* *** */
/* *** */
bool enelist_t::removeLast ()
{
   enemy_t *app=NULL;

   if (start==NULL)
      return false;

   // The list has one element
   if ((start->getNext())==NULL)
   {
      delete (start);

      start=NULL;
      end=NULL;

      return true;
   }

   app=end;
   end=end->getPrev ();
   end->setNext (NULL);

   delete (app);

   return true;
}
/* *** */
/* *** */
/* *** */
void enelist_t::moveEnemies ()
{
   // List is empty
   if (start==NULL)
      return ;

   if ((start->move ())==true)
      this->modified= true;
}
/* *** */
/* *** */
/* *** */
enemy_t *enelist_t::begin ()
{
   iter= start;
   return start;
}
/* *** */
/* *** */
/* *** */
enemy_t *enelist_t::next ()
{
   if (iter!=NULL)
      iter= iter->getNext ();

   return iter;
}
/* *** */
/* *** */
/* *** */
enemy_t *enelist_t::getIter ()
{
   return iter;
}
/* *** */
/* *** */
/* *** */
bool enelist_t::deleteThis ()
{
   if (iter==NULL)
      return false;

   if ((iter->getPrev())==NULL)
      return removeFirst ();

   if ((iter->getNext())==NULL)
      return removeLast ();

   delete (iter);

   return true;
}
/* *** */
/* *** */
/* *** */
bool enelist_t::deleteEnemy (int pX, int pY)
{
   enemy_t *app=NULL;

   if ((start->getX())==pX && (start->getY())==pY)
      return removeFirst ();

   if ((end->getX ())==pX && (end->getY())==pY)
      return removeLast ();

   app=start;

   while (app!=NULL && (app->getY ())!=pY)
      app=app->getNext ();

   if (app==NULL)
      return false;

   app->getNext()->setPrev (app->getPrev());
   app->getPrev()->setNext (app->getNext());

   return true;
}
/* *** */
/* *** */
/* *** */
bool enelist_t::isModified ()
{
   if (modified)
   {
      modified=false;
      return true;
   }

   return modified;
}
