/** \file Components.h
 * \brief Header file for the library of project "Space Invaders"
 * \author Luca Di Mauro
 *
 * In this header file are specifications of elememts of game: cannon, bullets and enemies (with subclasses).
 */


#ifndef _COMPONENTS_H
#define _COMPONENTS_H

#include <ctime>



/** \brief Speed of bullets shooted by cannon */
const int BULLET_SPEED= 100000;
/** \brief Start life of spacecrafts */
const int SPACECRAFT_LIFE= 3;
/** \brief Speed of spacecrafts */
const int SPACECRAFT_SPEED= 1.0;
/** \brief Start life of big spacecrafts */
const int BIGSPACECRAFT_LIFE= 7;
/** \brief Speed of big spacecrafts */
const int BIGSPACECRAFT_SPEED= 1.7;
/** \brief Start life of asteroids */
const int ASTEROID_LIFE= 10;
/** \brief Speed of asteroids */
const int ASTEROID_SPEED= 0.5;
/** \brief Start life of rocks */
const int ROCK_LIFE= 5;
/** \brief Speed of rocks */
const int ROCK_SPEED= 2.0;



class cannon_t;
/* *** */
class bullist_t;
class bullet_t;
/* *** */
class enelist_t;
class enemy_t;



/** \brief Class of cannon which you shoot to spacecrafts */
class cannon_t
{
   private:
      /** \brief The abscissa where is placed the cannon */
      int x;
      /** \brief The ordinate where is placed the cannon */
      int y;
      /** \brief Variable to indicate the maximum limit until cannon can move */
      int maxLimit;
      /** \brief Variable to indicate the minimum limit until cannon can move */
      int minLimit;
      /** \brief Variable to indicate cannon's heigth */
      int heigth;

   public:
      /** \brief Constructor
       * \param x Abscisse where is placed cannon
       * \param y Ordinate where is placed cannon
       * \param maxLimit Value of field maxLimit
       * \param minLimit Value of field minLimit
       * \param heigth Heigth of cannon
       */
      cannon_t (int, int, int, int, int);
      /** \brief Destroyer */
      ~cannon_t ();

      /** \brief Method to get abscisse where is placed the cannon
       * \return x
       */
      int getX ();

      /** \brief Method to get ordinate where is placed the cannon
       * \return y
       */
      int getY ();

      /** \brief Method to move left the cannon
       * \param off Offset which cannon have to move
       * 
       * \return TRUE If ok
       * \return FALSE If it cannot move
       */
      bool moveLeft (int);

      /** \brief Method to move right the cannon
       * \param off Offset which cannon have to move
       * 
       * \return TRUE If ok
       * \return FALSE If it cannot move
       */
      bool moveRight (int);

      /** \brief Method to shoot ONE bullet
       * \param prec Previous bullet in list
       * \param next Next bullet in list
       * 
       * \return bull If it could shoot
       * \return NULL If it couldn't shoot
       */
      bullet_t *shoot (bullet_t *, bullet_t *);

      /** \brief Method to shoot ONE bullet
       * \return bull If it could shoot
       * \return NULL If it couldn't shoot
       */
      bullet_t *shoot ();
};





/** \brief Class that manages the list of bullets shooted by cannon (BULLETS IN LIST HAS SAME ABSCISSE) */
class bullist_t
{
   private:
      /** \brief Beginning of list */
      bullet_t *start;
      /** \brief Emd of list*/
      bullet_t *end;
      /** \brief Pointer that acts as iterator on list */
      bullet_t *iter;
      /** \brief Variable wich indicating that list is modified (some bullet has moved) */
      bool modified;
      
   public:
      /** \brief Constructor */
      bullist_t ();
      /** \brief Destroyer */
      ~bullist_t ();

      /** \brief Add a bullet in the list (at the end of list)
       * \param px Abscisse of bullet
       * \param py Ordinate of bullet
       * 
       * \return TRUE If ok
       * \return FALSE If there is an error
       */
      bool addBullet (int px, int py);

      /** \brief Remove the first list's element
       * \return TRUE If ok
       * \return FALSE if there is an error
       */
      bool removeFirst ();

      /** \brief Remove the last list's element
       * \return TRIE If ok
       * \return FALSE If there is an error
       */
      bool removeLast ();

      /** \brief Move upward bullets. */
      void moveBullet ();

      /** \brief Move to beginning the iterator.
       * \return start Pointer to first element in the list
       * \return NULL If there aren't elements in the list
       */
      bullet_t *begin ();

      /** \brief Advances the iterator to next element and return the pointer to this element
       * \return iter Pointer to next element in the list
       * \return NULL If is reached end of list
       */
      bullet_t *next ();

      /** \brief The method return object pointed by "iter"
       * \return iter If the pointer is pointing to an object
       * \return NULL Otherwiswe
       */
      bullet_t *getIter ();

      /** \brief Method to delete bullet pointed by "iter"
       * \return true If ok
       * \return false Otherwise (e.g. iter==NULL)
       */
      bool deleteThis ();

      /** \brief Delete a bullet from BULLIST
       * \param pX Abscisse of point
       * \param pY Ordinate of point
       *
       * \return TRUE If it's deleted
       * \return FALSE Otherwise
       */
      bool deleteBullet (int , int);

      /** \brief Method to know if list was modified from last visit (bullets have moved)
       * (The method set the variable modified to false if modified is true)
       * \return true If the list was modified
       * \return false Otherwise
       */
      bool isModified ();
};





/** \brief Class of bullets shooted */
class bullet_t
{
   private:
      /** \brief Abscissa where is placed the bullet */
      int x;
      /** \brief Ordinate where is placed the bullet */
      int y;
      /** \brief Pointer to next bullet */
      bullet_t *next;
      /** \brief Pointer to previous bullet */
      bullet_t *prev;
      /** \brief Start time of bullet's life */
      clock_t timeStart;
      
   public:
      /** \brief Constructor */
      bullet_t (int, int, bullet_t *, bullet_t *);
      /** \brief Destroyer */
      ~bullet_t ();
      
      /** \brief Return the next element's (another bullet) address or NULL*/
      bullet_t *getNext ();

      /** \brief Return the previous element's (another bullet) address or NULL*/
      bullet_t *getPrev ();

      /** \brief Return field x of the object
       * \return x Abscissa of bullet
       */
      int getX ();

      /** \brief Return field y of the object
       * \return y Ordinate of bullet
       */
      int getY ();

      /** \brief Set the field next
       * \param n
       */
      void setNext (bullet_t *);

      /** \brief Set the field prev
       * \param p
       */
       void setPrev (bullet_t *);

      /** \brief Move the bullet upward.
       * If the bullet has reached end of screen and it isn't the last or the first, it is removed.
       * 
       * \return true If the bullet was moved
       * \return false Otherwse
       */
      bool move ();
};






// ** ******* ** //
// ** ENEMIES ** //
// ** ******* ** //



/** \brief Class that manages list of enemies in game (ENEMIES IN LIST HAS THE SAME ABSCISSE) */
class enelist_t
{
   private:
      /** \brief Pointer to beginning of list */
      enemy_t *start;
      /** \brief Pointer to end of list */
      enemy_t *end;
      /** \brief Pointer that acts as iterator */
      enemy_t *iter;
       /** \brief Variable wich indicating that list is modified (some enemies has moved) */
      bool modified;

      public:
      /** \brief Constructor */
      enelist_t ();
      /** \brief Destroyer */
      ~enelist_t ();


      /** \brief Method to insert enemy in list (at the end of list)
       * \param px Abscisse of enemy
       * \param py Ordinate of enemy
       * \param type Type of enemy: 0_bigSpacecraft, 1_spacecraft, 2_asteroid, 3_rock
       *
       * \return true If enemy was added in list
       * \return false Otherwise
       */
      bool addEnemy (int px, int py, int type);

      /** \brief Remove the first list's element
       * \return TRUE If ok
       * \return FALSE if there is an error
       */
      bool removeFirst ();

      /** \brief Remove the last list's element
       * \return TRIE If ok
       * \return FALSE If there is an error
       */
      bool removeLast ();

      /** \brief Move downward enemies. */
      void moveEnemies ();

      /** \brief Move to beginning the iterator
       * \return start Pointer to first element in the list
       * \return NULL If there aren't elements in the list
       */
      enemy_t *begin ();

      /** \brief Advances the iterator to next element and return the pointer to this element
       * \return iter Pointer to next element in the list
       * \return NULL If is reached end of list
       */
      enemy_t *next ();

      /** \brief The method return object pointed by "iter"
       * \return iter If the pointer is pointing to an object
       * \return NULL Otherwiswe
       */
      enemy_t *getIter ();

      /** \brief Method to delete bullet pointed by "iter"
       * \return true If ok
       * \return false Otherwise (e.g. iter==NULL)
       */
      bool deleteThis ();

      /** \brief Delete an enemy from enelist
       * \param pX Abscisse of point
       * \param pY Ordinate of point
       *
       * \return true If it's deleted
       * \return false Otherwise
       */
      bool deleteEnemy (int pX, int pY);

      /** \brief Method to know if list was modified from last visit (enemies have moved)
       * (The method set the variable modified to false if modified is true)
       * \return true If the list was modified
       * \return false Otherwise
       */
      bool isModified ();
} ;





/** \brief Class for the whole of different enemies */
class enemy_t
{
   private:
      /** \brief Abscissa where is placed this enemy */
      int x;
      /** \brief Ordinate where is placed this enemy */
      int y;
      /** \brief Pointer to previous element in list */
      enemy_t *prev;
      /** \brief Pointer to next element in list */
      enemy_t *next;
      /** \brief Start time of enemy's life */
      clock_t timeStart;
      /** \brief The enemy's life */
      int life;
      /** \brief Pointer to function thath specifics bheaviour of this enemy */
      bool (*bheaviour) (clock_t *, int *);

      /** \brief Bheaavior of bigSpacecraft */
      static bool bigSpacecraft (clock_t *, int *);
      /** \brief bheaviour of spacecraft */
      static bool spacecraft (clock_t *, int *);
      /** \brief bheaviour of asteroid */
      static bool asteroid (clock_t *, int *);
      /** \brief bheaviour of rock */
      static bool rock (clock_t *, int *);
   
   public:
      /** \brief Constructor
       * \param px Abscisse of enemy
       * \param py Ordinate of enemy
       * \param prev Pointer to previous enemy in list
       * \param next Pointer to next enemy in list
       * \param type Type of enemy (0_big spacecraft  1_spacecraft  2_asteroid  3_rock)
       */
      enemy_t (int px, int py, enemy_t *prev, enemy_t *next, int type);
      /** \brief Destroyer */
      ~enemy_t ();

      /** \brief Move the enemy upward.
       * If the enemy has reached end of screen and it isn't the last or the first, it is removed.
       * 
       * \return true If the bullet was moved
       * \return false Otherwse
       */
      bool move ();

      /** \brief Function to check if enemy is die */
      bool isDie () ;

      /** \brief Return the next element's (another enemy) address or NULL*/
      enemy_t *getNext ();

      /** \brief Return the previous element's (another enemy) address or NULL*/
      enemy_t *getPrev ();

      /** \brief Return field x of the object
       * \return x Abscissa of bullet
       */
      int getX ();

      /** \brief Return field y of the object
       * \return y Ordinate of bullet
       */
      int getY ();

      /** \brief Set the field next
       * \param next New value of pointer next
       */
      void setNext (enemy_t *);

      /** \brief Set the field prev
       * \param prev New value of poiner prev
       */
      void setPrev (enemy_t *);

      /** \brief Decrease life of dec PV
       * \param dec Life which have to decrease
       *
       * \return true If life==0 (is died)
       * \retru nfalse Otherwise
       */
      bool decreaseLife (int dec);
};


#endif
