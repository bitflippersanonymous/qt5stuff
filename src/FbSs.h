/*
 * FbSs
 *
 *  Created on: Apr 1, 2012
 *	Copyright 2012 Ryan Henderson
 *
 */

#ifndef QT5STUFF_H
#define QT5STUFF_H

#include <QFileInfoList>
#include <QSettings>
#include "fb_ui.h"
#include "fb_access.h"
#include "fb_graphics_view.h"

class FbSs : public QObject
{
    Q_OBJECT

    FbUi			d_fb_ui;
    FbAccess		d_fb_access;
    QStringList		d_filenames;
    int				d_current;
    static const QString	s_store;

public slots:
	void nextImage(int direction);

private:
    void writeSettings() const;
    void readSettings();

public:
    FbSs();
    ~FbSs();
    void updateStore();
};


#endif // QT5STUFF_H

