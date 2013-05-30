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
	delete baseUrl;
	delete path;
}

bool Request::start() {
	QString url = buildURL(*baseUrl, *path, *parameter, ISO_8851_1);
	QString uri;
}

void Request::setBaseUrl(QString baseUrl) {
	this->baseUrl = new QString(baseUrl);
}

void Request::setPath(QString path) {
	this->path = new QString(path);
}

void Request::addParameter(QString name, QString value) {
	parameter->insert(name, value);
}

QString Request::buildURL(QString baseUrl, QString path, QMap<QString, QString> parameter, Encoding encoding) {
	QString url;

	//remove backslash at the end of the baseUrl
	if(baseUrl.endsWith("/") || baseUrl.endsWith("\\")) {
		baseUrl = baseUrl.remove(baseUrl.length() - 1, 1);
	}

	//remove backslash at the beginning of the path
	if(path.startsWith("/") || path.startsWith("\\")) {
		path = path.remove(0, 1);
	}

	url = baseUrl % "/" % path;

	//add parameter
	if(parameter.size() > 0) {
		QMapIterator<QString, QString> param(parameter);

		url = url % "?";

		while(param.hasNext()) {
			param.next();

			url = url % param.key() % "=" % encode(encoding, param.value());

			//prepare for the next parameter
			if(param.hasNext()) {
				url = url % "&";
			}
		}
	}

	return url;
}

QString Request::encode(Encoding encoding, QString value) {
	switch(encoding) {
	case UTF8:

		break;

	case ISO_8851_1:
		QByteArray bytes = QString(value).toLatin1(); //TODO implement latin1 encoding
		QString encoded;

		for(int i = 0; i < bytes.length(); i++) {
			char b = bytes.at(i);

			//ignore encoding for unreserved characters
			if((b >= 0x41 && b <= 0x5a) //A-Z
					|| (b >= 0x61 && b <= 0x7a) //a-z
					|| (b >= 0x30 && b <= 0x39) //0-9
					|| b == 0x7e // ~
					|| b == 0x5f // _
					|| b == 0x2d // -
					|| b == 0x2e // .
					) {
				encoded = encoded % QString(b);
			}

			//encode all reserved and special characters
			else {
				encoded = encoded % QString("\%%1").arg(b, 0, 16);
			}
		}

		value = encoded;
		break;
	}

	return value;
}
}

