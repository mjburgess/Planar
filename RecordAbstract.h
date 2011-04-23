/*
 * RecordAbstract.h
 *
 *  Created on: 28 Dec 2010
 *      Author: Michael
 */

#ifndef RECORDABSTRACT_H_
#define RECORDABSTRACT_H_

class RecordAbstract {
public:
	void setID(int id) {
		this->id = id;
	}
	int getID() {
		return this->id;
	}
private:
	int id;
};

#endif /* RECORDABSTRACT_H_ */
