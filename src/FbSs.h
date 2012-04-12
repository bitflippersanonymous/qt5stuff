#ifndef QT5STUFF_H
#define QT5STUFF_H

#include "fb_ui.h"
#include "fb_access.h"
#include "fb_graphics_view.h"

class FbSs : public QObject
{
    Q_OBJECT

    FbUi			d_fb_ui;
   // FbAccess		d_fb_access;

public slots:
	void nextImage();

public:
    FbSs();

};


#endif // QT5STUFF_H

