#include "FiveChess.h"
#include "ui_FiveChess.h"
#include "battlegui.h"

FiveChess::FiveChess(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FiveChess)
{
    ui->setupUi(this);
    QObject::connect(ui->pushButtonNew,ui->pushButtonNew->clicked,this,newFiveChessGame);
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
