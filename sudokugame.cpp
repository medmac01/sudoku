#include "sudokugame.h"
#include "ui_sudokugame.h"

sudokuGame::sudokuGame(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::sudokuGame)
{
    ui->setupUi(this);
}

sudokuGame::~sudokuGame()
{
    delete ui;
}

