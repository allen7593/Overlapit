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
#include "sharedis.h"


class regDia : public QDialog
{
    Q_OBJECT

public:
    regDia(QMainWindow *parent = 0);
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
    QPushButton* closeBut;

    shareDis* d;

    bool checkStatus;
};

#endif // REGDIA_H
