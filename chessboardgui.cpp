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
    ui->setupUi(this);
}

chessBoardGui::~chessBoardGui()
{
    delete ui;
}

void chessBoardGui::paintEvent(QPaintEvent *)
{
    ChessBoardCore::PaintOptType opt=chessBoard.getPaintOpt();
    chessBoard.dataPrint();
    auto f=[&]{parentWidget()->close();};
    qDebug()<<"OK1"<<endl;
    QPainter painter;
    painter.begin(this);
    painter.drawImage(QPoint(0,0),QImage(":/img/Resources/chessboard.jpg"));
    if (opt==ChessBoardCore::PaintOptType::blackWin)
    {
        painter.drawImage(QRect(535/2-200,535/2-60,400,120),QImage(":/img/Resources/blackwin.JPG"));
        QTimer::singleShot(2000,this,f);
    }
    if (opt==ChessBoardCore::PaintOptType::whiteWin)
    {
        painter.drawImage(QRect(535/2-200,535/2-60,400,120),QImage(":/img/Resources/whitewin.JPG"));
        QTimer::singleShot(2000,this,f);
    }
    qDebug()<<"OK2"<<endl;
    if (opt==ChessBoardCore::PaintOptType::chess){
    for (int i=0;i<15;i++)
        for (int j=0;j<15;j++)
        {
            qDebug()<<"i:"<<i<<"j:"<<j<<"data:"<<static_cast<int>(chessBoard.getPointData(i,j))<<endl;
            if (chessBoard.getPointData(i,j)==ChessBoardCore::DataType::black)
            painter.drawImage(QRect(i*35+7,j*35+7,30,30),QImage(":/img/Resources/black.png"));
            if (chessBoard.getPointData(i,j)==ChessBoardCore::DataType::white)
            painter.drawImage(QRect(i*35+7,j*35+7,30,30),QImage(":/img/Resources/white.png"));
        }
    }
    painter.end();
}

void chessBoardGui::mousePressEvent(QMouseEvent *event)
{
    int flag=chessBoard.getFlag();
    if (event->button() == Qt::LeftButton){
        mouseOffset=event->globalPos() - pos()-parentWidget()->pos()-QPoint(30,54);
    }
    qDebug()<<(mouseOffset.x())<<" "<<(mouseOffset.y())<<endl;
    int tx=(mouseOffset.x()+17)/35,ty=(mouseOffset.y()+17)/35;
    qDebug()<<tx<<" "<<ty<<endl;

    if (chessBoard.getPointData(tx,ty)==ChessBoardCore::DataType::none){
    chessBoard.setPointData(tx,ty,flag?ChessBoardCore::DataType::white:ChessBoardCore::DataType::black);
    chessBoard.setOpt(ChessBoardCore::PaintOptType::chess);
    if (chessBoard.searchWin(flag?ChessBoardCore::DataType::white:ChessBoardCore::DataType::black))
    {
        if (flag){chessBoard.setOpt(ChessBoardCore::PaintOptType::whiteWin);}
        else {chessBoard.setOpt(ChessBoardCore::PaintOptType::blackWin);}
    }
    repaint();
    chessBoard.setFlag(flag^1);
    }
}
void chessBoardGui::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
}

