#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>

#include "recdia.h"
#include "regdia.h"
#include "loginform.h"
#include "settocenter.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void showTheRecovery();
    void showRegister();
    void showLogin();
    void clearAll();
    void enableSubmit(const QString& text);
    void checkForAcc();
private:
    //Labels for register
    QLabel* nameLabel;
    QLabel* userName;
    QLabel* password;
    QLabel* visualPic;

    //LineEditers
    QLineEdit* usrNameEdit;
    QLineEdit* passWordEdit;

    //push buttons
    QPushButton* submitButton;
    QPushButton* clearButton;
    QPushButton* forgetButton;
    QPushButton* registerButton;

    recDia* recWin;
    regDia* regWin;
    LoginForm* lDia;

    setToCenter stc;
};

#endif // MAINWINDOW_H
