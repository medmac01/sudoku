#ifndef SOLVEDDIALOG_H
#define SOLVEDDIALOG_H

#include <QDialog>

namespace Ui {
class SolvedDialog;
}

class SolvedDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SolvedDialog(QWidget *parent = nullptr);
    ~SolvedDialog();

private:
    Ui::SolvedDialog *ui;
};

#endif // SOLVEDDIALOG_H
