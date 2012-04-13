/*
 * FbObject.h
 *
 *  Created on: Apr 3, 2012
 *      Author: george
 */

#ifndef FBOBJECT_H_
#define FBOBJECT_H_

#include "network_reader.h"

#include <QObject>
#include <QHash>
#include <QSet>
#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QUrl>
#include <QNetworkReply>
#include <QTimer>

class QJsonObject;

 class FbAccess : public QObject
 {
	 Q_OBJECT

	 enum State { Sinit, SgetFriends, SgetPhotos, SgetPhoto, Swait, Send };

	 QString 		d_access_token;
	 NetworkReader 	d_nr;
	 QList<QString>	d_friends;
	 QList<QString>	d_photos;
	 State			d_state;
	 QTimer 		d_timer;
	 int			d_i;

public slots:
    void stateHandler();
    void handleFriends();
    void handlePhotos();
    void handlePhoto();
    void handleSavePhoto(const QString &id);

private:
    QString makeFilename(const QString &id);
    bool fileExists(const QString &id);
    QJsonObject makeJson(QNetworkReply *reply);
    void getAccessToken();
    void query(QUrl &url, const char *slot);
    void getFriends(const QString &id);
    void getPhotos(const QString &id);
    void getPhoto(const QString &id);
    void savePhoto(QUrl url, const QString &id);

public:
    FbAccess(QObject *parent = 0);
    virtual ~FbAccess();


};

#endif /* FBOBJECT_H_ */
