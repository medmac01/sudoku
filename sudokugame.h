#ifndef SUDOKUGAME_H
#define SUDOKUGAME_H

#include <QMainWindow>
#include "solver.h"
#include <vector>


QT_BEGIN_NAMESPACE
namespace Ui { class sudokuGame; }
QT_END_NAMESPACE

class sudokuGame : public QMainWindow
{
    Q_OBJECT

public:
    sudokuGame(QWidget *parent = nullptr);
    void makeConnections();
//    void keyPressEvent(QKeyEvent *);
    void newGame();
    void boardGenerator();
    void loadBoard(Board *b);
    void solveBoard();
    void checkInput();
    bool checkifsolved();
    void updateHistory();
    struct Hist {
        int value;
        int row;
        int col;
    };
    Hist* newHist = new Hist;
    ~sudokuGame();
private slots:
    void quitGame();
    void undo();
    void solved();
private:
    Ui::sudokuGame *ui;
    Board * currentBoard = nullptr;
    Board * solvedBoard = nullptr;
    int score = 0;


};
#endif // SUDOKUGAME_H
