#include "battlegui.h"
#include "ui_battlegui.h"

battleGui::battleGui(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::battleGui)
{
    ui->setupUi(this);
    ui->frame->setData(chessBoardData);
}

battleGui::~battleGui()
{
    delete ui;
}

bool battleGui::close()
{
       QWidget *p = parentWidget();
       p->show();
       return true;
}


