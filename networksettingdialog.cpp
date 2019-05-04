#include "networksettingdialog.h"
#include "networksettings.h"
#include "ui_networksettingdialog.h"
#include <QDebug>

NetworkSettingDialog::NetworkSettingDialog(QWidget* parent)
    : QDialog(parent), ui(new Ui::networkSettingDialog)
{
    ui->setupUi(this);
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, [&] {
        qDebug() << ui->lineEdit->text() << " " << ui->lineEdit_2->text().toInt();
        networkSettings["port"] = ui->lineEdit_2->text().toInt();
        networkSettings["host"] = ui->lineEdit->text();
    });
}

NetworkSettingDialog::~NetworkSettingDialog() { delete ui; }