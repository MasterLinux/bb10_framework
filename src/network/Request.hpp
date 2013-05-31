/*
 * Request.hpp
 *
 *  Created on: 30.05.2013
 *      Author: Christoph Grundmann
 */

#ifndef REQUEST_HPP_
#define REQUEST_HPP_

#include <QObject>
#include <QString>
#include <QMap>
#include <QChar>
#include <QMapIterator>
#include <QStringBuilder>
#include <QByteArray>
#include <Latin1Encoder.hpp>
#include <../nullptr_t.hpp>

namespace Network {

enum ContentType { JSON, XML, Text };

enum Encoding { UTF8, ISO_8851_1 };

class Request : public QObject {
	Q_OBJECT

public:
	Request();
	virtual ~Request();

	/**
	 * Starts the request when it isn't running.
	 * @return false if already running, true otherwise
	 */
	bool start(); //TODO use int as return value to allow error codes?

	/**
	 * Stops the request if it is running.
	 * @return false if it isn't running, true otherwise
	 */
	bool stop(); //TODO use int as return value to allow error codes?

	void addParameter(QString name, QString value);

	void addHeader(QString name, QString value);

	void addBody(QString name, QString value);

	void setEncoding(Encoding encoding);

	void setContentType(ContentType contentType);

	void setBaseUrl(QString host);

	void setPath(QString path);

	/**
	 * Clears the cached response
	 * of this request.
	 */
	void clearCache();

private:
	bool isStarted;
	QString *cacheFilename;
	QString *baseUrl, *path;
	QMap<QString, QString> *parameter;
	QMap<QString, QString> *header;
	QMap<QString, QString> *body;
	IUrlEncoder *urlEncoder;

	/**
	 * Deserializes the response.
	 * @param response The received response
	 * @param contentType Type of the response, which is necessary to select the required deserializer
	 */
	void deserialize(QString response, ContentType contentType); //TODO change return type


	QString buildURL(QString baseUrl, QString path, QMap<QString, QString> parameter);
};

};

#endif /* REQUEST_HPP_ */
