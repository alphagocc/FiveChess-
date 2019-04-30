/*#include "networksettingdialog.h"
#include "ui_networksettingdialog.h"
#include <QMessageBox>
#include <QFile>

networkSettingDialog::networkSettingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::networkSettingDialog)
{
    ui->setupUi(this);
    connect(ui->buttonBox,&QDialogButtonBox::accepted,this,[&]()
    {
        QFile *file=new QFile(QString("conf.conf"));
        if (!file->open(QFile::WriteOnly|QFile::Text))
        {
            file->write(QByteArray(ui->lineEdit->text()+"\n"+ui->lineEdit_2->text()));
            file->close();
        }else
        {
            QMessageBox::critical(this,
                                  tr("Error!The Configuration File Can't Write!"),
                                  tr("The Configuration File Can't Write!\n"
                                     "Please check and try again."),
                                  QMessageBox::Ok,
                                  QMessageBox::Cancel);
        }
        parent->networkFiveChessGame();
    });
}

networkSettingDialog::~networkSettingDialog()
{
    delete ui;
}
*/
