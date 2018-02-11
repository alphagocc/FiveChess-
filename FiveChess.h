#ifndef FIVECHESS_H
#define FIVECHESS_H

#include <QMainWindow>
#include "chessboarddata_process.h"
#include <QTranslator>

namespace Ui {
class FiveChess;
}

class FiveChess : public QMainWindow
{
    Q_OBJECT

public:
    explicit FiveChess(QWidget *parent = 0);
    ~FiveChess();

private:
    Ui::FiveChess *ui;
	QTranslator *tsor;
public slots:
    void newFiveChessGame();
    void loadFiveChessGame();
public :
    chessBoardData_Process *chessBoardData;
    void setData(chessBoardData_Process*data);
	void translateUi(int value);
	void setTranslator(QTranslator *tsor) { this->tsor = tsor; }
};

#endif // FIVECHESS_H
