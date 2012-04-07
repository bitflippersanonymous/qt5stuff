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

FbSs::FbSs(QWidget *parent)
    : QWidget(parent), d_b(new QPushButton(this))
{
	d_fb_access.start();
	resize(200, 200);

}

FbSs::~FbSs()
{
	delete d_b;
}
