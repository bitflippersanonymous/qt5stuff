#ifndef QT5STUFF_H
#define QT5STUFF_H

#include "ui_FbSs.h"
#include "fb_access.h"

class QPushButton;

class FbSs : public QWidget
{
    Q_OBJECT

    Ui::FbSs 		ui;
    FbAccess		d_fb_access;

private:
    void setImage();

public:
    FbSs(QWidget *parent = 0);
    ~FbSs();

    void mouseDoubleClickEvent ( QMouseEvent * event );
	void keyPressEvent(QKeyEvent *event);
};


#endif // QT5STUFF_H

