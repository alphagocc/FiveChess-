#include "chessboardgui.h"
#include "ui_chessboardgui.h"
#include "stdafx.h"
#include <QPainter>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QDebug>
#include <QTimer>

chessBoardGui::chessBoardGui(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::chessBoardGui)
{
    ui->setupUi(this);
}

chessBoardGui::~chessBoardGui()
{
    delete ui;
}

void chessBoardGui::paintEvent(QPaintEvent *)
{
    chessBoardData_Process::optType& opt=(chessBoardData->opt);
    chessBoardData->dataPrint();
    auto f=[&]{parentWidget()->close();};
    qDebug()<<"OK1"<<endl;
    QPainter painter;
    painter.begin(this);
    painter.drawImage(QPoint(0,0),QImage(":/img/Resources/chessboard.jpg"));
    if (opt==chessBoardData_Process::blackWin)
    {
        painter.drawImage(QRect(535/2-200,535/2-60,400,120),QImage(":/img/Resources/blackwin.JPG"));
        QTimer::singleShot(2000,this,f);
    }
    if (opt==chessBoardData_Process::whiteWin)
    {
        painter.drawImage(QRect(535/2-200,535/2-60,400,120),QImage(":/img/Resources/whitewin.JPG"));
        QTimer::singleShot(2000,this,f);
    }
    qDebug()<<"OK2"<<endl;
    if (opt==chessBoardData_Process::chess){
    for (int i=0;i<15;i++)
        for (int j=0;j<15;j++)
        {
            //qDebug()<<"i:"<<i<<"j:"<<j<<"data:"<<chessBoardData.data[i][j]<<endl;
            if (chessBoardData->data[i][j]==chessBoardData_Process::black)
            painter.drawImage(QRect(i*35+7,j*35+7,30,30),QImage(":/img/Resources/black.png"));
            if (chessBoardData->data[i][j]==chessBoardData_Process::white)
            painter.drawImage(QRect(i*35+7,j*35+7,30,30),QImage(":/img/Resources/white.png"));
        }
    }
    painter.end();
}

void chessBoardGui::mousePressEvent(QMouseEvent *event)
{
    chessBoardData_Process::optType& opt=chessBoardData->opt;
    int& flg=chessBoardData->flg;
    if (event->button() == Qt::LeftButton){
        mouseOffset=event->globalPos() - pos()-parentWidget()->pos()-QPoint(30,54);
    }
    qDebug()<<(mouseOffset.x())<<" "<<(mouseOffset.y())<<endl;
    int tx=(mouseOffset.x()+17)/35,ty=(mouseOffset.y()+17)/35;
    qDebug()<<tx<<" "<<ty<<endl;
    if (chessBoardData->data[tx][ty]==chessBoardData_Process::none){
    chessBoardData->data[tx][ty]=flg?chessBoardData_Process::white:chessBoardData_Process::black;
    opt=chessBoardData_Process::chess;
    if (chessBoardData->searchWin(flg?chessBoardData_Process::white:chessBoardData_Process::black))
    {
        if (flg){opt=chessBoardData_Process::whiteWin;}
        else {opt=chessBoardData_Process::blackWin;}
    }
    repaint();
    flg^=1;
    }
}

void chessBoardGui::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
}

void chessBoardGui::setData(chessBoardData_Process *data)
{
    this->chessBoardData=data;
    qDebug()<<"SetData!2"<<data<<endl;
}
