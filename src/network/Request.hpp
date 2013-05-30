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

namespace Network {

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

	void clearCache();

private:
	bool isStarted;
	QString cacheFilename;

};

};

#endif /* REQUEST_HPP_ */
