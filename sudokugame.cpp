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
}

sudokuGame::~sudokuGame()
{
    delete ui;
}

void sudokuGame::newGame(){
    //Set score to 0
    ui->scoreInt->setText("00000");
    boardGenerator();

}

void sudokuGame::boardGenerator(){
//    srand(time(NULL));

    // Creating an instance of Board
    Board *puzzle = new Board(0);

    // Creating a seed for puzzle generation
    puzzle->createSeed();

    // Generating the puzzle
    puzzle->genPuzzle();
//    QString s = to_string(puzzle->grid[0][4]);
    loadBoard(puzzle);

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

void sudokuGame::makeConnections(){
    connect(ui->newGameBt,&QPushButton::clicked,this,&sudokuGame::newGame);

}
