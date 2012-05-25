/*
 * FbSs
 *
 *  Created on: Apr 1, 2012
 *	Copyright 2012 Ryan Henderson
 *
 */


#include "fb_access.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include <QEventLoop>
#include <QSignalMapper>

const QString fburl = "https://graph.facebook.com/";
const char *loginurl = "https://www.facebook.com/dialog/oauth?redirect_uri=https://www.facebook.com/connect/login_success.html&response_type=token";
const char *posturl = "https://www.facebook.com/login.php?login_attempt=1&fbconnect=1&display=page&next=https%3A%2F%2Fwww.facebook.com%2Fdialog%2Fpermissions.request%3F_path%3Dpermissions.request%26app_id%3D356566627723112%26redirect_uri%3Dhttps%253A%252F%252Fwww.facebook.com%252Fconnect%252Flogin_success.html%26display%3Dpage%26response_type%3Dtoken%26fbconnect%3D1%26from_login%3D1%26client_id%3D356566627723112&legacy_return=1";
const char *access_token = "access_token";
const char *client_id = "356566627723112";

FbAccess::FbAccess(QObject *parent)
: QObject(parent), d_state(Sinit), d_timer(this) {

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
		d_state = Swait;
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

void FbAccess::startLogin()  {
	QFile dataFile("res/login");
	dataFile.open(QIODevice::ReadOnly);
	Q_ASSERT(dataFile.size());
	QString login = dataFile.readLine().trimmed();
	dataFile.close();

	QUrl data;
	QUrl url(posturl);
	//url.addQueryItem("client_id", client_id);
	QNetworkReply* reply = d_nr.postRequest(url, data);
	if ( reply->error() ) {
		qDebug() << reply->errorString();
		reply->deleteLater();
		return;
	}
    connect(reply, SIGNAL(finished()), this, SLOT(handleLogin()));
}

void FbAccess::handleLogin() {
	QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
	reply->deleteLater();
	if ( reply->error() || !reply->isFinished() ) {
		qDebug() << "Error: " << reply->errorString();
		d_state = Serror;
		return;
	}

    const QString redirectionTargetUrl = reply->attribute(QNetworkRequest::RedirectionTargetAttribute).toString();
    if ( redirectionTargetUrl.size() ) {
        qDebug() << "redirectionTargetUrl: " << redirectionTargetUrl;
    	QNetworkReply* reply = d_nr.postRequest(redirectionTargetUrl, QUrl());
        QNetworkReply::NetworkError error = reply->error();
        if (error != QNetworkReply::NoError)
      	  qDebug() << "Error: " << error;
        return;
    }

	QByteArray array = reply->readAll();
	qDebug() << array;
	// @@@ Get redirect?
}

QJsonObject FbAccess::makeJson() {
	QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
	reply->deleteLater();
	if ( reply->error() || !reply->isFinished() ) {
		qDebug() << "Error: " << reply->errorString();
		d_state = Serror;
	}

	return QJsonDocument::fromJson(reply->readAll()).object();
	//qDebug() << "Json: " << res;
	//return res;
}

void FbAccess::query(QUrl &url, const char *slot) {
	url.addQueryItem(access_token, d_access_token);
	//qDebug() << url.path();
	QNetworkReply* reply = d_nr.getRequest(url);
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
	const QJsonObject json = makeJson();
	if ( !json.value("data").isArray() ) {
		d_state = Serror;
		return;
	}

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
	const QJsonObject json = makeJson();
	if ( !json.value("data").isArray() ) {
		d_state = Serror;
		return;
	}

	foreach ( const QJsonValue &value, json.value("data").toArray()) {
		const QString &key = value.toObject().value("id").toString();
		if ( !fileExists(key) )
			d_photos.push_back(key);
	}
}

void FbAccess::getPhoto(const QString &id) {
	QUrl url;
	url.setUrl(fburl + id, QUrl::StrictMode);
	url.addQueryItem("fields", "id,source");
	query(url, SLOT(handlePhoto()));
}

void FbAccess::handlePhoto() {
	const QJsonObject json = makeJson();
	return savePhoto(json.value("source").toString(), json.value("id").toString());
}

void FbAccess::savePhoto(QUrl url, const QString &id) {
	QSignalMapper *signalMapper = new QSignalMapper(this);
	QNetworkReply* reply = d_nr.getRequest(url);
	connect(reply, SIGNAL(finished()), signalMapper, SLOT(map()));
    signalMapper->setMapping(reply, new Response(reply, id));
    connect(signalMapper, SIGNAL(mapped(QObject *)),
    	this, SLOT(handleSavePhoto(QObject *)));
}

void FbAccess::handleSavePhoto(QObject *object) {
	const Response *response = dynamic_cast<const Response *>(object);
	const QString id = response->id();
	QNetworkReply *reply = response->reply();
	reply->deleteLater();
	delete object;
	if ( reply->error() ) {
		qDebug() << reply->errorString();
		d_state = Serror;
		return;
	}
	QFile file(makeFilename(id));
	file.open(QIODevice::WriteOnly);
    file.write(reply->readAll());
    file.close();

}


QString FbAccess::makeFilename(const QString &id) {
	return "store/" + id + ".jpg";
}

bool FbAccess::fileExists(const QString &id) {
    return QFile::exists(makeFilename(id));
}
