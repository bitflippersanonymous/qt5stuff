/*
 * FbSs
 *
 *  Created on: Apr 1, 2012
 *	Copyright 2012 Ryan Henderson
 *
 */

#ifndef FBSSUI_H_
#define FBSSUI_H_

#include <QResizeEvent>
#include "ui_FbSs.h"
#include "fb_graphics_view.h"

class FbUi : public QWidget {
    Q_OBJECT

    QGraphicsScene 	d_scene;
    FbGraphicsView 	d_view;

signals:
    void nextImage(int direction);

protected:
    void resizeEvent(QResizeEvent *event);
    void keyPressEvent(QKeyEvent *event);

public:
	FbUi();
	virtual ~FbUi();
	void showImage(const QString &path);
};

#endif /* FBSSUI_H_ */
