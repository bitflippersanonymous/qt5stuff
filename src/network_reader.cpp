/*
 * network_reader.cpp
 *
 *  Created on: Apr 3, 2012
 *      Author: vmplanet
 */

#include "network_reader.h"
#include <QDebug>

NetworkReader::NetworkReader()
	: d_manager(new QNetworkAccessManager(this)) {
	QObject::connect(d_manager, SIGNAL(finished(QNetworkReply*)),
			this, SLOT(finishedSlot(QNetworkReply*)));
}

NetworkReader::~NetworkReader() {
	delete d_manager;
}

void NetworkReader::makeRequest(const QUrl &url)
{
	QNetworkRequest request;
    request.setUrl(url);
    request.setRawHeader("User-Agent", "YouTwitFace 1.0");
    QNetworkReply *reply = d_manager->get(request);
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)),
            this, SLOT(slotError(QNetworkReply::NetworkError)));
}

void NetworkReader::finishedSlot(QNetworkReply* reply) {
  QVariant statusCodeV = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
  QVariant redirectionTargetUrl = reply->attribute(QNetworkRequest::RedirectionTargetAttribute);
  // see CS001432 on how to handle this

  QNetworkReply::NetworkError error = reply->error();
  if (error != QNetworkReply::NoError) {
    // handle errors here
  }
  emit finishedRequest(reply);
}

void NetworkReader::slotError(QNetworkReply::NetworkError error)  {
	  qDebug() << "Error";
}

void NetworkReader::encodeQueryItems(QUrl& url) {
  QList<QPair<QString, QString> > queryList = url.queryItems();
  for (int i = 0; i  < queryList.count(); i++) {
    QPair<QString, QString> pair = queryList[i];
    QByteArray leftEncoded = QUrl::toPercentEncoding(pair.first);
    QByteArray rightEncoded = QUrl::toPercentEncoding(pair.second);
    url.removeQueryItem(pair.first);
    url.addEncodedQueryItem(leftEncoded, rightEncoded);
  }
}
