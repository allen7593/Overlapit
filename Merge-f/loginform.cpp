#include "loginform.h"

LoginForm::LoginForm(QMainWindow *parent,QString accName)
    : QDialog(parent,Qt::FramelessWindowHint)
{

    this->accName=accName;
    //homePath="/home/allen7593";
    restoreBut = new QPushButton(tr("Restore the program"));
    newDevice = new QPushButton(tr("Change to a new deveice"));
    resetPass = new QPushButton(tr("Reset password"));
    onBut = new QPushButton(tr("On"));
    offBut = new QPushButton(tr("Off"));
    preBut = new QPushButton(tr("Previous"));

    infoLabel = new QLabel(tr("Please select one of the "));

    onOffLabel = new QLabel(tr("Turn on/off"));

    mainLayout = new QVBoxLayout;
    onOffLayout = new QHBoxLayout;
    infoLayout = new QHBoxLayout;

    preWin=parent;

    onOffLayout->addWidget(onBut);
    onOffLayout->addStretch();
    onOffLayout->addWidget(offBut);

    infoLayout->addStretch();
    infoLayout->addWidget(infoLabel);
    infoLayout->addStretch();

    mainLayout->addLayout(infoLayout);
    mainLayout->addSpacing(10);
    mainLayout->addWidget(onOffLabel);
    mainLayout->addLayout(onOffLayout);
    mainLayout->addSpacing(10);
    mainLayout->addWidget(newDevice);
    mainLayout->addWidget(resetPass);
    mainLayout->addWidget(restoreBut);
    mainLayout->addSpacing(10);
    mainLayout->addWidget(preBut);

    connect(preBut,SIGNAL(clicked()),this,SLOT(backToPre()));
    connect(onBut,SIGNAL(clicked()),this,SLOT(turnOn()));
    connect(offBut,SIGNAL(clicked()),this,SLOT(turnOff()));
    connect(resetPass,SIGNAL(clicked()),this,SLOT(resetPassword()));
    connect(newDevice,SIGNAL(clicked()),this,SLOT(resetPic()));



    QHBoxLayout* paddingHL=new QHBoxLayout;
    QVBoxLayout* paddingVL=new QVBoxLayout;

    paddingHL->addStretch();
    paddingHL->addLayout(mainLayout);
    paddingHL->addStretch();

    paddingVL->addStretch();
    paddingVL->addLayout(paddingHL);
    paddingVL->addStretch();



    setWindowFlags( ( (this->windowFlags() | Qt::CustomizeWindowHint)& ~Qt::WindowCloseButtonHint) );
    setLayout(paddingVL);

    setMinimumSize(220,230);

}

LoginForm::~LoginForm()
{
}

void LoginForm::backToPre()
{
    this->hide();
    preWin->show();

}

void LoginForm::turnOn()
{
    std::string absPatho,absPathf;
    absPatho="on";
    absPathf="off";

    if(0==access(absPatho.c_str(), 0))
    {
        QMessageBox::warning(this, tr("Warning"),tr("Program has already turned on"),QMessageBox::Ok);
    }
    else if(0==access(absPathf.c_str(), 0))
    {
        std::remove(absPathf.c_str());
        std::ofstream inFile;
        inFile.open(absPatho.c_str());
        inFile<<"on";
        inFile.close();
        QMessageBox::information(this, tr("Info"),tr("Program turned on"),QMessageBox::Ok);
    }
    else
    {
        std::ofstream inFile;
        inFile.open(absPatho.c_str());
        inFile<<"on";
        inFile.close();
        QMessageBox::information(this, tr("Info"),tr("Program turned on"),QMessageBox::Ok);
    }



}

void LoginForm::turnOff()
{
    std::string absPatho,absPathf;
    absPatho="on";
    absPathf="off";


    if(0==access(absPathf.c_str(), 0))
    {
        QMessageBox::warning(this, tr("Warning"),tr("Program has already turned off"),QMessageBox::Ok);
    }
    else if(0==access(absPatho.c_str(), 0))
    {
        std::remove(absPatho.c_str());
        std::ofstream inFile;
        inFile.open(absPathf.c_str());
        inFile<<"off";
        inFile.close();
        QMessageBox::information(this, tr("Info"),tr("Program turned off"),QMessageBox::Ok);
    }
    else
    {
        std::ofstream inFile;
        inFile.open(absPathf.c_str());
        inFile<<"off";
        inFile.close();
        QMessageBox::information(this, tr("Info"),tr("Program turned off"),QMessageBox::Ok);
    }

}

void LoginForm::resetPassword()
{
    remove("asset1");
    regDia* r=new regDia(this,accName);
    this->hide();
    r->show();
}

void LoginForm::resetPic()
{


}

void LoginForm::restoreSys()
{


}
