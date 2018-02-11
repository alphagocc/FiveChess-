#include "battlegui.h"
#include "ui_battlegui.h"
#include "stdafx.h"
#include <QDebug>

battleGui::battleGui(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::battleGui),
    timer(new QTimer)
{
    qDebug()<<"OK2"<<endl;
    ui->setupUi(this);
    time=0;
    timer->start(1000);

    connect(ui->pushButtonSave,&QPushButton::clicked,this,[&]{
        ui->frame->chessBoardData->saveBoard();
    });
    connect(timer,&QTimer::timeout,this,[&]{
        time++;
        ui->labelTime->setText(tr("Time:%1 Second").arg(time));
    });qDebug()<<"OK3"<<endl;
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

void battleGui::setData(chessBoardData_Process *data)
{
    this->chessBoardData=data;
    qDebug()<<"SetData!1"<<data<<endl;
    ui->frame->setData(chessBoardData);
}



