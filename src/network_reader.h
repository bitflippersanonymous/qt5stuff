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
    enum { timeout = 1000 }; // in ms

private:
    void encodeQueryItems(QUrl& url);

public:
	NetworkReader();
	~NetworkReader();
	QNetworkReply *makeRequest(const QUrl &url);

signals:
	void finishedRequest(QNetworkReply* json);

private slots:
	virtual void slotError(QNetworkReply::NetworkError error);
};


#endif /* NETWORK_READER_H_ */
