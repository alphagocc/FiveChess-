#ifndef FIVECHESS_H
#define FIVECHESS_H

#include "chessboardcore.h"
#include <QMainWindow>
#include <QTranslator>

namespace Ui
{
class FiveChess;
}

class FiveChess : public QMainWindow
{
    Q_OBJECT

  public:
    explicit FiveChess(QWidget* parent = 0);
    ~FiveChess();

  private:
    Ui::FiveChess* ui;
    QTranslator*   tsor;
  public slots:
    void newFiveChessGame();
    void loadFiveChessGame();
    void newNetworkFiveChessGame();

  public:
    void translateUi(int value);
    void setTranslator(QTranslator* tsor) { this->tsor = tsor; }
};

#endif // FIVECHESS_H
