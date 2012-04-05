#include "FbSs.h"
#include "FbObject.h"
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDebug>

const QString fburl = "https://graph.facebook.com/";
const char *access_token = "access_token";

FbSs::FbSs(QWidget *parent)
    : QMainWindow(parent)
{
	ui.setupUi(this);

    QFile dataFile("res/access_token");
    dataFile.open(QIODevice::ReadOnly);
    Q_ASSERT(dataFile.size());
    d_access_token = dataFile.readLine().trimmed();
    dataFile.close();
    populateFriends();
}

FbSs::~FbSs()
{

}

void FbSs::populateFriends() {
	QUrl url;
	url.setUrl(fburl + "me/friends", QUrl::StrictMode);
	url.addQueryItem(access_token, d_access_token);
	d_nr.makeRequest(url);
    connect(&d_nr, SIGNAL(finishedRequest(QNetworkReply *)), this, SLOT(processItem(QNetworkReply *)));

}

void FbSs::processItem(QNetworkReply *reply) {
	FbObject friends(QJsonDocument::fromJson(reply->readAll()).object());
    foreach ( const QString &key, friends.getJson().keys() ) {
    	qDebug() << key << friends.getJson().value(key);
    }
}
