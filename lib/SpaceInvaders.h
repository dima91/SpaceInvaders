/**
 * \file SpaceInvaders.h
 * \brief Header file for the library of project "Space Invaders"
 * \author Luca Di Mauro
 */


#ifndef _SPACEINVADERS_H
#define _SPACEINVADERS_H

#include <ncurses.h>
#include <ctime>
#include "./Components.h"


/** \brief Offset of cannon's left side from focus */
#define OFF_SX 1
/** \brief Offste of cann's right side from focus */
#define OFF_DX 1




class game_t;



/** \brief Class to manage easily the game place and graphics representation of components.
 * This class manages cannon, list of bullets shooted by cannon, aìenemies and their bheaviour.
 * Object of type game_t also knows sizes of components that are on the screen.
 * Does Everything
 */
class game_t
{
   private:
      /** \brief Pointer to cannon **/
      cannon_t *cannon;
      /** \brief Array of pointer to bullist, ordered by abscisse, which, in turn, manages bullets shooted by cannon */
      bullist_t **bullist;
      /** \brief Array of pointer to enelist, ordered by abscisse, which, in turn, manages enemies */
      enelist_t **enelist;
      /** \brief Number of screen's columns [0, nCol-1] */
      int nCol;
      /** \brief Number of screen's lines [0, nLin-1] */
      int nLin;
      

   public:
      /** \brief Constructor
       * \param col Number of screen's columns
       * \param lin Number of screen's lines
       * \param posx Start bscisse of cannon
       * \param posy Start ordinate of cannon
       * \param h Cannon's heigth
       */
      game_t (int, int, int, int, int);
      /** \brief Destroyer */
      ~game_t ();

      /** \brief This method deals to print on cuscr cannon bullets and enemies
       */
      void print ();

      /** \brief Move left cannon
       * \param off Offset which cannon have to move
       *
       * \return true If ok
       * \return false Otherwise (e.g. cannon reached left side of screen)
       */
      bool moveLeft (int);

      /** \brief Move right cannon
       * \param off Offset which cannon have to move
       *
       * \return true If ok
       * \return false Otherwise (e.g. cannon reached right side of screen)
       */
      bool moveRight (int);

      /** \brief Print initial message */
      void startMessage ();

      /** \brief Shoot a bullet */
       bool shoot ();

      /** \brief Move upward bullets */
      void moveBullet ();

      /** \brief Move downward enemies */
      void moveEnemies ();

      /** \brief Check collision between bullets and enemies (check if first elements of bullist and enelist (with same abscisse) collide) */
      bool checkCollision ();

      /** \brief Add an enemy to enelist
       * \param px Abscisse of enemy
       * \param py Ordinate of enemy
       * \param type Type of enemy: 0_bigSpacecraft, 1_spacecraft, 2_asteroid, 3_rock
       *
       * \return true If enemy was added
       * \return false Otherwise
       */
      bool addEnemy (int px, int py, int type);
};


#endif
