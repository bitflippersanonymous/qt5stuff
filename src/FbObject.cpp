/*
 * FbObject.cpp
 *
 *  Created on: Apr 3, 2012
 *      Author: george
 */

#include "FbObject.h"

FbObject::FbObject(const QJsonObject &json)
	: d_json(json) {

}

FbObject::~FbObject() {
}

