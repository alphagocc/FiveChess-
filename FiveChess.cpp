#include "fivechess.h"
#include "battlegui.h"
#include "clientthread.h"
#include "networksettingdialog.h"
#include "serverthread.h"
#include "ui_FiveChess.h"
#include "ui_chooseCorS.h"
#include "waitdialog.h"

#include <QDebug>
#include <QLocale>

FiveChess::FiveChess(QWidget* parent) : QMainWindow(parent), ui(new Ui::FiveChess)
{
    ui->setupUi(this);
    connect(ui->pushButtonNew, &QPushButton::clicked, this, &FiveChess::newFiveChessGame);
    connect(ui->pushButtonLoad, &QPushButton::clicked, this,
            &FiveChess::loadFiveChessGame);
    connect(ui->actionEnglish, &QAction::triggered, this, [&] {
        translateUi(QLocale::UnitedStates);
        qDebug() << "!!#en_us";
    });
    connect(ui->actionChinese, &QAction::triggered, this, [&] {
        translateUi(QLocale::China);
        qDebug() << "!!#zh_cn";
    });
    connect(ui->pushButtonNetworkGame, &QPushButton::clicked, this,
            &FiveChess::newNetworkFiveChessGame);
}
FiveChess::~FiveChess() { delete ui; }

void FiveChess::newFiveChessGame()
{
    hide();
    battleGui* gameGui = new battleGui();
    gameGui->setTranslator(tsor);
    gameGui->show();
}

void FiveChess::loadFiveChessGame()
{
    if (chessBoard.loadBoard())
    {
        chessBoard.setOpt(ChessBoardCore::PaintOptType::chess);
        qDebug() << "OK!" << endl;
        newFiveChessGame();
    }
}

void FiveChess::newNetworkFiveChessGame()
{
    NetworkSettingDialog settingDialog;
    settingDialog.exec();
	
	QDialog*              chooseDialog   = new QDialog(this);
    Ui::ChooseCorSDialog* chooseDialogUi = new Ui::ChooseCorSDialog;
    chooseDialogUi->setupUi(chooseDialog);

    connect(chooseDialogUi->clientPushButton, &QPushButton::clicked, this, [&] {
        clientThread = new ClientThread;
        clientThread->run();
        chessBoard.setPlayMode(ChessBoardCore::PlayMode::client);
        chooseDialog->close();
    });
    connect(chooseDialogUi->serverPushButton, &QPushButton::clicked, this, [&] {
        serverThread = new ServerThread;
        serverThread->run();
        chessBoard.setPlayMode(ChessBoardCore::PlayMode::server);
        chooseDialog->close();
    });
    chooseDialog->exec();

    newFiveChessGame();
}

void FiveChess::translateUi(int value)
{
    switch (value)
    {
    case QLocale::China:
    {
        tsor->load(":/lang/zh_CN.qm");
        break;
    }
    case QLocale::UnitedStates:
    {
        tsor->load(":/lang/en_US.qm");
        break;
    }
    default: { break;
    }
    }
    ui->retranslateUi(this);
}
