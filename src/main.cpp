#include "FbSs.h"

#include <QtGui>
#include <QApplication>
#include <QJsonDocument>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FbSs w;
    w.show();

#if 0
    QFile dataFile("res/Test.json");
    dataFile.open(QIODevice::ReadOnly);
    QByteArray json = dataFile.readAll();
    dataFile.close();
    QJsonDocument doc(QJsonDocument::fromJson(json));
    QJsonObject item = doc.object();

    foreach ( const QString &key, item.keys() ) {
    	qDebug() << key << item.value(key);
    }
#endif

    NetworkReader nr("https://graph.facebook.com/99394368305");
    nr.makeRequest();

    return a.exec();
}
