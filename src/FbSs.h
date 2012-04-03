#ifndef QT5STUFF_H
#define QT5STUFF_H

#include "ui_FbSs.h"
#include "network_reader.h"
#include <QtWidgets/QMainWindow>

class FbSs : public QMainWindow
{
    Q_OBJECT

public:
    FbSs(QWidget *parent = 0);
    ~FbSs();

private:
    Ui::FbSs ui;
};



#endif // QT5STUFF_H

