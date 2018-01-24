#include "FiveChess.h"
#include "ui_FiveChess.h"
#include "battlegui.h"
#include "waitdialog.h"
#include <QDebug>

FiveChess::FiveChess(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FiveChess)
{
    ui->setupUi(this);
    QObject::connect(ui->pushButtonNew,ui->pushButtonNew->clicked,this,newFiveChessGame);
    QObject::connect(ui->pushButtonLoad,ui->pushButtonLoad->clicked,this,loadFiveChessGame);
}

FiveChess::~FiveChess()
{
    delete ui;
}

void FiveChess::newFiveChessGame()
{
    hide();
    battleGui *gameGui = new battleGui();
    gameGui->setData(chessBoardData);
    gameGui->show();
}

void FiveChess::loadFiveChessGame()
{
    if(chessBoardData->loadBoard())
    {
            chessBoardData->opt=chessBoardData_Process::chess;
            qDebug()<<"OK!"<<endl;
            newFiveChessGame();
            /*waitDialog *waitDialogWindow=new waitDialog(nullptr);
            waitDialogWindow->setModal(true);
            waitDialogWindow->show();*/
    }
}

void FiveChess::setData(chessBoardData_Process *data)
{
    this->chessBoardData=data;
    qDebug()<<"SetData0!"<<data<<endl;
}
