# sudoku
A Simple Sudoku Game using QT and C++

# Index
  - Game Functionnalities
  - App components
  - Algorithm
  - Signals and slots
  - Final Results

## Game Functionnalities
In this version of sudoku, we successfully built these features:

1. The player can check whether the answer is correct or not. 

2. Each board can be solved automatically.    

3. The player can undo the most recent movement.        

4. The player can save and load a board from a `.sku` file.

    
## App components
This version of Sudoku relies mainly on:
  - `QTableWidget mainBoard`: which serves as the main board widget.
  - `Board *b`: which represents a board.
  - `QPushButtonBox` : Contains five `QPushButton`:
      * New Game: Starts a new game.
      * Save : saves the current board into a `.sku` file.
      * Check: checks whether the entered answers are correct or not.
      * Solve: solves the current board.
      * Quit: quits the game.
  - `Struct Hist {
        int row;
        int col;
        int value;
    }` : a structure that stores the latest move made by the player.
   - `int score` : stores the score of the player.

### Slots and methods
Here are the slots and methods implemented in this project:
  - `void newGame();` : Creates a new `Board` and starts a new game.
  - `void boardGenerator();` : generates numbers to store them in the board.
  - `void loadBoard(Board *b);` ; loads the board into the main widget.
  - `void checkInput();` : checks the player's answers and returns a graphical feedback.
  - `void updateHistory();` : updates the history within each move.
  - `bool checkifsolved();` : checks if the player has solved the board to end the game.
  - `void loadBoardFromFile(QString filename);` : loads the board from a `.sku` file.
  - `void saveBoardContent(QString filename);` : saves the board into a `.sku` file.

**Slots**
  - `void undo();` : Deletes the last filled cell.
  - `void solved():` : returns a congratulations dialog.
  - `void saveBoard():` : Opens the save file dialog.
  - `void openFileDialog();` : Opens the loadfile dialog.
  - `void quitGame();` : exits the game.

### Defining a board
A `Board` is defined by the following:

**Attributes**

  - `int grid[9][9];` : A 9x9 bi-dimensional vector that stores the board values.
  - `int difficultylevel` : define the difficulty level of the game (*lowest is the easiest*).
  - `bool grid_status`: checks whether the grid is valid or not (contains valid numbers from 1-9).

**Methods**
  - `bool solveGrid();` : solves the grid using backtracking algorithm.
  - `QString getGrid();` : returns the values of the grid in a QString.
  - `void genPuzzle();` : generates a new unsolved grid.

## Algorithm 
For the algorithm, we got inspired from this repository : vaithak/Sudoku-Generator 
The solver relies on backtracking algorithms to generate the board puzzle.
The algorithm can be described by the following flowchart:

![image](https://user-images.githubusercontent.com/56129562/152696493-748b620f-c71f-4a8d-a8d8-19967e665fc9.png)
![image](https://user-images.githubusercontent.com/56129562/152696556-96ef1dd6-a61d-43a7-ad35-764d3edbe30d.png)


## The final Result
The final result looks like this:

![image](https://user-images.githubusercontent.com/56129562/152696649-0d2b78bf-80e6-4f15-9301-dc0f6372a50a.png)
![image](https://user-images.githubusercontent.com/56129562/152696858-c1f9cb95-d16d-4ec9-a675-9be14eaf10b4.png)
**Check feedback**
![image](https://user-images.githubusercontent.com/56129562/152696906-135703bf-f66a-4630-97c4-94cea10937be.png)



 
 
