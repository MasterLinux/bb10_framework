/*
 * Request.cpp
 *
 *  Created on: 30.05.2013
 *      Author: Christoph
 */

#include "Request.hpp"

namespace Network {

Request::Request() {
	parameter = new QMap<QString, QString>();
}

Request::~Request() {
	delete parameter;
}

bool Request::start() {
	QString url = buildURL("", "", parameter, ISO_8851_1);
	QString uri;
}

void Request::addParameter(QString name, QString value) {
	parameter->insert(name, value);
}

QString Request::buildURL(QString baseUrl, QString path, QMap<QString, QString>* parameter, Encoding encoding) {
	QMapIterator<QString, QString> param(*parameter);
	QString url;

	//add parameter
	url = url % "?";
	while(param.hasNext()) {
		param.next();

		url = url % param.key() % "=" % encode(encoding, param.value());

		//prepare for the next parameter
		if(param.hasNext()) {
			url = url % "&";
		}
	}

	return url;
}

QString Request::encode(Encoding encoding, QString value) {
	switch(encoding) {
	case UTF8:

		break;

	case ISO_8851_1:
		value = value.toLatin1(); //TODO implement latin1 encoding
		break;
	}

	return value;
}
}

