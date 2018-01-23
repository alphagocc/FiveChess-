#include "FiveChess.h"
#include "ui_FiveChess.h"
#include "battlegui.h"
#include "waitdialog.h"

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
    //chessBoardData.loadBoard();
    //newFiveChessGame();
    waitDialog *waitDialogWindow=new waitDialog(nullptr);
    waitDialogWindow->setModal(true);
    waitDialogWindow->show();
}
