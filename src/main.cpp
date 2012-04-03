#include "qt5stuff.h"

#include <QtGui>
#include <QApplication>
#include <QJsonDocument>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qt5stuff w;
    //w.show();

    QFile dataFile("res/Test.json");
    dataFile.open(QIODevice::ReadOnly);
    QByteArray json = dataFile.readAll();
    dataFile.close();
    QJsonDocument doc(QJsonDocument::fromJson(json));
    QJsonObject item = doc.object();

    foreach ( const QString &key, item.keys() ) {
    	qDebug() << key << item.value(key);
    }

    return 0;
    return a.exec();
}
