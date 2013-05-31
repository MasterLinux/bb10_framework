/*
 * Request.cpp
 *
 *  Created on: 30.05.2013
 *      Author: Christoph
 */

#include "Request.hpp"

namespace Network {

Request::Request() {
	networkAccessManager = new QNetworkAccessManager(this);

	connect(
		networkAccessManager, SIGNAL(finished(QNetworkReply*)),
		this, SLOT(onFinished(QNetworkReply*))
	);

	parameter = new QMap<QString, QString>();
}

Request::~Request() {
	delete networkAccessManager;
	delete parameter;

	if(urlEncoder != 0) {
		delete urlEncoder;
	}
}

bool Request::start() {
	QNetworkRequest request = QNetworkRequest();
	request.setUrl(QUrl(buildURL(baseUrl, path, *parameter)));
	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

	//start the request
	networkAccessManager->get(request);

	return true;
}

void Request::onFinished(QNetworkReply* reply) {
	QNetworkReply::NetworkError networkError = reply->error();

	//get content on success
	if(networkError == QNetworkReply::NoError) {
		QByteArray bytes = reply->readAll();
		QString s = QString(bytes);
		s.toAscii();
	}

	//handle error
	else {
		emit error(-1);
	}

	//destroy reply
	reply->deleteLater();
}

void Request::setBaseUrl(QString baseUrl) {
	this->baseUrl = baseUrl;
}

void Request::setPath(QString path) {
	this->path = path;
}

void Request::addParameter(QString name, QString value) {
	parameter->insert(name, value);
}

QString Request::buildURL(QString baseUrl, QString path, QMap<QString, QString> parameter) {
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

			url = url % param.key() % "=" % urlEncoder->encode(param.value());

			//prepare for the next parameter
			if(param.hasNext()) {
				url = url % "&";
			}
		}
	}

	return url;
}

void Request::setEncoding(Encoding encoding) {
//	if(urlEncoder != NULL) {
//		delete urlEncoder;
//	}

	switch(encoding) {
		case UTF8:

			break;

		case ISO_8851_1:
			urlEncoder = new Latin1Encoder();
			break;

		default:
			break;
	}
}

}

