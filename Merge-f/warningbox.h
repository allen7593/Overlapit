#ifndef WARNINGBOX_H
#define WARNINGBOX_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

class warningBox : public QDialog
{
    Q_OBJECT
public:
    explicit warningBox(QWidget *parent = 0);
    warningBox(QString);

public slots:
    void hidewin();

private:
    QPushButton* okayBut;
    QLabel* warningLabel;

    QHBoxLayout* mainLayout;
    QVBoxLayout* butLayout;
};

#endif // WARNINGBOX_H
