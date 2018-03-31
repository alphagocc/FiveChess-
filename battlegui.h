#ifndef BATTLEGUI_H
#define BATTLEGUI_H

#include <QWidget>
#include "chessBoardCore.h"
#include <QTimer>
#include <QTranslator>

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
	QTranslator * tsor;
public :
    chessBoardCore *chessBoard;
    void setData(chessBoardCore*data);
	void setTranslator(QTranslator *tsor) { this->tsor = tsor; }
};

#endif // BATTLEGUI_H
