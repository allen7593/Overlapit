#ifndef REGDIA_H
#define REGDIA_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QCryptographicHash>
#include <sstream>
#include <ctime>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include "sharedis.h"
#include "aes_ctr.h"
#include "rexh.h"


class regDia : public QDialog
{
    Q_OBJECT

public:
    regDia(QMainWindow *parent = 0);
    regDia(QWidget *parent = 0, QString accName="");
    ~regDia();

private slots:
    void backToPrePage();
    void clearAll();
    void enableSubmit(const QString&);
    void GenerateQR();
    void checkAcc();
private:
    void saveTheAccinfo();

    int seed;
    QLabel* nameLabel;
    QLabel* infoLabel;
    QLabel* usrNameLabel;
    QLabel* passwordLabel;
    QLabel* reEnterLabel;
    QLabel* emailLabel;
    QLabel* imgLabel;


    QLineEdit* usrNameEdit;
    QLineEdit* passwordEdit;
    QLineEdit* reEnterEdit;
    QLineEdit* emailEdit;

    QPushButton* checkBut;
    QPushButton* submitBut;
    QPushButton* clearBut;
    QPushButton* previousBut;

    QMainWindow* preWin;
    QWidget* preDia;
    QPushButton* closeBut;

    shareDis* d;
    QString accName;
    QString hashedVal;
    bool checkStatus;
};

#endif // REGDIA_H
