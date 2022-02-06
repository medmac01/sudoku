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




 
 
