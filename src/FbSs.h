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

    Ui::FbSs 		ui;
    QString 		d_access_token;
    NetworkReader 	*d_nr;
    QPushButton 	*d_b;

private:
    QString makeFilename(const QString &id);
    bool fileExists(const QString &id);
    QJsonObject makeJson(QNetworkReply *reply);

public:
    FbSs(QWidget *parent = 0);
    ~FbSs();

    void photoThread();
    QNetworkReply* query(QUrl &url);
    bool getFriends(const QString &id);
    bool getPhotos(const QString &id);
    bool getPhoto(const QString &id);
    bool savePhoto(QUrl url, const QString &id);
};



#endif // QT5STUFF_H

