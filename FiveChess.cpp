#include "FiveChess.h"
#include "ui_FiveChess.h"
#include "battlegui.h"
#include "waitdialog.h"
#include "networksettingdialog.h"
#include "networkthread.h"

#include <QDebug>
#include <QLocale>

FiveChess::FiveChess(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::FiveChess)
{
	ui->setupUi(this);
	QObject::connect(ui->pushButtonNew, &QPushButton::clicked, this, &FiveChess::newFiveChessGame);
	QObject::connect(ui->pushButtonLoad, &QPushButton::clicked, this, &FiveChess::loadFiveChessGame);
	connect(ui->actionEnglish, &QAction::triggered, this, [&] {
		translateUi(QLocale::UnitedStates);
        qDebug() << "!!#en_us" << endl;
	});
	connect(ui->actionChinese, &QAction::triggered, this, [&] {
		translateUi(QLocale::China);
		qDebug() << "!!#zh_cn" << endl;
	});
}
FiveChess::~FiveChess()
{
    delete ui;
}

void FiveChess::newFiveChessGame()
{
    hide();
    battleGui *gameGui = new battleGui();
	gameGui->setTranslator(tsor);
    gameGui->show();
}

void FiveChess::loadFiveChessGame()
{
    if(chessBoard.loadBoard())
    {
            chessBoard.setOpt(ChessBoardCore::PaintOptType::chess);
            qDebug()<<"OK!"<<endl;
            newFiveChessGame();
            /*waitDialog *waitDialogWindow=new waitDialog(nullptr);
            waitDialogWindow->setModal(true);
            waitDialogWindow->show();*/
    }
}

void FiveChess::translateUi(int value)
{
	switch (value)
	{
	case QLocale::China: {
		tsor->load(":/lang/zh_CN.qm");
		break;
	}
	case QLocale::UnitedStates: {
		tsor->load(":/lang/en_US.qm");
		break;
	}
	default: {
		break;
	}
	}
	ui->retranslateUi(this);
}
