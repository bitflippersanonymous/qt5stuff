/*
 * network_reader.h
 *
 *  Created on: Apr 3, 2012
 *      Author: vmplanet
 */

#ifndef NETWORK_READER_H_
#define NETWORK_READER_H_

#include <QNetworkAccessManager>
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QImage>
#include <QImageReader>

class NetworkReader : public QObject
{
    Q_OBJECT
	QNetworkAccessManager 	*d_manager;
    QUrl					d_url;
    QNetworkRequest			*d_request;
    QNetworkReply 			*d_reply;

private:
    void encodeQueryItems(QUrl& url);

public:
	NetworkReader(const QString &url);
	~NetworkReader();
	void makeRequest();
	QByteArray getBytes() { return d_reply->readAll(); }
	QImage getImage() { return QImageReader(d_reply).read(); }
	QJsonObject getJson() { return QJsonDocument::fromJson(getBytes()).object(); }

signals:
	void finishedRequest();

private slots:
	virtual void finishedSlot(QNetworkReply* reply);
	virtual void slotError(QNetworkReply::NetworkError error);
};


#endif /* NETWORK_READER_H_ */
