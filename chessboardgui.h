#ifndef CHESSBOARDGUI_H
#define CHESSBOARDGUI_H

#include <QFrame>
#include "chessboardcore.h"

namespace Ui {
class chessBoardGui;
}

class chessBoardGui : public QFrame
{
    Q_OBJECT
public:
    explicit chessBoardGui(QWidget *parent = nullptr);
    ~chessBoardGui();

private:
    Ui::chessBoardGui *ui;
    QPoint mouseOffset;

protected :
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
};

#endif // CHESSBOARDGUI_H
