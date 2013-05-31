/*
 * Latin1Encoder.h
 *
 *  Created on: 31.05.2013
 *      Author: Christoph
 */

#ifndef LATIN1ENCODER_HPP_
#define LATIN1ENCODER_HPP_

#include <QString>
#include <QStringBuilder>
#include <IUrlEncoder.hpp>

namespace Network {

class Latin1Encoder : public IUrlEncoder {
public:
	Latin1Encoder() {}
	virtual ~Latin1Encoder() {}

	/**
	 * Encodes a string
	 */
	QString encode(QString url);
};

} /* namespace Network */
#endif /* LATIN1ENCODER_HPP_ */
