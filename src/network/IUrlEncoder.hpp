/*
 * IEncoder.h
 *
 *  Created on: 31.05.2013
 *      Author: Christoph Grundmann
 */

#ifndef IENCODER_HPP_
#define IENCODER_HPP_

#include <QString>

namespace Network {

class IUrlEncoder {
public:
	IUrlEncoder() {}
	virtual ~IUrlEncoder() {}

	virtual QString encode(QString url) = 0;
};

};

#endif /* IENCODER_HPP_ */
