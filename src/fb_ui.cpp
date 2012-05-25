/*
 * FbSs
 *
 *  Created on: Apr 1, 2012
 *	Copyright 2012 Ryan Henderson
 *
 */


#include <QDebug>
#include <QGraphicsItem>
#include <QPixmap>
#include "fb_ui.h"

FbUi::FbUi()
	: d_view(&d_scene, this)
{
    setFocusPolicy(Qt::StrongFocus);
    resize(640,480);
    d_view.setFocusPolicy(Qt::NoFocus);
}

FbUi::~FbUi() {}

void FbUi::showImage(const QString &path) {
	d_scene.clear();
	const QGraphicsItem *item = d_scene.addPixmap(QPixmap(path, 0));
	d_scene.setSceneRect(item->boundingRect());
	d_view.fitInView(item, Qt::KeepAspectRatio);
}

void FbUi::resizeEvent(QResizeEvent *event) {
	d_view.resize(event->size());
}

void FbUi::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Left:
    	emit nextImage(-1);
        break;
    case Qt::Key_Right:
    	emit nextImage(+1);
        break;
    case Qt::Key_Escape:
//    	 hide();
   	 qApp->quit();
   	 break;
    default:
   	 break;
    }
}
