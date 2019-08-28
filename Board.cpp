/*********************************************************************
** Program name: Board.cpp
** Author: Group 10
** Date: November 3, 2018
** Description: This is the class defines the Board class contains functions to create Critterboard, move critter, breed critter.  
*Board class controls controls Critters and uses Critter functions.
*********************************************************************/
#include "Ant.hpp"
#include "Board.hpp"
#include "Doodlebug.hpp"

using std::cout;
using std::endl;
using std::rand;

/* private member variables of the class
  int numRows;
  int numCols;
  int numAnts;
  int numDoodlebugs;
  Critter*** bugBoard;
*/

//default constructor, sets private members to standard values and creates board
Board::Board() {
  numRows = 20;
  numCols = 20;
  numAnts = 100;
  numDoodlebugs = 5;

  //dynamically allocate the bugBoard
  bugBoard = new Critter**[numRows];
  for (int i = 0; i < numRows; i++) {
    bugBoard[i] = new Critter*[numCols];
  }

  //Set the pointers to null
  for (int i = 0; i < numRows; i++) {
      for (int j = 0; j < numCols; j++) {
        bugBoard[i][j] = NULL;
      }
  }

  //place the ants
  for (int i = 0; i < numAnts; i++) {
    this->placeBug(1); //1 indicates ant
  }

  //place the doodlebugs
  for (int i = 0; i < numDoodlebugs; i++) {
    this->placeBug(0); //0 indicates doodlebug
  }
}

//creates the initial board with input rows, columns, ants, and doodlebugs
Board::Board(int row, int col, int ant, int doodlebug) {
  numRows = row;
  numCols = col;
  numAnts = ant;
  numDoodlebugs = doodlebug;

  //dynamically allocate the bugBoard
  bugBoard = new Critter**[numRows];
  for (int i = 0; i < numRows; i++) {
    bugBoard[i] = new Critter*[numCols];
  }

  //Set the pointers to null
  for (int i = 0; i < numRows; i++) {
      for (int j = 0; j < numCols; j++) {
        bugBoard[i][j] = NULL;
      }
  }

  //place the ants
  for (int i = 0; i < numAnts; i++) {
    this->placeBug(1);
  }

  //place the doodlebugs
  for (int i = 0; i < numDoodlebugs; i++) {
    this->placeBug(0);
  }
}

Board::~Board() {
  cleanBoard();
}

//places a bug (0 for input for doodlebug, 1 for ant)
void Board::placeBug(int species) {
  int eligibleSpaces = 0;
  int bugSpace;

  //Determine how many eligible spaces are left on board
  for (int i = 0; i < numRows; i++)
      for (int j = 0; j < numCols; j++) {
        if (bugBoard[i][j] == NULL) {
          eligibleSpaces += 1;
      }
  }

  //Determine which eligible space to place doodlebug
  bugSpace = rand() % eligibleSpaces + 1;

  //reset eligibleSpace counter
  eligibleSpaces = 0;

  //Find eligible space, create doodlebug
  for (int i = 0; i < numRows; i++) {
      for (int j = 0; j < numCols; j++) {
        if (bugBoard[i][j] == NULL) {
          eligibleSpaces += 1;
          if (eligibleSpaces == bugSpace) {
            if (species == 0) {
              bugBoard[i][j] = new Doodlebug(i, j);
            }
            else if (species == 1) {
              bugBoard[i][j] = new Ant(i, j);
            }
            else {
              cout << "Invalid species call to placeBug. Expected '0' or '1'. Got" << species << ".\n";
            }
          }
        }
     }
  }
}

//passes board to doodlebug object, changes row and col of object, copies object data
//to new row and col, deletes old data.
void Board::moveDoodlebugs() {
  int tempRow;
  int tempCol;

  //loop through the board
  for (int i = 0; i < numRows; i++) {
    for (int j = 0; j < numCols; j++) {

      //check if we're looking at a doodlebug
      if (bugBoard[i][j] != NULL) {
        if (bugBoard[i][j]->returnType() == 0 && bugBoard[i][j]->getHasMoved() == false) { //need a hasMoved clause here

          //call move function for doodlebug
          bugBoard[i][j]->move(bugBoard, numRows, numCols);

          //set temp row and col to new doodlebug location
          tempRow = bugBoard[i][j]->getRow();
          tempCol = bugBoard[i][j]->getCol();

          //if the doodlebug is eating an ant, delete the ant
          if (bugBoard[tempRow][tempCol] != NULL) {
            if (bugBoard[tempRow][tempCol]->returnType() == 1) {
              delete bugBoard[tempRow][tempCol];
			  bugBoard[tempRow][tempCol] = NULL;
            }
          }

          //copy over doodlebug if it moved
		  if (tempRow != i || tempCol != j) {

			  //bugBoard[tempRow][tempCol] = new Doodlebug(tempRow, tempCol);
			  bugBoard[tempRow][tempCol] = bugBoard[i][j];

			  //delete old doodlebug
			  bugBoard[i][j] = NULL;
		  }
        }
      }
    }
  }
}

void Board::breedDoodlebugs() {
  for (int i = 0; i < numRows; i++) {
    for (int j = 0; j < numCols; j++) {
      if (bugBoard[i][j] != NULL) {
        if (bugBoard[i][j]->returnType() == 0) {
          bugBoard[i][j]->breed(*this);
        }
      }
    }
  }
}

void Board::moveAnts() {
  int tempRow;
  int tempCol;

  for (int i = 0; i < numRows; i++) {
    for (int j = 0; j < numCols; j++) {

      //check if we're looking at an ant
      if (bugBoard[i][j]) {
        if (bugBoard[i][j]->returnType() == 1 && bugBoard[i][j]->getHasMoved() == false) {

          //call move function for ant
          bugBoard[i][j]->move(bugBoard, numRows, numCols);

          //set temp row and col to new ant location
          tempRow = bugBoard[i][j]->getRow();
          tempCol = bugBoard[i][j]->getCol();

	         //copy over ant
          if (tempRow != i || tempCol != j) {
            bugBoard[tempRow][tempCol] = bugBoard[i][j];

            //null old location
            bugBoard[i][j] = NULL;
	  }
        }
      }
    }
  }
}

void Board::breedAnts() {
  for (int i = 0; i < numRows; i++) {
    for (int j = 0; j < numCols; j++) {
      if (bugBoard[i][j] != NULL) {
        if (bugBoard[i][j]->returnType() == 1) {
          bugBoard[i][j]->breed(*this);
        }
      }
    }
  }
}

void Board::printBoard() {
    //print top border
    for (int i = 0; i < numRows + 2; i++) {
      cout << "-";
    }

    cout << endl;

    for (int i = 0; i < numRows; i++) {

      //print side border
      cout << "|";

      //loop through columns
      for (int j = 0; j < numCols; j++) {
        if (bugBoard[i][j] == NULL) {
          cout << " ";
        }
        else if (bugBoard[i][j]->returnType() == 0) {
          cout << "X";
        }
        else if (bugBoard[i][j]->returnType() == 1) {
          cout << "O";
        }
        else {
          cout << "Z"; //debug character
        }
      }

      //print side border, move to new line
      cout << "|" << endl;
    }

    //print bottom border
    for (int i = 0; i < numRows + 2; i++) {
      cout << "-";
    }
    cout << endl;
}

Critter* Board::getContents(int row, int col) {
  return bugBoard[row][col];
}

void Board::setContents(Critter* newCritter, int row, int col) {
  bugBoard[row][col] = newCritter;
}

int Board::getNumCols() {
  return numCols;
}

int Board::getNumRows() {
  return numRows;
}

void Board::starve() {
 //loop through the board
 for (int i = 0; i < numRows; i++) {
   for (int j = 0; j < numCols; j++) {

     //check if we're looking at a doodlebug
     if (bugBoard[i][j] != NULL) {
       if (bugBoard[i][j]->returnType() == 0) {

         //check whether the doodlebug starved, delete if true
         if (bugBoard[i][j]->starve() == true) {
           delete bugBoard[i][j];
           bugBoard[i][j] = NULL;
         }
       }
     }
   }
 }
}

//deletes the dynamic data
void Board::cleanBoard() {

  for (int i = 0; i < numRows; i++) {

   for (int j = 0; j < numCols; j++) {
       delete bugBoard[i][j];
       bugBoard[i][j] = NULL;
     }
     delete[] bugBoard[i];
     bugBoard[i] = NULL;
   }

  delete [] bugBoard;
  bugBoard = NULL;

}
