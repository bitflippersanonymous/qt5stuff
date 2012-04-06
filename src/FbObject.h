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
#include <QHash>
#include <QSet>

class FbObject : public QObject {
    Q_OBJECT

public:
    typedef unsigned long long FbId;
    typedef QHash<const FbObject::FbId, FbObject *> FbHash;
    typedef QSet<const FbObject::FbId> FbSet;

private:
	QJsonObject d_json;

public:
	FbObject(const QJsonObject &json);
	virtual ~FbObject();
	const QJsonObject &getJson() { return d_json; }
};

#endif /* FBOBJECT_H_ */
