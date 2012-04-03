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

signals:
	void finishedRequest();

private slots:
	virtual void finishedSlot(QNetworkReply* reply);
	virtual void slotError(QNetworkReply::NetworkError error);
};


#endif /* NETWORK_READER_H_ */
