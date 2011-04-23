/*
 * Table.h
 *
 *  Created on: 27 Dec 2010
 *      Author: Michael
 */

#ifndef TABLE_H_
#define TABLE_H_

#include <iostream>
#include <string>
#include <cstring>
#include <exception>
#include <stdexcept>
#include <map>

#include "Column.h"
#include "Utility.h"

using namespace std;

namespace Planar {
	struct Table {
		Table(): columnCount(0), columns(0) {}
		Table(string nameStr): columnCount(0), columns(0) {
			stringCopy(nameStr, name, sizeof(name));
			columns = new map<string, Column *>;
		}
		~Table() {
			map<string, Column *>::iterator it;
			for (it = columns->begin(); it != columns->end(); ++it) {
				delete it->second;
			}
			delete columns;
		}

		void newColumn(string name, size_t size, bool idColumn = false) {
			static size_t position = 0;

			if(idColumn) {
				position = 0;
			}

			(*columns)[name] = new Column(name, position, position + size);

			position += size;
			columnCount++;
		}

		void deleteColum(string name) {
			delete (*columns)[name];
			columns->erase(name);
		}

		char name[32];
		unsigned int columnCount;
		map<string, Column *> *columns;
	};
}

#endif /* TABLE_H_ */
