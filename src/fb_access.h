/*
 * FbSs
 *
 *  Created on: Apr 1, 2012
 *	Copyright 2012 Ryan Henderson
 *
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

class Response : public QObject {
	Q_OBJECT
	QNetworkReply	*d_reply;
	const QString 	d_id;
public:
	Response(QNetworkReply *reply, const QString &id) : d_reply(reply), d_id(id) {}
	QNetworkReply *reply() const { return d_reply; }
	const QString &id() const { return d_id; }
};

 class FbAccess : public QObject
 {
	 Q_OBJECT

	 enum State { Sinit, SgetFriends, SgetPhotos, SgetPhoto, Swait, Serror, Send };

	 QString 		d_access_token;
	 NetworkReader 	d_nr;
	 QList<QString>	d_friends;
	 QList<QString>	d_photos;
	 State			d_state;
	 QTimer 		d_timer;


private slots:
    void stateHandler();
    void handleFriends();
    void handlePhotos();
    void handlePhoto();
    void handleSavePhoto(QObject *object);
    void handleLogin();

private:
    QString makeFilename(const QString &id);
    bool fileExists(const QString &id);
    QJsonObject makeJson();
    void getAccessToken();
    void startLogin();
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
