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
```cpp
void sudokuGame::newGame(){
    //Set score to 0
    ui->scoreInt->setText("00000");
    ui->solveBt->setDisabled(false);
    boardGenerator();
}
```
  - `void boardGenerator();` : generates numbers to store them in the board.
```cpp
void sudokuGame::boardGenerator(){

    // Creating an instance of Board
    currentBoard = new Board(0);
    solvedBoard = new Board(0);
    *solvedBoard = *currentBoard;
    solvedBoard->solveGrid();

    // Creating a seed for puzzle generation
    currentBoard->createSeed();
    
    // Generating the puzzle
    currentBoard->genPuzzle();
    loadBoard(currentBoard);

}
```
  - `void loadBoard(Board *b);` ; loads the board into the main widget.
```cpp
void sudokuGame::loadBoard(Board *b){
  for(int i=0;i<9;i++) {
      for(int j=0;j<9;j++){
          auto buffer = to_string(b->grid[i][j]);
          QString s = QString::fromStdString(buffer);
          QTableWidgetItem* tmp = new QTableWidgetItem(QString::fromStdString(buffer));
          if(buffer == "0")
                  tmp->setText("");
          else
              tmp->setFlags(Qt::ItemIsEnabled);
          ui->mainBoard->setItem(i,j,tmp);
          delete tmp;
      }
  }
}
```
  - `void checkInput();` : checks the player's answers and returns a graphical feedback.
```cpp
void sudokuGame::checkInput(){
    for (int row=0;row<9;row++) {
        for (int col=0;col<9;col++) {
            if(currentBoard!= nullptr && ui->mainBoard->item(row,col)->text().toInt() == solvedBoard->grid[row][col]) {
                auto tmp = ui->mainBoard->item(row,col);
                if(ui->mainBoard->item(row,col)->flags() != Qt::ItemIsEnabled) {
                    tmp->setBackground(Qt::green);
                    score += ui->mainBoard->item(row,col)->text().toInt();
                    QString tmpScore;
                    tmpScore.setNum(score);
                    ui->scoreInt->setText(tmpScore);
                }

            } else {
                auto tmp = ui->mainBoard->item(row,col);
                tmp->setBackground(Qt::red);
            }
        }
    }
}
```
  - `void updateHistory();` : updates the history within each move.
```cpp
void sudokuGame::updateHistory(){
    newHist->col = ui->mainBoard->currentColumn();
    newHist->row = ui->mainBoard->currentRow();
    newHist->value = ui->mainBoard->currentItem()->text().toInt();
}
```
  - `bool checkifsolved();` : checks if the player has solved the board to end the game.
```cpp
bool sudokuGame::checkifsolved(){
    for (int row=0; row<9 ;row++ ) {
        for(int col=0; col<9; col++) {
            if(ui->mainBoard!= nullptr){
                if(ui->mainBoard->item(row,col)->text().toInt() != solvedBoard->grid[row][col]){ return false; }
            }
        }
    }
    return true;
}
```
  - `void loadBoardFromFile(QString filename);` : loads the board from a `.sku` file.
```cpp
void sudokuGame::loadBoardFromFile(QString filename){
    QFile file(filename);

    if(file.open(QFile::ReadOnly))
    {
        QTextStream in(&file);
        QStringList data;


        QString line= in.readLine();
        data = line.split(",");
        int row = 0;

        for(int i=0;i<81;i++) {
            if(data[i].toInt()>9)
                currentBoard->grid[row][i%9] = data[i].toInt()/10;
            else
                currentBoard->grid[row][i%9] = data[i].toInt();
            if(i%9 == 0)
                row++;
        }
        loadBoard(currentBoard);
    }
}
```
  - `void saveBoardContent(QString filename);` : saves the board into a `.sku` file.
```cpp
void sudokuGame::saveBoardContent(QString filename){
    QFile file(filename);

    if(file.open(QFile::WriteOnly))  //Opening the file in writing mode
    {
        //Initiating a stream using the file
        QTextStream out(&file);

        //loop to save all the content
        for(int i=0; i < 9;i++)
            for(int j=0; j < 9; j++)
            {
                auto tmp = ui->mainBoard->item(i, j);

                if(tmp) {
                    if(tmp->flags() == Qt::ItemIsEnabled)
                        out << tmp->text().toInt()*10 <<",";
                    else
                        out << tmp->text().toInt()<<",";
                }
                else
                    out << "0" << ",";
            }
        out<<endl;

    }
    file.close();
}
```
  - `void makeconnections();` : ensures the communication between signals/slots.
```cpp
void sudokuGame::makeConnections(){
    connect(ui->newGameBt,&QPushButton::clicked,this,&sudokuGame::newGame);
    connect(ui->solveBt,&QPushButton::clicked,this,&sudokuGame::solveBoard);
    connect(ui->checkBt,&QPushButton::clicked,this,&sudokuGame::checkInput);
    connect(ui->pushButton_4,&QPushButton::clicked,this,&sudokuGame::quitGame);
    connect(ui->mainBoard,&QTableWidget::cellDoubleClicked,this,&sudokuGame::updateHistory);
    connect(ui->mainBoard,&QTableWidget::cellChanged,this,&sudokuGame::solved);
    connect(ui->undoBt,&QPushButton::clicked,this,&sudokuGame::undo);
    connect(ui->saveBt,&QPushButton::clicked,this,&sudokuGame::openFileDiag);

}
```
  - `void solveBoard();` : solves the board.
```cpp
void sudokuGame::solveBoard(){
    if(currentBoard != nullptr) {
        currentBoard->solveGrid();
        loadBoard(currentBoard);
    }
}
```

**Slots**
  - `void undo();` : Deletes the last filled cell.
```cpp
void sudokuGame::undo() {
    QTableWidgetItem* tmp = new QTableWidgetItem(newHist->value);
    ui->mainBoard->setItem(newHist->row,newHist->col,tmp);
}
```
  - `void solved():` : returns a congratulations dialog.
```cpp
void sudokuGame::solved() {
    if (checkifsolved()){
        SolvedDialog* diag = new SolvedDialog();
        auto reply = diag->exec();

        if(reply == SolvedDialog::Accepted) {
            sudokuGame newS;
            newS.show();
        } else if(reply == SolvedDialog::Rejected) {
            qApp->exit();
        }
    }
}
```
  - `void saveBoard():` : Opens the save file dialog.
```cpp
void sudokuGame::saveBoard() {
    //Creating a file dialog to choose a file graphically
    auto dialog = new QFileDialog(this);

    //Check if the current file has a name or not
    if(currentFile == "")
    {
       currentFile = dialog->getSaveFileName(this,"Save file",".sku",tr("Sudoku Board(*.sku)"));

       //Update the window title with the file name
       setWindowTitle(currentFile);
    }

   //If we have a name simply save the content
   if( currentFile != "")
   {
           saveBoardContent(currentFile);
   }
}
```
  - `void openFileDialog();` : Opens the loadfile dialog.
```cpp
void sudokuGame::openFileDiag() {
    auto diag = new QFileDialog(this);

    currentFile = diag->getOpenFileName(this, tr("Open File"), "/", tr("CSV Files (*.sku)"));
    setWindowTitle(currentFile);

        if(currentBoard == nullptr){
            currentBoard = new Board(0);
            solvedBoard = new Board(0);
            *solvedBoard = *currentBoard;
        }

    loadBoardFromFile(currentFile);
}
```
  - `void quitGame();` : exits the game.
```cpp
void sudokuGame::quitGame() {
    auto reply = QMessageBox::question(this,"Quit","Do you really want to quit?");

    if(reply)
        qApp->exit();
}
```

### Defining a board
A `Board` is defined by the following:

**Attributes**

  - `int grid[9][9];` : A 9x9 bi-dimensional vector that stores the board values.
  - `int difficultylevel` : define the difficulty level of the game (*lowest is the easiest*).
  - `bool grid_status`: checks whether the grid is valid or not (contains valid numbers from 1-9).

**Methods**
  - `bool solveGrid();` : solves the grid using backtracking algorithm.
```cpp
bool Board::solveGrid()
{
    int row, col;

    // If there is no unassigned location, then the board is solved
    if (!FindUnassignedLocation(this->grid, row, col))
       return true; // success!

    for (int num = 0; num < 9; num++)
    {
        if (isSafe(this->grid, row, col, this->guessNum[num]))
        {
            this->grid[row][col] = this->guessNum[num];

            if (solveGrid())
                return true;
                
            this->grid[row][col] = UNASSIGNED;
        }
    }

    return false; // this triggers backtracking

}
```
  - `QString getGrid();` : returns the values of the grid in a QString.
```cpp
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
```
  - `void genPuzzle();` : generates a new unsolved grid.
```cpp
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
```
  - `void createSeed();` : creates the seed to generate the puzzle.
```cpp
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
```

## Algorithm 
For the algorithm, I got inspired from this repository : vaithak/Sudoku-Generator 
The solver relies on backtracking algorithms to generate the board puzzle.
The algorithm can be described by the following flowchart:

![flowchart](https://user-images.githubusercontent.com/56129562/152710343-5488af46-1bc8-4f92-8a43-982ac749192d.png)


<!-- 
![image](https://user-images.githubusercontent.com/56129562/152696493-748b620f-c71f-4a8d-a8d8-19967e665fc9.png)
![image](https://user-images.githubusercontent.com/56129562/152696556-96ef1dd6-a61d-43a7-ad35-764d3edbe30d.png)
 -->

## The final Result
The final result looks like this:

<!-- ![image](https://user-images.githubusercontent.com/56129562/152696649-0d2b78bf-80e6-4f15-9301-dc0f6372a50a.png) -->
<img src="https://user-images.githubusercontent.com/56129562/152696649-0d2b78bf-80e6-4f15-9301-dc0f6372a50a.png" width="800"></img>

**Game won panel**

<img src="https://user-images.githubusercontent.com/56129562/152696858-c1f9cb95-d16d-4ec9-a675-9be14eaf10b4.png" width="700"></img>

**Check feedback**

<img src="https://user-images.githubusercontent.com/56129562/152696906-135703bf-f66a-4630-97c4-94cea10937be.png" width="800"></img>
<!-- ![image](https://user-images.githubusercontent.com/56129562/152696858-c1f9cb95-d16d-4ec9-a675-9be14eaf10b4.png) -->
<!-- ![image](https://user-images.githubusercontent.com/56129562/152696906-135703bf-f66a-4630-97c4-94cea10937be.png) -->
