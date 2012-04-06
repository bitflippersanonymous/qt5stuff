#ifndef QT5STUFF_H
#define QT5STUFF_H

#include "ui_FbSs.h"
#include "network_reader.h"
#include "FbObject.h"
#include <QtWidgets>
#include <QPushButton>
#include <QHash>

class FbSs : public QWidget
{
    Q_OBJECT

    Ui::FbSs ui;
    QString d_access_token;
	NetworkReader d_nr;
	QPushButton 	*d_b;
    QStateMachine machine;
    FbObject::FbSet d_photos;

private:
    bool fileExists(const QString &id);
    QJsonObject makeJson(QNetworkReply *reply);

public:
    FbSs(QWidget *parent = 0);
    ~FbSs();

    void query(QUrl &url, const char *slot);
    void getFriends(const QString &id);
    void getPhotos(const QString &id);
    void getPhoto(const QString &id);


private slots:
	void gotFriends(QNetworkReply* reply);
	void gotPhotos(QNetworkReply* reply);
	void gotPhoto(QNetworkReply* reply);
	void savePhoto(QNetworkReply* reply);
    void handleState();

};



#endif // QT5STUFF_H

