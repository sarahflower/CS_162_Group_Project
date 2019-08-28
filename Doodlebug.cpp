/*********************************************************************
** Program name: Doodlebug.cpp
** Author: Group 10
** Date: November 3, 2018
** Description: This is the class defines the Doodlebug class and inherits Critter Class.
* Class contains functions for the Doodlebug to Breed and Move.
*********************************************************************/

/*The doodlebugs behave according to the following model:
Move: For every time step, the doodlebug will firstly try to move to an adjacent cell
containing an ant and eat the ant (you can decide if there are several ants in the adjacent cells,
how the doodlebug will choose to move). If there are no ants in adjacent cells, the doodlebug moves
according to the same rules as the ant.  Note that a doodlebug cannot eat other doodlebugs.
Breed: If a doodlebug survives for eight time steps, at the end of the time step, it will spawn off
a new doodlebug in the same manner as the ant (the Doodlebug will only breed into an empty cell).
Starve: If a doodlebug has not eaten an ant within three time steps, at the end of the third time
step it will starve and die. The doodlebug should then be removed from the grid of cells. */

#include <cstdlib>
#include <iostream>

#include "Doodlebug.hpp"

using std::cout;
using std::endl;
using std::rand;

//Default constructor. Shouldn't be called.
Doodlebug::Doodlebug() {
  row = -1;
  col = -1;
  age = 0;
  breedingPending = false;
  hasMoved = false;
  isStarved = false;
  lastMeal = 0;
  cout << "Error = default doodlebug constructor called. Only overloaded constructor should be called.\n";
}

//Overloaded contstructor
Doodlebug::Doodlebug(int r, int c) {
   row = r;
   col = c;
   age = 0;
   breedingPending = false;
   hasMoved = false;
   isStarved = false;
   lastMeal = 0;
}

//Destructor. Not doing anything special at the moment.
Doodlebug::~Doodlebug() {}

//takes the board, calls the eat function if an ant exists, otherwise changes row and col location of the doodlebug.
//Board function should call row and col to copy bug (ex. Board[Board[old location]->getRow][Board[old location]->getCol] = Board[old location]
void Doodlebug::move(Critter*** board, int maxRow, int maxCol) {
  bool adjacentAnt = false;
  int direction;
  bool validMove = true;

  //set hasMoved to true (it will be reset in breed)
  hasMoved = true;

  //increment age
  this->incrementAge();

  //Check to see if there is an adjacent ant
  if (row != 0) {
    if (board[row - 1][col] != NULL) {
      if (board[row - 1][col]->returnType() == 1) {
        adjacentAnt = true;
      }
    }
  }
  if (row != (maxRow - 1)) { // -1 because board is 0 to numRows - 1
    if (board[row + 1][col] != NULL) {
      if ( board[row + 1][col]->returnType() == 1 ) {
        adjacentAnt = true;
      }
    }
  }
  if (col != 0) {
    if ( board[row][col - 1] != NULL ) {
      if ( board[row][col - 1]->returnType() == 1 ) {
        adjacentAnt = true;
      }
    }
  }
  if (col != (maxCol - 1)) {
    if ( board[row][col + 1] != NULL ) {
      if ( board[row][col + 1]->returnType() == 1 ) {
        adjacentAnt = true;
      }
    }
  }

  //if there is an adjacent ant, call the eat function and eat it
  if (adjacentAnt == true) {
    this->eat(board, maxRow, maxCol);
  }

  //otherwise, look for open spots and take one at random, add 1 to lastMeal
  else {
    //increment last meal
    lastMeal += 1;

    if (lastMeal >= 3) {
      isStarved = true;
    }

    //Pick a direction at random, move if it is valid
    direction = rand() % 4 + 1; //1 for north, 2 for east, 3 for south, 4 for west

    //top row condition
    if (row == 0 && direction == 1) {
    validMove = false;
    }
    //left edge condition
    else if (col == 0 && direction == 4) {
    validMove = false;
    }
    //bottom row condition
    else if ( row == maxRow - 1 && direction == 3) {
    validMove = false;
    }
    //left edge condition
    else if (col == maxCol - 1 && direction == 2) {
    validMove = false;
    }
    //if not an edge case, check for contents already
    else if (direction == 1) {
      if (board[row - 1][col] != NULL) {
        validMove = false;
      }
    }
    else if (direction == 2) {
      if (board[row][col + 1] != NULL) {
        validMove = false;
      }
    }
    else if (direction == 3) {
      if (board[row + 1][col] != NULL) {
        validMove = false;
      }
    }
    else if (direction == 4) {
      if (board[row][col - 1] != NULL) {
        validMove = false;
      }
    }

    if (validMove == true) {
      if (direction == 1) {
        row = row - 1;
	col = col;
      }
      else if (direction == 2) {
        row = row;
	col = col + 1;
      }
      else if (direction == 3) {
        row = row + 1;
	col = col;
      }
      else if (direction == 4) {
        row = row;
	col = col - 1;
      }
    }
  }
}

void Doodlebug::eat(Critter*** board, int maxRow, int maxCol) {
  int eligibleSpots = 0;
  int chosenSpot;

  //Check to see where adjacent ants are, add to eligible spots
  if (row != 0) {
    if (board[row - 1][col] != NULL) {
      if (board[row - 1][col]->returnType() == 1) {
        eligibleSpots += 1;
      }
    }
  }
  if (row != (maxRow - 1)) { // -1 because board is 0 to numRows - 1
    if (board[row + 1][col] != NULL) {
      if ( board[row + 1][col]->returnType() == 1 ) {
        eligibleSpots += 1;
      }
    }
  }
  if (col != 0) {
    if ( board[row][col - 1] != NULL ) {
      if ( board[row][col - 1]->returnType() == 1 ) {
        eligibleSpots += 1;
      }
    }
  }
  if (col != maxCol - 1) {
    if ( board[row][col + 1] != NULL ) {
      if ( board[row][col + 1]->returnType() == 1 ) {
        eligibleSpots += 1;
      }
    }
  }

  chosenSpot = rand() % eligibleSpots + 1;


  //reset eligibleSpots
  eligibleSpots = 0;

  //Find chosen spot, move row and col to it, (the ant will be deleted and this will be moved in board function), reset lastMeal
  if (row != 0) {
    if (board[row - 1][col] != NULL) {
      if (board[row - 1][col]->returnType() == 1) {
        eligibleSpots += 1;
        if (eligibleSpots == chosenSpot) {
	  row = row - 1;
	  col = col;
	  lastMeal = 0;
	}
      }
    }
  }
  if (row != (maxRow - 1)) { // -1 because board is 0 to numRows - 1
    if (board[row + 1][col] != NULL) {
      if ( board[row + 1][col]->returnType() == 1 ) {
        eligibleSpots += 1;
	if (eligibleSpots == chosenSpot) {
	  row = row + 1;
	  col = col;
	  lastMeal = 0;
	}
      }
    }
  }
  if (col != 0) {
    if ( board[row][col - 1] != NULL ) {
      if ( board[row][col - 1]->returnType() == 1 ) {
        eligibleSpots += 1;
	if (eligibleSpots == chosenSpot) {
	  this->row = row;
	  this->col = col - 1;
	  lastMeal = 0;
	}
      }
    }
  }
  if (col != maxCol - 1) {
    if ( board[row][col + 1] != NULL ) {
      if ( board[row][col + 1]->returnType() == 1 ) {
        eligibleSpots += 1;
	if (eligibleSpots == chosenSpot) {
	  row = row;
	  col = col + 1;
	  lastMeal = 0;
	}
      }
    }
  }
}


void Doodlebug::breed(Board &b) {

  // Booleans to determine if the surrounding cells are occupied and if a new
  // Doodlebug could be placed successfully in a cell.
  bool canBreed = false, hasBred = false;
  // Integer to represent a direction on the board: 1 for north, 2 for east, 3
  // for south, 4 for west.
  int direction;
  // A pointer to a Critter that breeding will place on the board
  Critter* babyDoodlebug = NULL;

  // Attempt to breed a Doodlebug into an empty cell only if the Doodlebug's age
  // is not 0 and divisible by 8, or if the Doodlebug was previously able to
  // breed, but no adjacent cells were available during that time step.
  if ( (age > 0 && age % 8 == 0) || breedingPending) {

    if (!canBreed && row != 0) {

      if ( !b.getContents(row - 1, col) ) {
        // There's an available cell to the north.
        canBreed = true;
      }

    }

    if (!canBreed && row != b.getNumRows() - 1) {
      // We haven't found a place to breed yet and
      // there's an available cell to the south.

      if ( !b.getContents(row + 1, col) ) {
        canBreed = true;
      }

    }

    if (!canBreed && col != 0) {
      // we haven't found a place to breed yet and
      // there's an available cell to the west.

      if (!b.getContents(row, col - 1)) {
        canBreed = true;
      }

    }

    if (!canBreed && col != b.getNumCols() - 1) {
      // We haven't found a place to breed yet and
      // there's an available cell to the east.

      if ( !b.getContents(row, col + 1) ) {
        canBreed = true;
      }

    }

    if (canBreed) {
      // Generate a random number, then verify that number corresponds to a cell
      // on the board that is also empty before placing a new Doodlebug via
      // setContents. Loop until we can place a new Doodlebug on the board.
      do {
        direction = rand() % 4 + 1;

        switch (direction) {

          case 1:   if ( row != 0 && !b.getContents(row - 1, col) ) {
                      babyDoodlebug = new Doodlebug(row - 1, col);
                      b.setContents(babyDoodlebug, row - 1, col);
                      hasBred = true;
                    }
                    break;

          case 2:   if ( col != b.getNumCols() - 1 && !b.getContents(row, col + 1) ) {
                      babyDoodlebug = new Doodlebug(row, col + 1);
                      b.setContents(babyDoodlebug, row, col + 1);
                      hasBred = true;
                    }
                    break;

          case 3:   if ( row != b.getNumRows() - 1 && !b.getContents(row + 1, col) ) {
                      babyDoodlebug = new Doodlebug(row + 1, col);
                      b.setContents(babyDoodlebug, row + 1, col);
                      hasBred = true;
                    }
                    break;

          case 4:   if ( col != 0 && !b.getContents(row, col - 1) ) {
                      babyDoodlebug = new Doodlebug(row, col - 1);
                      b.setContents(babyDoodlebug, row, col - 1);
                      hasBred = true;
                    }
                    break;
        }


      } while(!hasBred);

    } else {
      // Set breedingPending to true if we could have bred, but there wasn't an
      // empty cell adjacent to the Doodlebug. We'll try again during the next
      // time step.
      breedingPending = true;
    }


  }

  // Reset the hasMoved boolean so this Doodlebug can perform a move the next
  // time its move function is called.
  hasMoved = false;

}


bool Doodlebug::starve() {
  if (isStarved == true) {
    return true;
  }
  else {
    return false;
  }
}


void Doodlebug::incrementLastMeal() { //probably don't need this anymore, built it into move instead
  lastMeal += 1;
}


int Doodlebug::getLastMeal() {
  return lastMeal;
}


void Doodlebug::setLastMeal(int meal) {
  lastMeal = meal;
}
//print the type of bug (for use in print board function)
void Doodlebug::printType() {
  cout << "doodlebug";
}

  //return a 0 for doodlebug and 1 for ant (for use in movement and eating functions? We may just get rid of this one)
int Doodlebug::returnType() {
  return 0;
}

/*Just here so I can copy paste
class Doodlebug : public Critter
{
private:
  int lastMeal;
  bool isStarved;

public:
  Doodlebug::Doodlebug();
  Doodlebug(int, int); // ints - row and column location of Doodlebug
  ~Doodlebug();
  void move(&Board b) {

  virtual void eat(//add params);
  virtual void breed(//add params);
  void starve();
  void incrementLastMeal();   // lastMeal++
  int getLastMeal();
  void setLastMeal(int);
};
*/
