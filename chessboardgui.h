#ifndef CHESSBOARDGUI_H
#define CHESSBOARDGUI_H

#include <QFrame>
#include <chessboarddata_process.h>

namespace Ui {
class chessBoardGui;
}

class chessBoardGui : public QFrame
{
    Q_OBJECT

public:
    explicit chessBoardGui(QWidget *parent = 0);
    ~chessBoardGui();

private:
    Ui::chessBoardGui *ui;
    QPoint mouseOffset;
    int flg;
    enum optType{
        onlyChessBoard = 0x00000000,
        chess          = 0x00000001,
        blackWin       = 0x00000002,
        whiteWin       = 0x00000004,
        over           = 0x00000008
    }opt;

protected :
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
public :
    chessBoardData_Process chessBoardData;
    void setData(chessBoardData_Process&data){this->chessBoardData=data;}
};

#endif // CHESSBOARDGUI_H
