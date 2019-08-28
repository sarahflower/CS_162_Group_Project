/*********************************************************************
** Program name: Ant.cpp
** Author: Group 10
** Date: November 3, 2018
** Description: This is the class defines the Ant class and inherits Critter Class.
*Class contains functions for the Ant to Breed and Move.
*********************************************************************/
#include "Ant.hpp"
#include "Board.hpp"
// Default constructor for Ant(), set variables to default values
Ant::Ant()
{
    row = -1;
    col = -1;
    age = 0;
    breedingPending = false;
    isEaten = false;
    hasMoved = false;
}

// Ant constructor
Ant::Ant(int r, int c)
{
    row = r;
    col = c;
    age = 0;
    breedingPending = false;
    isEaten = false;
    hasMoved = false;
}

// Ant Destructor
Ant::~Ant()
{
    // Destructor
}

/*********************************************************************
** Ant::move() moves the ants randomly move up, down, left, or right.
** If the neighboring cell in the selected direction is occupied or
** would move the ant off the grid, then the ant stays in the current cell.
*********************************************************************/
void Ant::move(Critter*** board, int maxRow, int maxCol)
{
	// 1 = RIGHT, 2 = LEFT, 3 = UP, 4 = DOWN
	int direction = rand() % 4 + 1;

	switch (direction)
	{
	case 1:     // Ant moving right
		if (col + 1 < maxCol)
		{
			if (board[row][col+1] == NULL)
			{
				col += 1;
				age++;
			}
		}
		break;

	case 2:     // Ant moving left
		if (col - 1 >= 0)
		{
			if (board[row][ col - 1] == NULL)
			{
				col -= 1;
				age++;
			}
		}
		break;

	case 3:     // Ant moving up
		if (row - 1 >= 0)
		{
			if (board[row - 1][ col] == NULL)
			{
				row -= 1;
				age++;
			}
		}
		break;

	case 4:     // Ant moving down
		if (row + 1 < maxRow)
		{
			if (board[row + 1][ col] == NULL)
			{
				row += 1;
				age++;
			}
		}
		break;
	}
  //prevent the Ant from moving multiple times as we loop through the array
  hasMoved = true;

}




//print the type of bug (for use in print board function)
void Ant::printType() {
  std::cout << "ant";
}

  //return a 0 for doodlebug and 1 for ant (for use in movement and eating functions? We may just get rid of this one)
int Ant::returnType() {
  return 1;
}

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

void Ant::breed(Board &b) {


  // Booleans to determine if the surrounding cells are occupied and if a new
  // Ant could be placed successfully in a cell.
  bool canBreed = false, hasBred = false;
  // Integer to represent a direction on the board: 1 for north, 2 for east, 3
  // for south, 4 for west.
  int direction;
  // A pointer to a Critter that breeding will place on the board
  Critter* babyAnt = NULL;

  // Attempt to breed a Ant into an empty cell only if the Ant's age
  // is not 0 and divisible by 8, or if the Ant was previously able to
  // breed, but no adjacent cells were available during that time step.
  if ( (age > 0 && age % 3 == 0) || breedingPending) {

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
      // on the board that is also empty before placing a new Ant via
      // setContents. Loop until we can place a new Ant on the board.
      do {
        direction = rand() % 4 + 1;

        switch (direction) {

          case 1:   if ( row != 0 && !b.getContents(row - 1, col) ) {
                      babyAnt = new Ant(row - 1, col);
                      b.setContents(babyAnt, row - 1, col);
                      hasBred = true;
                    }
                    break;

          case 2:   if ( col != b.getNumCols() - 1 && !b.getContents(row, col + 1) ) {
                      babyAnt = new Ant(row, col + 1);
                      b.setContents(babyAnt, row, col + 1);
                      hasBred = true;
                    }
                    break;

          case 3:   if ( row != b.getNumRows() - 1 && !b.getContents(row + 1, col) ) {
                      babyAnt = new Ant(row + 1, col);
                      b.setContents(babyAnt, row + 1, col);
                      hasBred = true;
                    }
                    break;

          case 4:   if ( col != 0 && !b.getContents(row, col - 1) ) {
                      babyAnt = new Ant(row, col - 1);
                      b.setContents(babyAnt, row, col - 1);
                      hasBred = true;
                    }
                    break;
        }


      } while(!hasBred);

    } else {
      // Set breedingPending to true if we could have bred, but there wasn't an
      // empty cell adjacent to the Ant. We'll try again during the next
      // time step.
      breedingPending = true;
    }


  }

  // Reset the hasMoved boolean so this Ant can perform a move the next
  // time its move function is called.
  hasMoved = false;

}
