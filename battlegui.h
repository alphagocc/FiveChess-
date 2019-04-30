#ifndef BATTLEGUI_H
#define BATTLEGUI_H

#include <QWidget>
#include "chessboardcore.h"
#include <QTimer>
#include <QTranslator>

namespace Ui {
class battleGui;
}

class battleGui : public QWidget
{
    Q_OBJECT

public:
    explicit battleGui(QWidget *parent = nullptr);
    ~battleGui();

private:
    Ui::battleGui *ui;
    bool close();
    QTimer *timer;
	QTranslator * tsor;
public :
	void setTranslator(QTranslator *tsor) { this->tsor = tsor; }
};

#endif // BATTLEGUI_H
