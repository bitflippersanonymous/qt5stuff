/*
 * FbSs
 *
 *  Created on: Apr 1, 2012
 *	Copyright 2012 Ryan Henderson
 *
 */


#include "fb_graphics_view.h"


void FbGraphicsView::resizeEvent(QResizeEvent *event) {
	(void)event;
	if ( items().size() )
		fitInView(items().back(), Qt::KeepAspectRatio);
}

void FbGraphicsView::mouseDoubleClickEvent ( QMouseEvent * event )
{

	(void)event;
	if ( parentWidget()->isFullScreen() )
		parentWidget()->showNormal();
	else
		parentWidget()->showFullScreen();
};
