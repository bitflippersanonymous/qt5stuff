/*
 * FbSs
 *
 *  Created on: Apr 1, 2012
 *	Copyright 2012 Ryan Henderson
 *
 */


#include "network_reader.h"
#include <QDebug>

NetworkReader::NetworkReader()
	: d_manager(new QNetworkAccessManager(this)), d_pending(0) {
	 connect(d_manager, SIGNAL(finished(QNetworkReply*)),
	         this, SLOT(finished()));
}

NetworkReader::~NetworkReader() {
	delete d_manager;
}

void NetworkReader::finished() {
	d_pending--;
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
