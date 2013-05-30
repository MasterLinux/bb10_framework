/*
 * Request.cpp
 *
 *  Created on: 30.05.2013
 *      Author: Christoph
 */

#include "Request.hpp"

Request::Request() {

}

Request::~Request() {
	// TODO Auto-generated destructor stub
}

void Request::addParameter(QString name, QString value) {
	parameter.insert(name, value);
}

QString Request::buildURL(QString baseUrl, QString path, QMap<QString, QString> parameter) {
	QMapIterator<QString, QString> it(parameter);
	QString url;

	while(it.hasNext()) {
		it.next();

		it.key() + it.value();
	}

	return "";
}

