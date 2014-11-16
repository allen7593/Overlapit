#include "regdia.h"


regDia::regDia(QMainWindow *parent)
    : QDialog(parent,Qt::FramelessWindowHint)
{
    preWin=parent;

    checkStatus=false;


    nameLabel = new QLabel(tr("Register"));
    infoLabel = new QLabel(tr("Please input all the blocks below."));
    usrNameLabel = new QLabel(tr("New user name:"));
    passwordLabel = new QLabel(tr("New password:"));
    reEnterLabel = new QLabel(tr("Re-enter password:"));
    emailLabel = new QLabel(tr("Enter the email:"));
    imgLabel = new QLabel;


    usrNameEdit = new QLineEdit;
    passwordEdit = new QLineEdit;
    passwordEdit->setEchoMode(QLineEdit::Password);
    reEnterEdit = new QLineEdit;
    reEnterEdit->setEchoMode(QLineEdit::Password);
    emailEdit = new QLineEdit;


    checkBut = new QPushButton(tr("Check"));
    submitBut = new QPushButton(tr("&Submit"));
    submitBut->setDisabled(true);
    clearBut = new QPushButton(tr("&Clear"));
    previousBut = new QPushButton(tr("Previous"));

    usrNameLabel->setBuddy(usrNameEdit);
    passwordLabel->setBuddy(passwordEdit);
    reEnterLabel->setBuddy(reEnterEdit);
    emailLabel->setBuddy(emailEdit);


    connect(previousBut,SIGNAL(clicked()),this,SLOT(backToPrePage()));
    connect(clearBut,SIGNAL(clicked()),this,SLOT(clearAll()));

    connect(submitBut,SIGNAL(clicked()),this,SLOT(GenerateQR()));

    connect(checkBut,SIGNAL(clicked()),this,SLOT(checkAcc()));

    connect(usrNameEdit,SIGNAL(textChanged(const QString&)),this,SLOT(enableSubmit(const QString&)));
    connect(passwordEdit,SIGNAL(textChanged(const QString&)),this,SLOT(enableSubmit(const QString&)));
    connect(reEnterEdit,SIGNAL(textChanged(const QString&)),this,SLOT(enableSubmit(const QString&)));
    connect(emailEdit,SIGNAL(textChanged(const QString&)),this,SLOT(enableSubmit(const QString&)));



    QVBoxLayout* mainLayout = new QVBoxLayout;

    QHBoxLayout* nameLayout = new QHBoxLayout;
    nameLayout->addStretch();
    nameLayout->addWidget(nameLabel);
    nameLayout->addStretch();

    QHBoxLayout* usrNameLayout=new QHBoxLayout;
    usrNameLabel->setBuddy(usrNameEdit);
    usrNameLayout->addWidget(usrNameLabel);
    usrNameLayout->addWidget(usrNameEdit);


    QHBoxLayout* passwordLayout = new QHBoxLayout;
    passwordLabel->setBuddy(passwordEdit);
    passwordLayout->addWidget(passwordLabel);
    passwordLayout->addWidget(passwordEdit);

    QHBoxLayout* reEnterLayout = new QHBoxLayout;
    reEnterLabel->setBuddy(reEnterEdit);
    reEnterLayout->addWidget(reEnterLabel);
    reEnterLayout->addWidget(reEnterEdit);

    QHBoxLayout* emailLayout = new QHBoxLayout;
    emailLabel->setBuddy(emailEdit);
    emailLayout->addWidget(emailLabel);
    emailLayout->addWidget(emailEdit);

    QHBoxLayout* checkButLayout = new QHBoxLayout;
    checkButLayout->addStretch();
    checkButLayout->addWidget(checkBut);

    QHBoxLayout* butLayout = new QHBoxLayout;
    butLayout->addStretch();
    butLayout->addWidget(previousBut);
    butLayout->addWidget(clearBut);
    butLayout->addWidget(submitBut);

    mainLayout->addStretch();
    mainLayout->addLayout(nameLayout);
    mainLayout->addWidget(infoLabel);
    mainLayout->addLayout(usrNameLayout);
    mainLayout->addLayout(passwordLayout);
    mainLayout->addLayout(reEnterLayout);
    mainLayout->addLayout(emailLayout);
    mainLayout->addLayout(checkButLayout);
    mainLayout->addLayout(butLayout);
    mainLayout->addStretch();


    QHBoxLayout* paddingHL=new QHBoxLayout;
    QVBoxLayout* paddingVL=new QVBoxLayout;

    paddingHL->addStretch();
    paddingHL->addLayout(mainLayout);
    paddingHL->addStretch();

    paddingVL->addStretch();
    paddingVL->addLayout(paddingHL);
    paddingVL->addStretch();

    this->setLayout(paddingVL);
    setWindowFlags( ( (this->windowFlags() | Qt::CustomizeWindowHint)& ~Qt::WindowCloseButtonHint) );

    setMinimumSize(325,250);


}

regDia::~regDia()
{
}

void regDia::backToPrePage()
{
    this->hide();
    preWin->show();
    clearAll();

}

void regDia::clearAll()
{
    usrNameEdit->clear();
    passwordEdit->clear();
    reEnterEdit->clear();
    emailEdit->clear();

}

void regDia::enableSubmit(const QString & text)
{
    submitBut->setDisabled(text.isEmpty());
}

void regDia::GenerateQR()
{

    if(checkStatus==true)
    {
        //save the information
        saveTheAccinfo();
        d=new shareDis(this,seed);
        this->hide();
        QMessageBox::warning(this, tr("Warning"),tr("Please keep next page in secret!!!"),QMessageBox::Ok);
        //d->setSeed(seed);
        d->show();
    }
    else
    {
        QMessageBox::warning(this, tr("Warning"),tr("Need to pass the check first"),QMessageBox::Ok);
    }

}

void regDia::checkAcc()
{
    if(usrNameEdit->text().isEmpty())
    {
        QMessageBox::warning(this, tr("Warning"),tr("userName filed need to be filled"),QMessageBox::Ok);
        return;
    }
    if(passwordEdit->text().isEmpty())
    {
        QMessageBox::warning(this, tr("Warning"),tr("Password filed need to be filled"),QMessageBox::Ok);
        return;
    }
    if(passwordEdit->text()!=reEnterEdit->text())
    {
        QMessageBox::warning(this, tr("Warning"),tr("Password are not the same"),QMessageBox::Ok);
        return;
    }
    if (0==access("asset1", 0)) {
        // error processing here
        QMessageBox::warning(this, tr("Warning"),tr("Account has already exist."),QMessageBox::Ok);
        return;

    }
    QMessageBox::warning(this, tr("Success"),tr("Please click submit to continue"),QMessageBox::Ok);
    checkStatus=true;
}

void regDia::saveTheAccinfo()
{
    QFile file("asset1");
    QFile file1("assetmc");
    QFile file2("assetT");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        // error processing here
        QMessageBox::warning(this, tr("Warning"),tr("File writting error"),QMessageBox::Ok);
        return;

    }
    if (!file1.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        // error processing here
        QMessageBox::warning(this, tr("Warning"),tr("File writting error"),QMessageBox::Ok);
        return;

    }
    if (!file2.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        // error processing here
        QMessageBox::warning(this, tr("Warning"),tr("File writting error"),QMessageBox::Ok);
        return;

    }

    QTextStream ts(&file);
    QTextStream ts1(&file1);
    QTextStream ts2(&file2);

    ts2<<time(NULL);
    file2.close();


    QByteArray bb;
    bb.append(usrNameEdit->text());
    bb.append(passwordEdit->text());
    QString save=QCryptographicHash::hash((bb),QCryptographicHash::Sha1).toHex();
    QString mc = QCryptographicHash::hash((save.toUtf8()),QCryptographicHash::Sha1).toHex();
    mc = mc.mid(0,10);
    std::stringstream ss;
    ss<<std::hex<<save.toStdString();
    ss>>seed;
    seed%=100000;
    //d->setSeed(seed);
    ts1<<mc;
    ts<<save;
    file.close();
    file1.close();
    clearAll();
}
