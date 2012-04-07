#ifndef QT5STUFF_H
#define QT5STUFF_H

#include "ui_FbSs.h"
#include "fb_access.h"
#include <QPushButton>

class FbSs : public QWidget
{
    Q_OBJECT

    Ui::FbSs 		ui;
    QPushButton 	*d_b;
    FbAccess		d_fb_access;

public:
    FbSs(QWidget *parent = 0);
    ~FbSs();
};



#endif // QT5STUFF_H

