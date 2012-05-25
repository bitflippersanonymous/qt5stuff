/*
 * FbSs
 *
 *  Created on: Apr 1, 2012
 *	Copyright 2012 Ryan Henderson
 *
 */

#include <QDebug>
#include <QDir>
#include "FbSs.h"

const QString FbSs::s_store = "store";

FbSs::FbSs() : d_current(0)
{
	connect(&d_fb_ui, SIGNAL(nextImage(int)), this, SLOT(nextImage(int)));
	updateStore();
	readSettings();
	nextImage(0);
	d_fb_ui.show();
	d_fb_ui.setFocus();
}

FbSs::~FbSs()
{
	writeSettings();
}

void FbSs::writeSettings() const {
	QSettings 		settings;
	settings.beginGroup("MainWindow");
	settings.setValue("size", d_fb_ui.size());
	settings.setValue("pos", d_fb_ui.pos());
	settings.endGroup();
}

void FbSs::readSettings() {
	QSettings 		settings;
    settings.beginGroup("MainWindow");
    d_fb_ui.resize(settings.value("size", QSize(400, 400)).toSize());
    d_fb_ui.move(settings.value("pos", QPoint(200, 200)).toPoint());
    settings.endGroup();
}

void FbSs::updateStore() {
	d_filenames.clear();
	d_filenames = QDir(s_store).entryList(QDir::Files);
}

void FbSs::nextImage(int direction) {
	if ( !d_filenames.size() )
		return;

	d_current+=direction;
	if ( d_current >= d_filenames.size())
		d_current = 0;
	if ( d_current < 0 )
		d_current = d_filenames.size()-1;

	d_fb_ui.showImage(s_store + "/" + d_filenames[d_current]);
}
