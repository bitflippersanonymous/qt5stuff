#ifndef QT5STUFF_H
#define QT5STUFF_H

#include "ui_FbSs.h"
#include "network_reader.h"
#include <QtWidgets/QMainWindow>
#include <QPushButton>

class FbSs : public QMainWindow
{
    Q_OBJECT

    Ui::FbSs ui;
    QString d_access_token;
	NetworkReader d_nr;
	QPushButton 	*d_b;

public:
    FbSs(QWidget *parent = 0);
    ~FbSs();

    void handleState();
    void populateFriends();

private slots:
	void processItem(QNetworkReply *reply);

};



#endif // QT5STUFF_H

