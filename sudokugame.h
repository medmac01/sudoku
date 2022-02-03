#ifndef SUDOKUGAME_H
#define SUDOKUGAME_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class sudokuGame; }
QT_END_NAMESPACE

class sudokuGame : public QMainWindow
{
    Q_OBJECT

public:
    sudokuGame(QWidget *parent = nullptr);
    ~sudokuGame();

private:
    Ui::sudokuGame *ui;
};
#endif // SUDOKUGAME_H
