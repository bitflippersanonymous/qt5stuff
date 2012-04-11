#include "FbSs.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FbSs w;
    w.show();
    return a.exec();
}
