#include "sharedis.h"

shareDis::shareDis(QWidget *parent,int seed)
    : QDialog(parent,Qt::FramelessWindowHint)
{

    preWin=parent;
    scanLabel = new QLabel(tr("Please scan the QR code"));
    QRLabel = new QLabel;

    share2=new QLabel;

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
    leftLayout->addStretch();

    mainLayout->addLayout(leftLayout);
    mainLayout->addWidget(share2);


    connect(preBut,SIGNAL(clicked()),this,SLOT(goback()));
    connect(verifyEdit,SIGNAL(textChanged(const QString&)),this,SLOT(validateBut(const QString&)));
    connect(verifyBut,SIGNAL(clicked()),this,SLOT(checkForValidity()));


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

    setMinimumSize(1150,550);
}

shareDis::~shareDis()
{
}

void shareDis::setSeed(int seed)
{
    std::ostringstream oss;
    oss<<seed;
    std::string setToSeed;
    setToSeed=oss.str();
    QRCode->setQRData(tr(setToSeed.c_str()));
    p.setKey(seed);

}

void shareDis::goback()
{
    this->hide();
    preWin->show();

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
    hashedVal=QCryptographicHash::hash((bb),QCryptographicHash::Sha1).toHex();
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
