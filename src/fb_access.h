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

class QJsonObject;

 class FbAccess : public QThread
 {
     Q_OBJECT

public:
    typedef unsigned long long FbId;
    typedef QHash<const FbAccess::FbId, FbAccess *> FbHash;
    typedef QSet<const FbAccess::FbId> FbSet;

    QString 		d_access_token;
    NetworkReader 	*d_nr;
    QMutex			d_mutex;
    bool			d_abort;
    QWaitCondition	d_condition;

private:
    QString makeFilename(const QString &id);
    bool fileExists(const QString &id);
    QJsonObject makeJson(QNetworkReply *reply);
    void getAccessToken();

public:
    FbAccess(QObject *parent = 0);
    virtual ~FbAccess();
    void run();
    QNetworkReply* query(QUrl &url);
    bool getFriends(const QString &id);
    bool getPhotos(const QString &id);
    bool getPhoto(const QString &id);
    bool savePhoto(QUrl url, const QString &id);
};

#endif /* FBOBJECT_H_ */
