/*
 * Utility.h
 *
 *  Created on: 28 Dec 2010
 *      Author: Michael
 */

#ifndef UTILITY_H_
#define UTILITY_H_

#include <string>
#include <cstring>

using namespace std;

namespace Planar {
	void stringCopy(string name, char *dest, size_t len) {
		memset(dest, '\0', len);
		strncpy(dest, name.substr(0, len - 1).c_str(), len - 1);
	}
}

#endif /* UTILITY_H_ */
