#ifndef QT5STUFF_H
#define QT5STUFF_H

#include "ui_FbSs.h"
#include "fb_access.h"
#include "fb_graphics_view.h"

class QPushButton;

class FbSs : public QWidget
{
    Q_OBJECT

    Ui::FbSs 		ui;
    QGraphicsScene 	d_scene;
    FbGraphicsView 	d_view;
    FbAccess		d_fb_access;

private:
    void showImage(const QString &path);

public:
    FbSs(QWidget *parent = 0);

protected:
	void keyPressEvent(QKeyEvent *event);
    void resizeEvent(QResizeEvent *event);
};


#endif // QT5STUFF_H

