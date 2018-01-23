#include "battlegui.h"
#include "ui_battlegui.h"

battleGui::battleGui(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::battleGui),
    timer(new QTimer)
{
    ui->setupUi(this);
    time=0;
    ui->frame->setData(chessBoardData);
    timer->start(1000);
    connect(ui->pushButtonSave,ui->pushButtonSave->clicked,this,[&]{
        ui->frame->chessBoardData.saveBoard();
    });
    connect(timer,timer->timeout,this,[&]{
        time++;
        ui->labelTime->setText(tr("时间：%1秒").arg(time));
    });
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



