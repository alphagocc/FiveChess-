#ifndef FIVECHESS_H
#define FIVECHESS_H

#include <QMainWindow>
#include "chessboarddata_process.h"

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

public slots:
    void newFiveChessGame();
    void loadFiveChessGame();
public :
    chessBoardData_Process chessBoardData;
    void setData(chessBoardData_Process&data){this->chessBoardData=data;}
};

#endif // FIVECHESS_H
