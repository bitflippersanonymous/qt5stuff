#include "FbSs.h"

#include <QtGui>
#include <QApplication>

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



    return a.exec();
}
