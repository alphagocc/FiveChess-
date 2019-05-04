#ifndef NETWORKSETTINGDIALOG_H
#define NETWORKSETTINGDIALOG_H

#include <QDialog>

namespace Ui {
class networkSettingDialog;
}

class NetworkSettingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NetworkSettingDialog(QWidget *parent = 0);
    ~NetworkSettingDialog();

private:
    Ui::networkSettingDialog *ui;
};

#endif // NETWORKSETTINGDIALOG_H

