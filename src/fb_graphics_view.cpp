/*
 * fb_graphics_view.cpp
 *
 *  Created on: Apr 11, 2012
 *      Author: vmplanet
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
