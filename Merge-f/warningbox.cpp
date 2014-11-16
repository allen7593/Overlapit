#include "warningbox.h"

warningBox::warningBox(QWidget* parent):
    QDialog(parent)
{
    okayBut = new QPushButton(tr("OK"));

    warningLabel = new QLabel(tr("Warning"));

    mainLayout = new QHBoxLayout;
    butLayout = new QVBoxLayout;

    butLayout->addStretch();
    butLayout->addWidget(okayBut);

    mainLayout->addWidget(warningLabel);
    mainLayout->addLayout(butLayout);

    connect(okayBut,SIGNAL(clicked()),this,SLOT(hidewin()));
    show();

}

warningBox::warningBox(QString parent)
{

    okayBut = new QPushButton(tr("OK"));

    warningLabel = new QLabel(parent);
    warningLabel->setBuddy(okayBut);

    mainLayout = new QHBoxLayout;
    butLayout = new QVBoxLayout;

    connect(okayBut,SIGNAL(clicked()),this,SLOT(hidewin()));

    butLayout->addStretch();
    butLayout->addWidget(okayBut);

    mainLayout->addWidget(warningLabel);
    mainLayout->addLayout(butLayout);


    show();
}

void warningBox::hidewin()
{
    this->hide();

}
