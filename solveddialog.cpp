#include "solveddialog.h"
#include "ui_solved_dialog.h"

SolvedDialog::SolvedDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SolvedDialog)
{
    ui->setupUi(this);
}

SolvedDialog::~SolvedDialog()
{
    delete ui;
}
