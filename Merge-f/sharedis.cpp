#include "sharedis.h"
#include <iostream>
shareDis::shareDis(QWidget *parent,QString hashedSeed)
    : QDialog(parent,Qt::FramelessWindowHint)
{

    hexSeed=hashedSeed;
    std::stringstream ss;
    ss<<std::hex<<hashedSeed.toStdString();
    ss>>seed;
//    seed+=std::time(NULL);
//    seed=abs(seed);
    //seed%=100000;


    time = QTime(0,2,0);
    timer=new QTimer(this);
    timer->setInterval(1000);
    timeCount=1000;


    preWin=parent;
    scanLabel = new QLabel(tr("Please scan the QR code"));
    QRLabel = new QLabel;

    share2=new QLabel;
    QFont font;
    font.setPixelSize(20);



    timeLabel=new QLabel();
    timeWarning=new QLabel();
    timeLabel->setFont(font);
    timeWarning->setFont(font);
    timeWarning->setStyleSheet("color:red");

    //s2 = new QImage(48*6,24*6,QImage::Format_RGBA8888);
    verifyEdit = new QLineEdit;
    verifyBut = new QPushButton(tr("Verify"));
    preBut=new QPushButton(tr("Previous"));
    verifyBut->setDisabled(true);
    mainLayout = new QHBoxLayout;
    leftLayout = new QVBoxLayout;
    buttonLayout = new QHBoxLayout;

    QRCode = new QRWidget;
    setSeed(seed);
    //QRCode->setQRData(tr("89564"));
    QRCode->setMinimumWidth(150);
    QRCode->setMinimumHeight(150);
    //p.setKey(89564);
    p.excu();
    s2=p.getShare2();

    share2->setPixmap(QPixmap::fromImage(*s2));


    leftLayout->addWidget(scanLabel);
    leftLayout->addWidget(QRCode);
    leftLayout->addWidget(verifyEdit);

    buttonLayout->addStretch();
    buttonLayout->addWidget(preBut);
    buttonLayout->addWidget(verifyBut);

    leftLayout->addLayout(buttonLayout);
    leftLayout->addWidget(timeLabel);
    leftLayout->addWidget(timeWarning);
    leftLayout->addStretch();

    mainLayout->addLayout(leftLayout);
    mainLayout->addWidget(share2);


    connect(preBut,SIGNAL(clicked()),this,SLOT(goback()));
    connect(verifyEdit,SIGNAL(textChanged(const QString&)),this,SLOT(validateBut(const QString&)));
    connect(verifyBut,SIGNAL(clicked()),this,SLOT(checkForValidity()));
    connect(timer,SIGNAL(timeout()),this,SLOT(countDown()));
    timer->start();


    QHBoxLayout* paddingHL=new QHBoxLayout;
    QVBoxLayout* paddingVL=new QVBoxLayout;

    paddingHL->addStretch();
    paddingHL->addLayout(mainLayout);
    paddingHL->addStretch();

    paddingVL->addStretch();
    paddingVL->addLayout(paddingHL);
    paddingVL->addStretch();


    setLayout(paddingVL);
    setWindowFlags( ( (this->windowFlags() | Qt::CustomizeWindowHint)& ~Qt::WindowCloseButtonHint) );

    setMinimumSize(1250,550);
}

shareDis::~shareDis()
{
}

void shareDis::setSeed(int seed)
{/*
    QFile file("assetT");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Truncate)) {
        // error processing here
        QMessageBox::warning(this, tr("Warning"),tr("File Reading error"),QMessageBox::Ok);
        return;

    }
    QTextStream ts(&file);
    QString regTime;
    regTime=ts.readAll();*/

    string aesKey = "b7bd865cb99216307a49b2a6a7a66efd"; //128 bits key
    string aesIV = "ABCDEF0123456789";//128 bits
    string cipherText,plainText;

    //save hashed seed and encrypt it
    std::ofstream ts("asset1");
    plainText=hexSeed.toStdString();
    cipherText=CTR_AESEncryptStr(aesKey, aesIV, plainText.c_str());
    ts<<cipherText;
    plainText.clear();
    cipherText.clear();

    ts.close();
    //std::cout<<hexSeed.toStdString()<<std::endl;

    //save current register time

    std::ofstream ts2("assetT");

    std::ostringstream timeConv;
    timeConv<<std::time(NULL);

    plainText=timeConv.str();

    cipherText=CTR_AESEncryptStr(aesKey, aesIV, plainText.c_str());

    ts2<<cipherText;
    ts2.close();


    //read the registrer time
    ifstream file("assetT");
    file>>cipherText;
    plainText=CTR_AESDecryptStr(aesKey, aesIV, cipherText.c_str());


    std::stringstream ossT(std::stringstream::out|std::stringstream::in);
    ossT<<plainText;
    time_t rTime;


    ossT>>rTime;


    //compute the seed
    seed+=rTime;
    seed=abs(seed);
    seed%=100000;
    //cout<<seed<<endl;
    //get time difference
    int timeD=(std::time(NULL)-rTime)/120;

    std::ostringstream oss;
    oss<<seed;
    std::string setToSeed;
    setToSeed=oss.str();



    QRCode->setQRData(tr(setToSeed.c_str()));



    //compute final seed
    std::ostringstream ossC;

    ossC<<timeD;
    setToSeed+=ossC.str();

    std::istringstream iss(setToSeed);
    iss>>seed;
    //std::cout<<seed<<endl;
    p.setKey(seed);

}

void shareDis::goback()
{
    this->hide();
    preWin->show();
    timer->stop();

}

void shareDis::validateBut(const QString & text)
{
    verifyBut->setDisabled(text.isEmpty());
}

void shareDis::checkForValidity()
{
    QString secretH;
    QString hashedVal;
    QByteArray bb=verifyEdit->text().toUtf8();
    hashedVal=QCryptographicHash::hash((bb),QCryptographicHash::Md5).toHex();
    secretH=p.getHashedSecret();
    if(hashedVal==secretH)
    {
        //qDebug<<"true";
        QMessageBox::StandardButton reply;
        reply=QMessageBox::information(this,tr("Sucess!"),tr("Conguatulations! Please close the program."),QMessageBox::Ok);
        if(reply==QMessageBox::Ok)
            exit(0);
    }
    else
    {
        //qDebug<<"false";
        QMessageBox::warning(this, tr("Warning"),tr("Invalid code,please try again"),QMessageBox::Ok);
    }
}


void shareDis::countDown()
{
    QString time_Display;


    time_Display=time.toString("hh:mm:ss");
    timeLabel->setText(time_Display);
    if(time.minute()==1 && time.second()==0)
        timeWarning->setText(tr("You have 1 minute left"));
    else if(time.minute()==0 && time.second()==30)
        timeWarning->setText(tr("You have 30 seconds left"));
    else if(time.minute()==0 && time.second()==0)
    {

//        QMessageBox::StandardButton retvel;
//        retvel=QMessageBox::warning(this,tr("Time out"),tr("You have no time left press Ok to refresh the page!"),QMessageBox::Ok);
//        if(retvel==QMessageBox::Ok)
        {
            //do something
            this->close();
            QFile file("stylesheet.qss");
            file.open(QFile::ReadOnly);
            QTextStream filetext(&file);
            QString stylesheet=filetext.readAll();
            shareDis *newWindow;
            newWindow=new shareDis(preWin,hexSeed);
            newWindow->setStyleSheet(stylesheet);
            //setCenterOfApplication(newWindow);
            newWindow->show();
        }
    }
    time=time.addSecs(-1);
}
