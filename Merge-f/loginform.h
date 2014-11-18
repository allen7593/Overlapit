#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QMainWindow>
#include <fstream>
#include <QMessageBox>
#include <iostream>
#include <unistd.h>
#include "regdia.h"

class LoginForm : public QDialog
{
    Q_OBJECT

public:
    LoginForm(QMainWindow *parent = 0,QString accName="");
    ~LoginForm();

private slots:
    void backToPre();
    void turnOn();
    void turnOff();
    void resetPassword();
    void resetPic();
    void restoreSys();

private:
    QPushButton* restoreBut;
    QPushButton* newDevice;
    QPushButton* resetPass;
    QPushButton* onBut;
    QPushButton* offBut;
    QPushButton* preBut;

    QLabel* infoLabel;
    QLabel* onOffLabel;

    QVBoxLayout* mainLayout;
    QHBoxLayout* onOffLayout;
    QHBoxLayout* infoLayout;

    QMainWindow* preWin;
    QString accName;
    std::string homePath;

};

#endif // LOGINFORM_H
