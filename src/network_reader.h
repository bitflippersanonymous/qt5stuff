/*
 * FbSs
 *
 *  Created on: Apr 1, 2012
 *	Copyright 2012 Ryan Henderson
 *
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
    enum { timeout = 1000 }; // in ms
    QNetworkAccessManager 	*d_manager;
    int						d_pending;

private:
    void encodeQueryItems(QUrl& url);

public:
	NetworkReader();
	~NetworkReader();
	QNetworkReply *makeRequest(const QUrl &url);
    int getPending() { return d_pending; }

private slots:
	virtual void finished();
	virtual void slotError(QNetworkReply::NetworkError error);
};


#endif /* NETWORK_READER_H_ */
