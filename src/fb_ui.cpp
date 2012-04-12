/*
 * FbSsUi.cpp
 *
 *  Created on: Apr 12, 2012
 *      Author: vmplanet
 */

#include <QDebug>
#include <QGraphicsItem>
#include <QPixmap>
#include "fb_ui.h"

FbUi::FbUi()
	: d_view(&d_scene, this)
{
    setFocusPolicy(Qt::StrongFocus);
}

FbUi::~FbUi() {
}

void FbUi::showImage(const QString &path) {
	d_scene.clear();
	d_scene.addPixmap(QPixmap(path, 0));
}

void FbUi::resizeEvent(QResizeEvent *event) {
	 d_view.resize(event->size());
}

void FbUi::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Left:
        break;
    case Qt::Key_Right:
    	emit nextImage();
        break;
    case Qt::Key_Escape:
//    	 hide();
   	 qApp->quit();
   	 break;
    default:
   	 break;
    }
}
