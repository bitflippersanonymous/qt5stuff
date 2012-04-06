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
#include <QtCore>

FbSs::FbSs(QWidget *parent)
    : QWidget(parent), d_b(new QPushButton(this))
{
	resize(200, 200);
	d_fb_access.start();
}

FbSs::~FbSs()
{
	delete d_b;
}
