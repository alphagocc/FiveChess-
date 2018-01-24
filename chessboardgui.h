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

protected :
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
public :
    chessBoardData_Process *chessBoardData;
    void setData(chessBoardData_Process *data);
};

#endif // CHESSBOARDGUI_H
