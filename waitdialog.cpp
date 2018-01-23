#include "waitdialog.h"
#include "ui_waitdialog.h"

waitDialog::waitDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::waitDialog)
{
    ui->setupUi(this);
}

waitDialog::~waitDialog()
{
    delete ui;
}
