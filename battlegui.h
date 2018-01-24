#ifndef BATTLEGUI_H
#define BATTLEGUI_H

#include <QWidget>
#include "chessboarddata_process.h"
#include <QTimer>

namespace Ui {
class battleGui;
}

class battleGui : public QWidget
{
    Q_OBJECT

public:
    explicit battleGui(QWidget *parent = 0);
    ~battleGui();

private:
    Ui::battleGui *ui;
    bool close();
    QTimer *timer;
    int time;
public :
    chessBoardData_Process *chessBoardData;
    void setData(chessBoardData_Process*data);
};

#endif // BATTLEGUI_H
