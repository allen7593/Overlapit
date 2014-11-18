#include "resetpass.h"
#include "ui_resetpass.h"

resetPass::resetPass(QWidget *parent,QString accName) :
    QDialog(parent),
    ui(new Ui::resetPass)
{
    this->accName=accName;
    preWin=parent;
    ui->setupUi(this);
    ui->passWordLabel->setBuddy(ui->passEdit);
    ui->reenterLabel->setBuddy(ui->reenterLabel);
    ui->Okaybut->setDisabled(true);

    connect(ui->Okaybut,SIGNAL(clicked()),this,SLOT(saveNewPass()));
    connect(ui->preBut,SIGNAL(clicked()),this,SLOT(backToPre()));
    connect(ui->passEdit,SIGNAL(textChanged(QString)),this,SLOT(enableBut(QString)));
}

resetPass::~resetPass()
{
    delete ui;
}

void resetPass::enableBut(QString text)
{
    ui->Okaybut->setDisabled(text.isEmpty());
}

void resetPass::saveNewPass()
{
    if(ui->passEdit->text()==ui->reEnterEdit->text())
    {
        //save the password
        std::string plainText,cipherText;
        std::string aesKey = "b7bd865cb99216307a49b2a6a7a66efd"; //128 bits key
        std::string aesIV = "ABCDEF0123456789";//128 bits


        plainText.append(accName.toStdString());
        plainText.append(ui->passEdit->text().toStdString());
        cipherText=CTR_AESEncryptStr(aesKey, aesIV, plainText.c_str());

        std::ofstream outf;
        outf.open("asset1");
    }
    else
    {
        QMessageBox::warning(this, tr("Warning"),tr("Password are not the same"),QMessageBox::Ok);
        return;
    }


}

void resetPass::backToPre()
{
    this->close();
    preWin->show();
}
