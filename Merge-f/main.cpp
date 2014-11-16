#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include <QTextStream>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    QFile file("stylesheet.qss");
    file.open(QFile::ReadOnly);
    QTextStream filetext(&file);
    QString stylesheet=filetext.readAll();

    w.setStyleSheet(stylesheet);


    return a.exec();
}
