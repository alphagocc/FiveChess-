#include "chessboardgui.h"
#include "ui_chessboardgui.h"
#include <QPainter>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QDebug>
#include <QTimer>

chessBoardGui::chessBoardGui(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::chessBoardGui)
{
    opt=onlyChessBoard;
    ui->setupUi(this);
    flg=0;
}

chessBoardGui::~chessBoardGui()
{
    delete ui;
}

void chessBoardGui::paintEvent(QPaintEvent *)
{
    chessBoardData.dataPrint();
    auto f=[&]{parentWidget()->close();};
    qDebug()<<"OK1"<<endl;
    QPainter painter;
    painter.begin(this);
    painter.drawImage(QPoint(0,0),QImage(":/img/Resources/chessboard.jpg"));
    if (opt==blackWin)
    {
        painter.drawImage(QRect(535/2-200,535/2-60,400,120),QImage(":/img/Resources/blackwin.JPG"));
        QTimer::singleShot(2000,this,f);
    }
    if (opt==whiteWin)
    {
        painter.drawImage(QRect(535/2-200,535/2-60,400,120),QImage(":/img/Resources/whitewin.JPG"));
        QTimer::singleShot(2000,this,f);
    }
    qDebug()<<"OK2"<<endl;
    if (opt==chess){
    for (int i=0;i<15;i++)
        for (int j=0;j<15;j++)
        {
            //qDebug()<<"i:"<<i<<"j:"<<j<<"data:"<<chessBoardData.data[i][j]<<endl;
            if (chessBoardData.data[i][j]==chessBoardData_Process::black)
            painter.drawImage(QRect(i*35+7,j*35+7,30,30),QImage(":/img/Resources/black.png"));
            if (chessBoardData.data[i][j]==chessBoardData_Process::white)
            painter.drawImage(QRect(i*35+7,j*35+7,30,30),QImage(":/img/Resources/white.png"));
        }
    }
    painter.end();
}

void chessBoardGui::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton){
        mouseOffset=event->globalPos() - pos()-parentWidget()->pos()-QPoint(30,54);
    }
    qDebug()<<(mouseOffset.x())<<" "<<(mouseOffset.y())<<endl;
    int tx=(mouseOffset.x()+17)/35,ty=(mouseOffset.y()+17)/35;
    qDebug()<<tx<<" "<<ty<<endl;
    if (chessBoardData.data[tx][ty]==chessBoardData_Process::none){
    chessBoardData.data[tx][ty]=flg?chessBoardData_Process::white:chessBoardData_Process::black;
    flg^=1;
    opt=chess;
    if (chessBoardData.searchWin(flg?chessBoardData_Process::white:chessBoardData_Process::black))
    {
        if (flg){opt=whiteWin;}
        else {opt=blackWin;}
    }
    repaint();
    }
}

void chessBoardGui::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
}
