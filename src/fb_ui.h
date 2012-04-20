/*
 * FbSs
 *
 *  Created on: Apr 1, 2012
 *	Copyright 2012 Ryan Henderson
 *
 */

#ifndef FBSSUI_H_
#define FBSSUI_H_

#include <QWebView>
#include <QResizeEvent>
#include "ui_FbSs.h"
#include "fb_graphics_view.h"

class FbUi : public QWidget {
    Q_OBJECT

    QGraphicsScene 	d_scene;
    FbGraphicsView 	d_view;
    QWebView		*d_webview;

signals:
    void nextImage(int direction);

protected:
    void resizeEvent(QResizeEvent *event);
    void keyPressEvent(QKeyEvent *event);

public:
	FbUi();
	virtual ~FbUi();
	void showImage(const QString &path);
	void showLogin();
};

#endif /* FBSSUI_H_ */
