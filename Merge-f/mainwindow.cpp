#include "mainwindow.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QImage>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent,Qt::FramelessWindowHint)
{
    //create the instance of labels
    nameLabel = new QLabel(tr("Login"));
    userName = new QLabel(tr("User Name:"));
    password = new QLabel(tr("Password:"));
    visualPic = new QLabel;

    //create the instance of line editers
    usrNameEdit=new QLineEdit;
    passWordEdit=new QLineEdit;
    passWordEdit->setEchoMode(QLineEdit::Password);

    //create the instace for buttons
    submitButton = new QPushButton(tr("&Submit"));
    submitButton->setDisabled(true);
    clearButton = new  QPushButton(tr("&Clear"));
    forgetButton = new QPushButton(tr("Forget Password"));
    registerButton = new QPushButton(tr("Register"));
    QPushButton* closeBut=new QPushButton(tr("Close"));

    QImage* image=new QImage(200,100,QImage::Format_RGBA8888);

    image->load("sharet.png");

    QSize size(1000,500);

    visualPic->setPixmap(QPixmap::fromImage(image->scaled(size,Qt::KeepAspectRatio,Qt::FastTransformation)));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    QVBoxLayout *leftLayout = new QVBoxLayout;

    QHBoxLayout *nameLayout = new QHBoxLayout;
    QHBoxLayout *userNameLayout= new QHBoxLayout;
    QHBoxLayout *passwordLayout= new QHBoxLayout;
    QHBoxLayout *submitLayout= new QHBoxLayout;
    QHBoxLayout *centerLayout= new QHBoxLayout;

    connect(forgetButton,SIGNAL(clicked()),this,SLOT(showTheRecovery()));
    connect(clearButton,SIGNAL(clicked()),this,SLOT(clearAll()));
    connect(usrNameEdit,SIGNAL(textChanged(const QString&)),this,SLOT(enableSubmit(const QString&)));
    connect(passWordEdit,SIGNAL(textChanged(const QString&)),this,SLOT(enableSubmit(const QString&)));
    connect(submitButton,SIGNAL(clicked()),this,SLOT(showLogin()));
    connect(registerButton,SIGNAL(clicked()),this,SLOT(showRegister()));
    connect(closeBut,SIGNAL(clicked()),this,SLOT(close()));


    nameLayout->addStretch();
    nameLayout->addWidget(nameLabel);
    nameLayout->addStretch();


    userName->setBuddy(usrNameEdit);
    userNameLayout->addWidget(userName);
    userNameLayout->addWidget(usrNameEdit);

    password->setBuddy(passWordEdit);
    passwordLayout->addWidget(password);
    passwordLayout->addWidget(passWordEdit);

    submitLayout->addWidget(submitButton);
    submitLayout->addWidget(clearButton);

    QImage* logoImg=new QImage(987,414,QImage::Format_RGBA8888);
    logoImg->load("logo.png");
    QSize s(300,150);



    QLabel *LogoLaybel=new QLabel;

    LogoLaybel->setPixmap(QPixmap::fromImage(logoImg->scaled(s,Qt::KeepAspectRatio,Qt::FastTransformation)));

    QFont font;
    font.setPixelSize(60);

    LogoLaybel->setFont(font);
    LogoLaybel->setMinimumHeight(30);
    LogoLaybel->setMinimumWidth(150);


    leftLayout->addWidget(LogoLaybel);
    leftLayout->addLayout(userNameLayout);
    leftLayout->addLayout(passwordLayout);
    leftLayout->addLayout(submitLayout);
    leftLayout->addWidget(forgetButton);
    leftLayout->addWidget(registerButton);
    leftLayout->addWidget(closeBut);

    centerLayout->addLayout(leftLayout);
    centerLayout->addWidget(visualPic);

    mainLayout->addLayout(nameLayout);
    mainLayout->addLayout(centerLayout);

    QWidget* centerWindow=new QWidget;
    this->setCentralWidget(centerWindow);

    QHBoxLayout* paddingHL=new QHBoxLayout;
    QVBoxLayout* paddingVL=new QVBoxLayout;

    paddingHL->addStretch();
    paddingHL->addLayout(mainLayout);
    paddingHL->addStretch();

    paddingVL->addStretch();
    paddingVL->addLayout(paddingHL);
    paddingVL->addStretch();

    centerWindow->setLayout(paddingVL);

    setMinimumSize(1350,575);

    this->setWindowTitle(tr("LOGIN"));

    stc.centerTheWin(this);
}

MainWindow::~MainWindow()
{
}

void MainWindow::showTheRecovery()
{
    this->hide();
    recWin = new recDia(this);
    recWin->show();

}

void MainWindow::clearAll()
{

    usrNameEdit->clear();
    passWordEdit->clear();
}

void MainWindow::enableSubmit(const QString& text)
{
    submitButton->setDisabled(text.isEmpty());
}

void MainWindow::checkForAcc()
{

}

void MainWindow::showRegister()
{
    this->hide();
    regWin = new regDia(this);
    regWin->show();

}

void MainWindow::showLogin()
{
    if(access("asset1", 0)==0)
    {

//        QFile file("asset1");
//        if (!file.open(QIODevice::ReadOnly | QIODevice::Truncate)) {
//            // error processing here
//            QMessageBox::warning(this, tr("Warning"),tr("File Reading error"),QMessageBox::Ok);
//            return;

//        }


//        QTextStream ts(&file);
        QByteArray aa;
//        QString bb;
//        bb=ts.readAll();

        string aesKey = "b7bd865cb99216307a49b2a6a7a66efd"; //128 bits key
        string aesIV = "ABCDEF0123456789";//128 bits
        string cipherText,plainText;

        ifstream file("asset1");
        file>>cipherText;
        plainText=CTR_AESDecryptStr(aesKey, aesIV, cipherText.c_str());

        aa.append(usrNameEdit->text());
        aa.append(passWordEdit->text());
        QString hased=QCryptographicHash::hash((aa),QCryptographicHash::Md5).toHex();
        if(hased.toStdString()==plainText)
        {
            this->hide();
            lDia = new LoginForm(this,usrNameEdit->text());
            lDia->show();
        }
        else
        {
            QMessageBox::warning(this, tr("Warning"),tr("Wrong account or password"),QMessageBox::Ok);
        }
        file.close();

    }
    else
    {
        QMessageBox::warning(this, tr("Warning"),tr("No account exist"),QMessageBox::Ok);
    }

    passWordEdit->clear();


}
