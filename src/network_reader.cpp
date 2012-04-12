/*
 * network_reader.cpp
 *
 *  Created on: Apr 3, 2012
 *      Author: vmplanet
 */

#include "network_reader.h"
#include <QDebug>

NetworkReader::NetworkReader()
	: d_manager(new QNetworkAccessManager(this)), d_pending(0) {
	 connect(d_manager, SIGNAL(finished(QNetworkReply*)),
	         this, SLOT(finished(QNetworkReply*)));
}

NetworkReader::~NetworkReader() {
	delete d_manager;
}

void NetworkReader::finished(QNetworkReply *reply) {
	d_pending--;
	emit finishedRequest(reply);
}

QNetworkReply *NetworkReader::makeRequest(const QUrl &url)
{
	QNetworkRequest request;
    request.setUrl(url);
    request.setRawHeader("User-Agent", "YouTwitFace 1.0");
    QNetworkReply *reply = d_manager->get(request);

    QVariant statusCodeV = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    QVariant redirectionTargetUrl = reply->attribute(QNetworkRequest::RedirectionTargetAttribute);
    // see CS001432 on how to handle this

    QNetworkReply::NetworkError error = reply->error();
    if (error != QNetworkReply::NoError) {
  	  qDebug() << "Error: " << error;
  	  reply->deleteLater();
  	  return 0;
    }
    d_pending++;
    return reply;
}

void NetworkReader::slotError(QNetworkReply::NetworkError error)  {
	d_pending--;
	qDebug() << "Error: " << error;
}
