/**
 * \file bullist.cpp
 * \brief Source file of class bullist_t
 * \author Luca Di Mauro
 */

#include "./Components.h"
/* *** */
/* *** */
/* *** */
bullist_t::bullist_t ()
{
   start=NULL;
   end=NULL;
   iter=NULL;
   modified=false;
}
/* *** */
/* *** */
/* *** */
bullist_t::~bullist_t ()
{
   bullet_t *app=start, *app1=start;

   while (app!=NULL)
   {
      app1= app->getNext ();
      delete (app);
      app=app1;
   }
}
/* *** */
/* *** */
/* *** */
bool bullist_t::addBullet (int px, int py)
{
   bullet_t *app=NULL;

   // The first element
   if (this->start==NULL)
   {
      start= new bullet_t (px, py, NULL, NULL);

      end=start;

      return true;
   }

   // I insert the bullet at the end of list
   app= new bullet_t (px, py, end, NULL);
   end->setNext (app);
   end=app;

   return true;   
}
/* *** */
/* *** */
/* *** */
bool bullist_t::removeFirst ()
{
   bullet_t *app=NULL;

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
   start= start->getNext ();
   start->setPrev (NULL);
   delete (app);

   return true;
}
/* *** */
/* *** */
/* *** */
bool bullist_t::removeLast ()
{
   bullet_t *app=NULL;

   if (end==NULL)
      return false;

   // The list has one element
   if ((start->getNext ())==NULL)
   {
      delete (start);
      start= NULL;
      end= NULL;

      return true;
   }

   app= end;
   end= end->getPrev ();
   end->setNext (NULL);
   delete (app);

   return true;
}
/* *** */
/* *** */
/* *** */
void bullist_t::moveBullet ()
{
   // List is empty
   if (start==NULL)
      return ;

   if ((start->move ())==true)
      this->modified= true;

   // ########################################
   // This command must be deleted?!?!?!?!?!?!
   if ((start->getY ()) <=0)
      removeFirst ();
}
/* *** */
/* *** */
/* *** */
bullet_t *bullist_t::begin ()
{
   iter= start;

   return iter;
}
/* *** */
/* *** */
/* *** */
bullet_t *bullist_t::next ()
{
   if (iter!=NULL)
      iter=iter->getNext ();

   return iter;
}
/* *** */
/* *** */
/* *** */
bullet_t *bullist_t::getIter ()
{
   return iter;
}
/* *** */
/* *** */
/* *** */
bool bullist_t::deleteThis ()
{
   if (iter==NULL)
      return false;

   if ((iter->getPrev ())==NULL)
      return removeFirst ();

   if ((iter->getNext ())==NULL)
      return removeLast ();

   else
      delete (iter);

   return true;
}
/* *** */
/* *** */
/* *** */
bool bullist_t::deleteBullet (int pX, int pY)
{
   bullet_t *app=NULL;

   if ((start->getX())==pX && (start->getY ())==pY)
   {
      removeFirst ();

      return true;
   }
   if ((end->getX())==pX && (start->getY())==pY)
   {
      removeLast ();

      return true;
   }

   while (app!=NULL && (app->getY ())> pY)
      app=app->getNext ();

   if (app==NULL)
      return false;

   delete (app);

   return true;
}
/* *** */
/* *** */
/* *** */
bool bullist_t::isModified ()
{
   if (modified)
   {
      modified=false;
      return true;
   }

   return modified;
}
