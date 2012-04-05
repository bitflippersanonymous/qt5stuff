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
#include <QJsonDocument>
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


}

FbSs::~FbSs()
{
	delete d_b;
}

void FbSs::handleState() {
	getFriends();
}

void FbSs::getFriends() {
	QUrl url;
	url.setUrl(fburl + "me/friends", QUrl::StrictMode);
	url.addQueryItem(access_token, d_access_token);
	url.addQueryItem("fields", "id");
	d_nr.makeRequest(url);
    connect(&d_nr, SIGNAL(finishedRequest(QNetworkReply *)), this, SLOT(gotFriends(QNetworkReply *)));

}
#if 0
void FbSs::getPhotos(FbObject::FbId id) {
	foreach (friend d_friends) {
		d_photos.add(new FbPhotos(id, "queueDownload"));
	}
}
#endif

void FbSs::gotFriends(QNetworkReply *reply) {
	FbObject friends(QJsonDocument::fromJson(reply->readAll()).object());
    foreach ( const QString &key, friends.getJson().keys() ) {
    	qDebug() << key << friends.getJson().value(key);
    }
}
