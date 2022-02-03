#ifndef SUDOKUGAME_H
#define SUDOKUGAME_H

#include <QMainWindow>
#include "solver.h"


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
    ~sudokuGame();
private slots:


private:
    Ui::sudokuGame *ui;



};
#endif // SUDOKUGAME_H
