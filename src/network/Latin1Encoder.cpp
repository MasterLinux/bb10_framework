/*
 * Latin1Encoder.cpp
 *
 *  Created on: 31.05.2013
 *      Author: Christoph
 */

#include "Latin1Encoder.hpp"

namespace Network {

QString Latin1Encoder::encode(QString url) {
	QByteArray bytes = url.toLatin1();
	QString encoded;

	for(int i = 0; i < bytes.length(); i++) {
		QChar b = bytes.at(i);

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
			encoded = encoded % QString("\%%1").arg(b.unicode(), 0, 16);
		}
	}

	return encoded;
}

} /* namespace Network */
