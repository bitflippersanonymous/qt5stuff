/*
 * network_reader.h
 *
 *  Created on: Apr 3, 2012
 *      Author: vmplanet
 *
 *
 */

#include "FbSs.h"
#include <QDebug>
#include <QKeyEvent>
#include <QGraphicsItem>
#include <QPixmap>

FbSs::FbSs(QWidget *parent)
    : QWidget(parent), d_view(&d_scene, this)
{
	d_fb_access.start();
	const QString path("store/536239_10150706845599936_577604935_9145859_1652936957_n.jpg");
    showImage(path);
	ui.setupUi(this);
}

void FbSs::showImage(const QString &path) {
	d_scene.clear();
	d_scene.addPixmap(QPixmap(path, 0));
}

 void FbSs::keyPressEvent(QKeyEvent *event)
 {
     switch (event->key()) {
     case Qt::Key_Left:
         break;
     case Qt::Key_Right:
         break;
     case Qt::Key_Escape:
    	 hide();
    	 qApp->quit();
    	 break;
     default:
    	 QWidget::keyPressEvent(event);
    	 break;
     }
 }

 void FbSs::resizeEvent(QResizeEvent *event) {
	 d_view.resize(event->size());
 }

