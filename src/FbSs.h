#ifndef QT5STUFF_H
#define QT5STUFF_H

#include "ui_FbSs.h"
#include "network_reader.h"
#include <QtWidgets>
#include <QPushButton>

class FbSs : public QWidget
{
    Q_OBJECT

    Ui::FbSs ui;
    QString d_access_token;
	NetworkReader d_nr;
	QPushButton 	*d_b;
    QStateMachine machine;

public:
    FbSs(QWidget *parent = 0);
    ~FbSs();

    void getFriends();

private slots:
	void gotFriends(QNetworkReply *reply);
    void handleState();

};



#endif // QT5STUFF_H

