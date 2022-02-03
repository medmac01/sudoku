#include "sudokugame.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    sudokuGame w;
    w.show();
    return a.exec();
}
