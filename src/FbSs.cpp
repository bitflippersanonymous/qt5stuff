/*
 * network_reader.h
 *
 *  Created on: Apr 3, 2012
 *      Author: vmplanet
 *
 *
 */

#include "FbSs.h"
#include "FbObject.h"
#include <QFile>
#include <QJsonObject>
#include <QStateMachine>
#include <QPushButton>
#include <QDebug>
#include <QtCore>
#include <QtConcurrentRun>
#include <QFuture>
#include <QFutureWatcher>
#include <QNetworkReply>


const QString fburl = "https://graph.facebook.com/";
const char *access_token = "access_token";

FbSs::FbSs(QWidget *parent)
    : QWidget(parent), d_nr(0), d_b(new QPushButton(this))
{
	resize(200, 200);
    QFile dataFile("res/access_token");
    dataFile.open(QIODevice::ReadOnly);
    Q_ASSERT(dataFile.size());
    d_access_token = dataFile.readLine().trimmed();
    dataFile.close();

	QFuture<void> future = QtConcurrent::run(this, &FbSs::photoThread);
}

FbSs::~FbSs()
{
	delete d_b;
	delete d_nr;
}

void FbSs::photoThread() {
	d_nr = new NetworkReader();
	getFriends("me");
}

QJsonObject FbSs::makeJson(QNetworkReply *reply) {
	return QJsonDocument::fromJson(reply->readAll()).object();
}

QNetworkReply* FbSs::query(QUrl &url) {
	url.addQueryItem(access_token, d_access_token);
	return d_nr->makeRequest(url);
}

bool FbSs::getFriends(const QString &id) {
	QUrl url;
	url.setUrl(fburl + id + "/friends", QUrl::StrictMode);
	url.addQueryItem("fields", "id");
	QNetworkReply *reply;
	if ( !(reply = query(url)) )
		return false;
	foreach ( const QJsonValue &value, makeJson(reply).value("data").toArray()) {
		getPhotos(value.toObject().value("id").toString());
		break;
	}
	return true;
}

bool FbSs::getPhotos(const QString &id) {
	QUrl url;
	url.setUrl(fburl + id + "/photos", QUrl::StrictMode);
	url.addQueryItem("fields", "id");
	QNetworkReply *reply;
	if ( !(reply = query(url)) )
		return false;
	foreach ( const QJsonValue &value, makeJson(reply).value("data").toArray()) {
		const QString &key = value.toObject().value("id").toString();
		if ( !fileExists(key) )
			getPhoto(key);
	}
	return true;
}

bool FbSs::getPhoto(const QString &id) {
	QUrl url;
	url.setUrl(fburl + id, QUrl::StrictMode);
	url.addQueryItem("fields", "id,picture");
	QNetworkReply *reply;
	if ( !(reply = query(url)) )
		return false;
	QJsonObject json(makeJson(reply));
	return savePhoto(json.value("picture").toString(), json.value("id").toString());
}

bool FbSs::savePhoto(QUrl url, const QString &id) {
	QNetworkReply *reply;
	if ( !(reply = query(url)) )
		return false;

	QFile file(makeFilename(id));
	file.open(QIODevice::WriteOnly);
    file.write(reply->readAll());
	file.close();

	return true;
}

QString FbSs::makeFilename(const QString &id) {
	return "store/" + id + ".jpg";
}

bool FbSs::fileExists(const QString &id) {
    return QFile::exists(makeFilename(id));
}
