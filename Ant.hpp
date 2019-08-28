#include <iostream>
#ifndef ANT_HPP
#define ANT_HPP

#include "Critter.hpp"

class Ant : public Critter
{
private:
  bool isEaten;

public:
  Ant();
  Ant(int, int);
  ~Ant();

  virtual void move(Critter***, int, int);
  virtual void breed(Board &b);

  //print the type of bug (for use in print board function)
  virtual void printType();

  //return a 0 for doodlebug and 1 for ant (for use in movement and eating functions? We may just get rid of this one)
  virtual int returnType();
};
#endif

/* The ants behave according to the following model:
Move: For every time step, the ants randomly move up, down, left, or right. If the neighboring
cell in the selected direction is occupied or would move the ant off the grid, then the ant stays
in the current cell.
Breed: If an ant survives for three time steps (not been eaten by doodlebugs), at the end of the
time step (i.e., after moving) the ant will breed. This is simulated by creating a new ant in an
adjacent (up, down, left, or right) cell that is empty randomly. If the cell that is picked is not empty,
randomly attempt to pick another one.  If there is no empty cell available, no breeding occurs.
Once an offspring is produced, an ant cannot produce an offspring again until it has
survived three more time steps. */
