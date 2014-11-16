#ifndef SETTOCENTER_H
#define SETTOCENTER_H

#include <QWidget>
#include <QMainWindow>
#include <QDesktopWidget>
#include <QApplication>

class setToCenter
{
public:
    setToCenter();

    void centerTheWin(QWidget*);
    void centerTheWin(QMainWindow*);

};

#endif // SETTOCENTER_H
