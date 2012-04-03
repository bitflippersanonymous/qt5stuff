/*
 * network_reader.cpp
 *
 *  Created on: Apr 3, 2012
 *      Author: vmplanet
 */

#include "network_reader.h"
#include <QDebug>

NetworkReader::NetworkReader(const QString &url)
	: d_manager(new QNetworkAccessManager(this)), d_request(0), d_reply(0) {
	QObject::connect(d_manager, SIGNAL(finished(QNetworkReply*)),
			this, SLOT(finishedSlot(QNetworkReply*)));
	d_url.setUrl(url, QUrl::StrictMode);
	encodeQueryItems(d_url);
}

NetworkReader::~NetworkReader() {
	delete d_reply;
	delete d_manager;
}

void NetworkReader::makeRequest()
{
	QNetworkRequest request;
    request.setUrl(d_url);
    request.setRawHeader("User-Agent", "YouTwitFace 1.0");
	d_reply = d_manager->get(request);
    connect(d_reply, SIGNAL(readyRead()), this, SLOT(downloadReadyRead()));
    connect(d_reply, SIGNAL(error(QNetworkReply::NetworkError)),
            this, SLOT(slotError(QNetworkReply::NetworkError)));
}

void NetworkReader::finishedSlot(QNetworkReply* reply) {
  Q_ASSERT(d_reply == reply);
  QVariant statusCodeV = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
  QVariant redirectionTargetUrl = reply->attribute(QNetworkRequest::RedirectionTargetAttribute);
  // see CS001432 on how to handle this

  QNetworkReply::NetworkError error = reply->error();
  if (error != QNetworkReply::NoError) {
    // handle errors here
  }
  emit finishedRequest();
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
