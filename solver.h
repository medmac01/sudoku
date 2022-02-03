#ifndef SOLVER_H
#define SOLVER_H
#include <string>
#include <QString>
using namespace std;

class Board {
private:
  int solnGrid[9][9];
  int guessNum[9];
  int gridPos[81];
  int difficultyLevel;
  bool grid_status;

public:
  Board (int difficulty);
  Board (string, bool row_major=true);
  int grid[9][9];
  void createSeed();
  void printGrid();
  bool solveGrid();
  QString getGrid();
  void countSoln(int &number);
  void genPuzzle();
  bool verifyGridStatus();
  void printSVG(string);
  void calculateDifficulty();
  int  branchDifficultyScore();
  void init();
};


#endif // SOLVER_H
