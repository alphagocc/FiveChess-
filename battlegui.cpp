#include "battlegui.h"
#include "ui_battlegui.h"
#include <QDebug>

battleGui::battleGui(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::battleGui),
    timer(new QTimer)
{
    qDebug()<<"OK2"<<endl;
    ui->setupUi(this);
    timer->start(1000);

    connect(ui->pushButtonSave,&QPushButton::clicked,this,[&]{
        chessBoard.saveBoard();
    });
    connect(timer,&QTimer::timeout,this,[&]{
        chessBoard.addUsedTime();
        ui->labelTime->setText(tr("Time:%1 Second").arg(chessBoard.getUsedTime()));
    });

    qDebug()<<"OK3";
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



