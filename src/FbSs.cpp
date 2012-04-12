/*
 * network_reader.h
 *
 *  Created on: Apr 3, 2012
 *      Author: vmplanet
 *
 *
 */

#include <QKeyEvent>
#include "FbSs.h"

FbSs::FbSs()
{
	const QString path("store/536239_10150706845599936_577604935_9145859_1652936957_n.jpg");
	d_fb_ui.show();
	d_fb_ui.setFocus();
	d_fb_ui.showImage(path);
}


void FbSs::nextImage() {
	d_fb_ui.showImage(path);
}
