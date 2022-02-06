#include "sudokugame.h"
#include "ui_sudokugame.h"
#include <ctime>
#include <QMessageBox>


//#include "solver.cpp"

sudokuGame::sudokuGame(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::sudokuGame)
{
    ui->setupUi(this);
    makeConnections();
    ui->solveBt->setDisabled(true);

    newHist->col = 1;
    newHist->row = 1;
    newHist->value = 0;
}

sudokuGame::~sudokuGame()
{
    delete ui;
}

void sudokuGame::newGame(){
    //Set score to 0
    ui->scoreInt->setText("00000");
    ui->solveBt->setDisabled(false);
    boardGenerator();
}

void sudokuGame::boardGenerator(){
//    srand(time(NULL));

    // Creating an instance of Board
    currentBoard = new Board(0);
    solvedBoard = new Board(0);
    *solvedBoard = *currentBoard;
    solvedBoard->solveGrid();


    // Creating a seed for puzzle generation
    currentBoard->createSeed();

    // Generating the puzzle
    currentBoard->genPuzzle();
//    QString s = to_string(puzzle->grid[0][4]);
    loadBoard(currentBoard);

//    QMessageBox::critical(this,"Error",);
}

void sudokuGame::loadBoard(Board *b){
    for(int i=0;i<9;i++) {
        for(int j=0;j<9;j++){
            auto buffer = to_string(b->grid[i][j]);
            QString s = QString::fromStdString(buffer);
            QTableWidgetItem* tmp = new QTableWidgetItem(s);
            if(buffer == "0")
                tmp->setText("");
            else
                tmp->setFlags(Qt::ItemIsEnabled);
            ui->mainBoard->setItem(i,j,tmp);
        }
    }
}

void sudokuGame::solveBoard(){
    if(currentBoard != nullptr) {
        currentBoard->solveGrid();
        loadBoard(currentBoard);
    }
}

void sudokuGame::updateHistory(){
    newHist->col = ui->mainBoard->currentColumn();
    newHist->row = ui->mainBoard->currentRow();
    newHist->value = ui->mainBoard->currentItem()->text().toInt();
}

void sudokuGame::makeConnections(){
    connect(ui->newGameBt,&QPushButton::clicked,this,&sudokuGame::newGame);
    connect(ui->solveBt,&QPushButton::clicked,this,&sudokuGame::solveBoard);
    connect(ui->checkBt,&QPushButton::clicked,this,&sudokuGame::checkInput);
    connect(ui->pushButton_4,&QPushButton::clicked,this,&sudokuGame::quitGame);
    connect(ui->mainBoard,&QTableWidget::cellDoubleClicked,this,&sudokuGame::updateHistory);
    connect(ui->mainBoard,&QTableWidget::cellChanged,this,&sudokuGame::solved);
    connect(ui->undoBt,&QPushButton::clicked,this,&sudokuGame::undo);
}

void sudokuGame::undo() {
    QTableWidgetItem* tmp = new QTableWidgetItem(newHist->value);
    ui->mainBoard->setItem(newHist->row,newHist->col,tmp);
}
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

void sudokuGame::quitGame() {
    auto reply = QMessageBox::question(this,"Quit","Do you really want to quit?");

    if(reply)
        qApp->exit();
}

void sudokuGame::solved() {
    if (checkifsolved())
        QMessageBox::information(this,"Congrats!","Board solved successfully!");
}
