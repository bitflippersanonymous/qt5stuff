/*
 * network_reader.cpp
 *
 *  Created on: Apr 3, 2012
 *      Author: vmplanet
 */

#include "network_reader.h"
#include <QDebug>
#include <QJsonDocument>

NetworkReader::NetworkReader()
	: d_manager(new QNetworkAccessManager(this)) {
}

NetworkReader::~NetworkReader() {
	delete d_manager;
}

QNetworkReply *NetworkReader::makeRequest(const QUrl &url)
{
	QNetworkRequest request;
    request.setUrl(url);
    request.setRawHeader("User-Agent", "YouTwitFace 1.0");
    QNetworkReply *reply = d_manager->get(request);
    if ( !reply->waitForReadyRead(timeout) )
    	return 0;

    QVariant statusCodeV = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    QVariant redirectionTargetUrl = reply->attribute(QNetworkRequest::RedirectionTargetAttribute);
    // see CS001432 on how to handle this

    QNetworkReply::NetworkError error = reply->error();
    if (error != QNetworkReply::NoError) {
  	  qDebug() << "Error: " << error;
  	  return 0;
    }

    return reply;
}

void NetworkReader::slotError(QNetworkReply::NetworkError error)  {
	  qDebug() << "Error: " << error;
}
