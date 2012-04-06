/*
 * FbObject.cpp
 *
 *  Created on: Apr 3, 2012
 *      Author: george
 */

#include "fb_access.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QEventLoop>
#include <QDebug>

const QString fburl = "https://graph.facebook.com/";
const char *access_token = "access_token";

FbAccess::FbAccess(QObject *parent)
: QThread(parent), d_nr(0) {
}

FbAccess::~FbAccess() {
	delete d_nr;
}

void FbAccess::run() {
	d_nr = new NetworkReader();
	getAccessToken();
	getFriends("me");
}

void FbAccess::getAccessToken() {
	QFile dataFile("res/access_token");
	dataFile.open(QIODevice::ReadOnly);
	Q_ASSERT(dataFile.size());
	d_access_token = dataFile.readLine().trimmed();
	dataFile.close();
}

QJsonObject FbAccess::makeJson(QNetworkReply *reply) {
	return QJsonDocument::fromJson(reply->readAll()).object();
}

QNetworkReply* FbAccess::query(QUrl &url) {
	url.addQueryItem(access_token, d_access_token);
	QNetworkReply* reply = d_nr->makeRequest(url);
	QEventLoop loop;
	connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
	loop.exec();
	return reply;
}

bool FbAccess::getFriends(const QString &id) {
	QUrl url;
	url.setUrl(fburl + id + "/friends", QUrl::StrictMode);
	url.addQueryItem("fields", "id");
	QNetworkReply *reply; // @@@ Need to delete
	if ( !(reply = query(url)) )
		return false;
	const QJsonObject json = makeJson(reply);
	qDebug() << json;
	if ( !json.value("data").isArray() )
		return false;
	foreach ( const QJsonValue &value, json.value("data").toArray()) {
		getPhotos(value.toObject().value("id").toString());
	}
	return true;
}

bool FbAccess::getPhotos(const QString &id) {
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

bool FbAccess::getPhoto(const QString &id) {
	QUrl url;
	url.setUrl(fburl + id, QUrl::StrictMode);
	url.addQueryItem("fields", "id,picture");
	QNetworkReply *reply;
	if ( !(reply = query(url)) )
		return false;
	QJsonObject json(makeJson(reply));
	return savePhoto(json.value("picture").toString(), json.value("id").toString());
}

bool FbAccess::savePhoto(QUrl url, const QString &id) {
	QNetworkReply *reply;
	if ( !(reply = query(url)) )
		return false;

	QFile file(makeFilename(id));
	file.open(QIODevice::WriteOnly);
    file.write(reply->readAll());
	file.close();

	return true;
}

QString FbAccess::makeFilename(const QString &id) {
	return "store/" + id + ".jpg";
}

bool FbAccess::fileExists(const QString &id) {
    return QFile::exists(makeFilename(id));
}
