/*
 * FbObject.h
 *
 *  Created on: Apr 3, 2012
 *      Author: george
 */

#ifndef FBOBJECT_H_
#define FBOBJECT_H_

#include <QObject>
#include <QJsonObject>

class FbObject : public QObject {
    Q_OBJECT

public:
    typedef long long FbId;

private:
	QJsonObject d_json;

public:
	FbObject(const QJsonObject &json);
	virtual ~FbObject();
	const QJsonObject &getJson() { return d_json; }
};

#endif /* FBOBJECT_H_ */
