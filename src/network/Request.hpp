/*
 * Request.hpp
 *
 *  Created on: 30.05.2013
 *      Author: Christoph
 */

#ifndef REQUEST_HPP_
#define REQUEST_HPP_

#include <QObject>
#include <QString>
#include <QMap>
#include <QMapIterator>

namespace Network {

enum ContentType { JSON, XML, Text };

enum Encoding { UTF8, ISO_8851_1 };

class Request {
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

	/**
	 * Clears the cached response
	 * of this request.
	 */
	void clearCache();

private:
	bool isStarted;
	QString cacheFilename;
	QMap<QString, QString> parameter;

	/**
	 * Deserializes the response.
	 * @param response The received response
	 * @param contentType Type of the response, which is necessary to select the required deserializer
	 */
	void deserialize(QString response, ContentType contentType); //TODO change return type

	/**
	 * Encodes a value with a specific encoding.
	 * @param encoding Required encoding
	 * @param value Value to encode
	 */
	void encode(Encoding encoding, QString* value);

	QString buildURL(QString baseUrl, QString path, QMap<QString, QString> parameter);
};

};

#endif /* REQUEST_HPP_ */
