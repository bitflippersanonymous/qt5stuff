#ifndef QT5STUFF_H
#define QT5STUFF_H

#include <QtWidgets/QMainWindow>
#include "ui_qt5stuff.h"

class qt5stuff : public QMainWindow
{
    Q_OBJECT

public:
    qt5stuff(QWidget *parent = 0);
    ~qt5stuff();

private:
    Ui::qt5stuffClass ui;
};

#endif // QT5STUFF_H
