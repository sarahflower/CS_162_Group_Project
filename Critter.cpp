/*********************************************************************
** Program name: Critter.cpp
** Author: Group 10
** Date: November 3, 2018
** Description: This is the class defines the Critter class which will be inherited by Ant and Doodlebug.
*Class contains virtual functions and functions which Ant and Doodlebug can use.
*********************************************************************/
#include "Critter.hpp"

void Critter::incrementAge() {
  age += 1;
}

int Critter::getAge() {
  return age;
}

void Critter::setAge(int a) {
  age = a;
}

void Critter::setHasMoved(int i) {
  if (i == 0) {
    hasMoved = false;
  } else if (i == 1) {
    hasMoved = true;
  }
}

bool Critter::getHasMoved() {
  return hasMoved;
}

int Critter::getRow() {
  return row;
}

int Critter::getCol() {
  return col;
}

//always returns false because only a doodlebug can starve
bool Critter::starve() {
  return false;
}
