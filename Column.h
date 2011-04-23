/*
 * Column.h
 *
 *  Created on: 27 Dec 2010
 *      Author: Michael
 */

#ifndef COLUMN_H_
#define COLUMN_H_

#include <iostream>
#include <string>
#include <cstring>
#include <exception>
#include <stdexcept>
#include <vector>

#include "Utility.h"

using namespace std;

namespace Planar {
	struct Column {
		Column(): start(0), end(0) {}
		Column(string nameStr, size_t start, size_t end): start(start), end(end) {
			stringCopy(nameStr, name, sizeof(name));
		}

		char name[32];
		size_t start;
		size_t end;
	};
}

#endif /* COLUMN_H_ */
