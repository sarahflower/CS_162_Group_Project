#ifndef BOARD_HPP
#define BOARD_HPP

class Critter;

class Board {

  private:
    int numRows;
    int numCols;
    int numAnts;
    int numDoodlebugs;
    Critter*** bugBoard;

  public:
    Board();

    Board(int row, int col, int ant, int doodlebug);

    ~Board();

    void placeDoodlebug();

    void placeAnts();

    void placeBug(int species);

    void moveDoodlebugs();

    void breedDoodlebugs();

    void moveAnts();

    void breedAnts();

    void printBoard();

    Critter* getContents(int row, int col);

    void setContents(Critter* newCritter, int row, int col);

    int getNumCols();

    int getNumRows();

    void starve();

    void cleanBoard();

};

#endif
