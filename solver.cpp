#include "solver.h"
#include <iostream>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <vector>

#define UNASSIGNED 0

using namespace std;


// START: Get grid as string in row major order
QString Board::getGrid()
{
  QString s = "";
  for(int row_num=0; row_num<9; ++row_num)
  {
    for(int col_num=0; col_num<9; ++col_num)
    {
      s.append(grid[row_num][col_num]);
      cout << grid[row_num][col_num] << endl;
    }
  }

  return s;
}
// END: Get grid as string in row major order


// START: Generate random number
int genRandNum(int maxLimit)
{
  return rand()%maxLimit;
}
// END: Generate random number


// START: Create seed grid
void Board::createSeed()
{
  this->solveGrid();

  // Saving the solution grid
  for(int i=0;i<9;i++)
  {
    for(int j=0;j<9;j++)
    {
      this->solnGrid[i][j] = this->grid[i][j];
    }
  }
}
// END: Create seed grid


// START: Intialising
Board::Board(int difficulty)
{

  // initialize difficulty level
  this->difficultyLevel = difficulty;

  // Randomly shuffling the array of removing grid positions
  for(int i=0;i<81;i++)
  {
    this->gridPos[i] = i;
  }

  random_shuffle(this->gridPos, (this->gridPos) + 81, genRandNum);

  // Randomly shuffling the guessing number array
  for(int i=0;i<9;i++)
  {
    this->guessNum[i]=i+1;
  }

  random_shuffle(this->guessNum, (this->guessNum) + 9, genRandNum);

  // Initialising the grid
  for(int i=0;i<9;i++)
  {
    for(int j=0;j<9;j++)
    {
      this->grid[i][j]=0;
    }
  }

  grid_status = true;
}
// END: Initialising


// START: Custom Initialising with grid passed as argument
Board::Board(string grid_str, bool row_major)
{
  if(grid_str.length() != 81)
  {
    grid_status=false;
    return;
  }

  // First pass: Check if all cells are valid
  for(int i=0; i<81; ++i)
  {
    int curr_num = grid_str[i]-'0';
    if(!((curr_num == UNASSIGNED) || (curr_num > 0 && curr_num < 10)))
    {
      grid_status=false;
      return;
    }

    if(row_major) grid[i/9][i%9] = curr_num;
    else          grid[i%9][i/9] = curr_num;
  }

  // Second pass: Check if all columns are valid
  for (int col_num=0; col_num<9; ++col_num)
  {
    bool nums[10]={false};
    for (int row_num=0; row_num<9; ++row_num)
    {
      int curr_num = grid[row_num][col_num];
      if(curr_num!=UNASSIGNED && nums[curr_num]==true)
      {
        grid_status=false;
        return;
      }
      nums[curr_num] = true;
    }
  }

  // Third pass: Check if all rows are valid
  for (int row_num=0; row_num<9; ++row_num)
  {
    bool nums[10]={false};
    for (int col_num=0; col_num<9; ++col_num)
    {
      int curr_num = grid[row_num][col_num];
      if(curr_num!=UNASSIGNED && nums[curr_num]==true)
      {
        grid_status=false;
        return;
      }
      nums[curr_num] = true;
    }
  }

  // Fourth pass: Check if all blocks are valid
  for (int block_num=0; block_num<9; ++block_num)
  {
    bool nums[10]={false};
    for (int cell_num=0; cell_num<9; ++cell_num)
    {
      int curr_num = grid[((int)(block_num/3))*3 + (cell_num/3)][((int)(block_num%3))*3 + (cell_num%3)];
      if(curr_num!=UNASSIGNED && nums[curr_num]==true)
      {
        grid_status=false;
        return;
      }
      nums[curr_num] = true;
    }
  }

  // Randomly shuffling the guessing number array
  for(int i=0;i<9;i++)
  {
    this->guessNum[i]=i+1;
  }

  random_shuffle(this->guessNum, (this->guessNum) + 9, genRandNum);

  grid_status = true;
}
// END: Custom Initialising


// START: Verification status of the custom grid passed
bool Board::verifyGridStatus()
{
  return grid_status;
}
// END: Verification of the custom grid passed


// START: Printing the grid
void Board::printGrid()
{
  for(int i=0;i<9;i++)
  {
    for(int j=0;j<9;j++)
    {
      if(grid[i][j] == 0)
    cout<<".";
      else
    cout<<grid[i][j];
      cout<<"|";
    }
    cout<<endl;
  }

  cout<<"\nDifficulty of current Board(0 being easiest): "<<this->difficultyLevel;
  cout<<endl;
}
// END: Printing the grid


// START: Helper functions for solving grid
bool FindUnassignedLocation(int grid[9][9], int &row, int &col)
{
    for (row = 0; row < 9; row++)
    {
        for (col = 0; col < 9; col++)
        {
            if (grid[row][col] == UNASSIGNED)
                return true;
        }
    }

    return false;
}

bool UsedInRow(int grid[9][9], int row, int num)
{
    for (int col = 0; col < 9; col++)
    {
        if (grid[row][col] == num)
            return true;
    }

    return false;
}

bool UsedInCol(int grid[9][9], int col, int num)
{
    for (int row = 0; row < 9; row++)
    {
        if (grid[row][col] == num)
            return true;
    }

    return false;
}

bool UsedInBox(int grid[9][9], int boxStartRow, int boxStartCol, int num)
{
    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            if (grid[row+boxStartRow][col+boxStartCol] == num)
                return true;
        }
    }

    return false;
}

bool isSafe(int grid[9][9], int row, int col, int num)
{
    return !UsedInRow(grid, row, num) && !UsedInCol(grid, col, num) && !UsedInBox(grid, row - row%3 , col - col%3, num);
}

// END: Helper functions for solving grid


// START: Modified Board solver
bool Board::solveGrid()
{
    int row, col;

    // If there is no unassigned location, we are done
    if (!FindUnassignedLocation(this->grid, row, col))
       return true; // success!

    // Consider digits 1 to 9
    for (int num = 0; num < 9; num++)
    {
        // if looks promising
        if (isSafe(this->grid, row, col, this->guessNum[num]))
        {
            // make tentative assignment
            this->grid[row][col] = this->guessNum[num];

            // return, if success, yay!
            if (solveGrid())
                return true;

            // failure, unmake & try again
            this->grid[row][col] = UNASSIGNED;
        }
    }

    return false; // this triggers backtracking

}
// END: Modified Board Solver


// START: Check if the grid is uniquely solvable
void Board::countSoln(int &number)
{
  int row, col;

  if(!FindUnassignedLocation(this->grid, row, col))
  {
    number++;
    return ;
  }


  for(int i=0;i<9 && number<2;i++)
  {
      if( isSafe(this->grid, row, col, this->guessNum[i]) )
      {
        this->grid[row][col] = this->guessNum[i];
        countSoln(number);
      }

      this->grid[row][col] = UNASSIGNED;
  }

}
// END: Check if the grid is uniquely solvable


// START: Gneerate puzzle
void Board::genPuzzle()
{
  for(int i=0;i<81;i++)
  {
    int x = (this->gridPos[i])/9;
    int y = (this->gridPos[i])%9;
    int temp = this->grid[x][y];
    this->grid[x][y] = UNASSIGNED;

    // If now more than 1 solution , replace the removed cell back.
    int check=0;
    countSoln(check);
    if(check!=1)
    {
      this->grid[x][y] = temp;
    }
  }
}
// END: Generate puzzle


// START: Printing into SVG file
void Board::printSVG(string path="")
{
}
// END: Printing into SVG file


// START: Calculate branch difficulty score
int Board::branchDifficultyScore()
{
   int emptyPositions = -1;
   int tempGrid[9][9];
   int sum=0;

   for(int i=0;i<9;i++)
  {
    for(int j=0;j<9;j++)
    {
      tempGrid[i][j] = this->grid[i][j];
    }
  }

   while(emptyPositions!=0)
   {
     vector<vector<int> > empty;

     for(int i=0;i<81;i++)
     {
        if(tempGrid[(int)(i/9)][(int)(i%9)] == 0)
        {
          vector<int> temp;
      temp.push_back(i);

      for(int num=1;num<=9;num++)
      {
        if(isSafe(tempGrid,i/9,i%9,num))
        {
          temp.push_back(num);
        }
      }

      empty.push_back(temp);
        }

     }

     if(empty.size() == 0)
     {
       cout<<"Hello: "<<sum<<endl;
       return sum;
     }

     int minIndex = 0;

     int check = empty.size();
     for(int i=0;i<check;i++)
     {
       if(empty[i].size() < empty[minIndex].size())
      minIndex = i;
     }

     int branchFactor=empty[minIndex].size();
     int rowIndex = empty[minIndex][0]/9;
     int colIndex = empty[minIndex][0]%9;

     tempGrid[rowIndex][colIndex] = this->solnGrid[rowIndex][colIndex];
     sum = sum + ((branchFactor-2) * (branchFactor-2)) ;

     emptyPositions = empty.size() - 1;
   }

   return sum;

}
// END: Finish branch difficulty score


// START: Calculate difficulty level of current grid
void Board::calculateDifficulty()
{
  int B = branchDifficultyScore();
  int emptyCells = 0;

  for(int i=0;i<9;i++)
  {
    for(int j=0;j<9;j++)
    {
    if(this->grid[i][j] == 0)
       emptyCells++;
    }
  }

  this->difficultyLevel = B*100 + emptyCells;
}



