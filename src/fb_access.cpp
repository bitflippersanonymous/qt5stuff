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
: QObject(parent), d_state(Sinit), d_timer(this), d_i(0) {

	connect(&d_timer, SIGNAL(timeout()), this, SLOT(stateHandler()));
	d_timer.start(1000);
    stateHandler();
}

FbAccess::~FbAccess() {
}

void FbAccess::stateHandler() {
	if ( d_nr.getPending() > 10 )
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
		getPhotos(d_friends.front());
		d_friends.pop_front();
		d_state = Swait;
		break;
	case SgetPhoto:
		getPhoto(d_photos.front());
		d_photos.pop_front();
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
	if ( reply->error() || !reply->isFinished() )
		qDebug() << "Error: " << reply->errorString();

	QByteArray bytes(reply->readAll());
	QJsonObject res(QJsonDocument::fromJson(bytes).object());
	qDebug() << "Json: " << res;
	return res;
}

void FbAccess::query(QUrl &url, const char *slot) {
	url.addQueryItem(access_token, d_access_token);
	qDebug() << url.path();
	QNetworkReply* reply = d_nr.makeRequest(url);
	if ( reply->error() ) {
		qDebug() << reply->errorString();
		reply->deleteLater();
		return;
	}
    connect(reply, SIGNAL(finished()), this, slot);
    connect(reply, SIGNAL(finished()), this, SLOT(stateHandler()));
}

void FbAccess::getFriends(const QString &id) {
	QUrl url;
	url.setUrl(fburl + id + "/friends", QUrl::StrictMode);
	url.addQueryItem("fields", "id");
	query(url, SLOT(handleFriends()));
}

void FbAccess::handleFriends() {
	QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
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
	query(url, SLOT(handlePhotos()));
}

void FbAccess::handlePhotos() {
	QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
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
	query(url, SLOT(handlePhoto()));
}

void FbAccess::handlePhoto() {
	QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
	QJsonObject json(makeJson(reply));
	reply->deleteLater();
	return savePhoto(json.value("picture").toString(), json.value("id").toString());
}

void FbAccess::savePhoto(QUrl url, const QString &id) {
	qDebug() << url.path();
	query(url, SLOT(handleSavePhoto));
}

void FbAccess::handleSavePhoto() {
	QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
	QFile file(makeFilename(id));
	file.open(QIODevice::WriteOnly);
    file.write(reply->readAll());
	reply->deleteLater();
    file.close();
}

QString FbAccess::makeFilename(const QString &id) {
	return "store/" + id + ".jpg";
}

bool FbAccess::fileExists(const QString &id) {
    return QFile::exists(makeFilename(id));
}
