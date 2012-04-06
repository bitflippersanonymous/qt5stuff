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

const QString fburl = "https://graph.facebook.com/";
const char *access_token = "access_token";

FbSs::FbSs(QWidget *parent)
    : QWidget(parent), d_b(new QPushButton(this))
{
	resize(200, 200);
    QFile dataFile("res/access_token");
    dataFile.open(QIODevice::ReadOnly);
    Q_ASSERT(dataFile.size());
    d_access_token = dataFile.readLine().trimmed();
    dataFile.close();

    QState *s1 = new QState();
    QState *s2 = new QState();
    s1->addTransition(d_b, SIGNAL(clicked()), s2);
    s2->addTransition(d_b, SIGNAL(clicked()), s1);
    connect(s2, SIGNAL(entered()), this, SLOT(handleState()));
    machine.addState(s1);
    machine.addState(s2);
    machine.setInitialState(s1);
    machine.start();

	getFriends("me");

}

FbSs::~FbSs()
{
	delete d_b;
}

void FbSs::handleState() {
	getFriends("me");
}

QJsonObject FbSs::makeJson(QNetworkReply *reply) {
	return QJsonDocument::fromJson(reply->readAll()).object();
}

void FbSs::query(QUrl &url, const char *slot) {
	url.addQueryItem(access_token, d_access_token);
	d_nr.makeRequest(url);
    connect(&d_nr, SIGNAL(finishedRequest(QNetworkReply *)), this, slot);
}

void FbSs::getFriends(const QString &id) {
	QUrl url;
	url.setUrl(fburl + id + "/friends", QUrl::StrictMode);
	url.addQueryItem("fields", "id");
	query(url, SLOT(gotFriends(QNetworkReply *)));
}

void FbSs::gotFriends(QNetworkReply* reply) {
	foreach ( const QJsonValue &value, makeJson(reply).value("data").toArray()) {
		getPhotos(value.toObject().value("id").toString());
		break;
	}
}

void FbSs::getPhotos(const QString &id) {
	QUrl url;
	url.setUrl(fburl + id + "/photos", QUrl::StrictMode);
	url.addQueryItem("fields", "id");
	query(url, SLOT(gotPhotos(QNetworkReply *)));
}

void FbSs::gotPhotos(QNetworkReply* reply) {
	foreach ( const QJsonValue &value, makeJson(reply).value("data").toArray()) {
		const QString &key = value.toObject().value("id").toString();
		if ( !fileExists(key) )
			d_photos.insert(key.toULongLong());
	}
}

void FbSs::getPhoto(const QString &id) {
	QUrl url;
	url.setUrl(fburl + id, QUrl::StrictMode);
	url.addQueryItem("fields", "id,picture");
	query(url, SLOT(gotPhoto(QNetworkReply *)));
}

void FbSs::gotPhoto(QNetworkReply* reply) {
	QUrl url(makeJson(reply).value("picture").toString());
	query(url, SLOT(savePhoto(QNetworkReply *)));
}

void FbSs::savePhoto(QNetworkReply* reply) {
	QFile file(filename);
	file.open(QIODevice::WriteOnly);
    file.write(reply->readAll());
	file.close();
}

bool FbSs::fileExists(const QString &id) {
    return QFile::exists("store/" + id + ".jpg");
}

#if 0
if ( d_photos.find(key) == d_photos.end() )
	d_photos.insert(key);
break;
#endif
