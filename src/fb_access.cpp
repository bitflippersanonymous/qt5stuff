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
#include <QDebug>
#include <QEventLoop>

const QString fburl = "https://graph.facebook.com/";
const char *access_token = "access_token";

FbAccess::FbAccess(QObject *parent)
: QObject(parent), d_state(Sinit) {

	connect(&d_timer, SIGNAL(timeout()), this, SLOT(stateHandler()));
    d_timer.start(5000);
    stateHandler();
}

FbAccess::~FbAccess() {
}

void FbAccess::stateHandler() {

	if ( d_nr.getPending() > 2 )
		return;

	switch ( d_state ) {
	case Sinit:
		getAccessToken();
		d_state = SgetFriends;
		break;
	case SgetFriends:
		getFriends("me");
		d_state = Swait;
		break;
	case SgetPhotos:
		getPhotos(d_friends.takeLast());
		d_state = Swait;
		break;
	case SgetPhoto:
		getPhoto(d_photos.takeLast());
		d_state = Swait;
		break;
	case Swait:
		if ( d_friends.size() )
			d_state = SgetPhotos;
		if ( d_photos.size() )
			d_state = SgetPhoto;
		break;
	default:
		break;
	}

}

void FbAccess::getAccessToken() {
	QFile dataFile("res/access_token");
	dataFile.open(QIODevice::ReadOnly);
	Q_ASSERT(dataFile.size());
	d_access_token = dataFile.readLine().trimmed();
	dataFile.close();
}

QJsonObject FbAccess::makeJson(QNetworkReply *reply) {
	if ( reply->error() )
		qDebug() << reply->errorString();

	QJsonObject res(QJsonDocument::fromJson(reply->readAll()).object());
	qDebug() << res;
	return res;
}

void FbAccess::query(QUrl &url, const char *slot) {
	url.addQueryItem(access_token, d_access_token);
	QNetworkReply* reply = d_nr.makeRequest(url);
	if ( reply->error() ) {
		qDebug() << reply->errorString();
		reply->deleteLater();
		return;
	}
    connect(&d_nr, SIGNAL(finishedRequest(QNetworkReply *)), this, slot);
}

void FbAccess::getFriends(const QString &id) {
	QUrl url;
	url.setUrl(fburl + id + "/friends", QUrl::StrictMode);
	url.addQueryItem("fields", "id");
	query(url, SLOT(handleFriends(QNetworkReply *)));
}

void FbAccess::handleFriends(QNetworkReply *reply) {
	const QJsonObject json = makeJson(reply);
	reply->deleteLater();
	if ( !json.value("data").isArray() ) // Handle Error
		return;

	foreach ( const QJsonValue &value, json.value("data").toArray()) {
		d_friends.push_back(value.toObject().value("id").toString());
	}
}

void FbAccess::getPhotos(const QString &id) {
	QUrl url;
	url.setUrl(fburl + id + "/photos", QUrl::StrictMode);
	url.addQueryItem("fields", "id");
	query(url, SLOT(handlePhotos(QNetworkReply *)));
}

void FbAccess::handlePhotos(QNetworkReply *reply) {
	const QJsonObject json = makeJson(reply);
	reply->deleteLater();

	foreach ( const QJsonValue &value, json.value("data").toArray()) {
		const QString &key = value.toObject().value("id").toString();
		if ( !fileExists(key) )
			d_photos.push_back(key);
	}
}

void FbAccess::getPhoto(const QString &id) {
	QUrl url;
	url.setUrl(fburl + id, QUrl::StrictMode);
	url.addQueryItem("fields", "id,picture");
	query(url, SLOT(handlePhoto(QNetworkReply *)));
}

void FbAccess::handlePhoto(QNetworkReply *reply) {
	QJsonObject json(makeJson(reply));
	reply->deleteLater();
	return savePhoto(json.value("picture").toString(), json.value("id").toString());
}

void FbAccess::savePhoto(QUrl url, const QString &id) {
	qDebug() << url.path();
	return;

/*
	query(url);
	QFile file(makeFilename(id));
	file.open(QIODevice::WriteOnly);
    file.write(reply->readAll());
    delete reply;
    file.close();
	return true;
	*/
}

QString FbAccess::makeFilename(const QString &id) {
	return "store/" + id + ".jpg";
}

bool FbAccess::fileExists(const QString &id) {
    return QFile::exists(makeFilename(id));
}
