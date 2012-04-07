#include "FbSs.h"

#include <QApplication>
#include <QQuickView>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FbSs w;
    w.show();

#if 0
	 QQuickView *view = new QQuickView;
     view->setSource(QUrl("qrc:/res/main.qml"));
	 view->show();
#endif

    return a.exec();
}
