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
#include <QPushButton>
#include <QKeyEvent>


FbSs::FbSs(QWidget *parent)
    : QWidget(parent)
{
    //ui.label_status->setText("Loading...");
	d_fb_access.start();
    ui.setupUi(this);
    setImage();
}

FbSs::~FbSs()
{
}

void FbSs::setImage() {

	delete ui.label_image->pixmap();
	const QPixmap *image = new QPixmap("res/robot.png");
	ui.label_image->setPixmap(*image);
}

void FbSs::mouseDoubleClickEvent ( QMouseEvent * event )
{
	(void)event;
	if ( isFullScreen() )
		showNormal();
	else
		showFullScreen();
};

 void FbSs::keyPressEvent(QKeyEvent *event)
 {
     switch (event->key()) {
     case Qt::Key_Left:
         break;
     case Qt::Key_Right:
         break;
     case Qt::Key_Escape:
    	 qApp->quit();
    	 break;
     default:
    	 QWidget::keyPressEvent(event);
    	 break;
     }
 }
