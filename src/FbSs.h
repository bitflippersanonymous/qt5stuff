#ifndef QT5STUFF_H
#define QT5STUFF_H

#include "ui_FbSs.h"
#include "fb_access.h"
#include "fb_graphics_view.h"

class FbSs : public QObject
{
    Q_OBJECT

    QGraphicsScene 	d_scene;
    FbGraphicsView 	d_view;
    FbAccess		d_fb_access;

private:
    void showImage(const QString &path);

protected:
	void keyPressEvent(QKeyEvent *event);
    void resizeEvent(QResizeEvent *event);

public:
    FbSs();

};


#endif // QT5STUFF_H

