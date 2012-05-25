/*
 * FbSs
 *
 *  Created on: Apr 1, 2012
 *	Copyright 2012 Ryan Henderson
 *
 */


#include "FbSs.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName("BitFlippersAnonymous");
    QCoreApplication::setOrganizationDomain("bitflippersanonymous.com");
    QCoreApplication::setApplicationName("FbSs");

    QApplication a(argc, argv);
    FbSs w;
    return a.exec();
}
