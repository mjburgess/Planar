/*
 * Header.h
 *
 *  Created on: 27 Dec 2010
 *      Author: Michael
 */

#ifndef HEADER_H_
#define HEADER_H_

struct TableHeader {
	unsigned recordsPosition;
	unsigned recordCount;
	unsigned recordSize;

	unsigned tablePosition;
	unsigned columnsPosition;

	TableHeader(): recordsPosition(0), recordCount(0), recordSize(0),
			tablePosition(0), columnsPosition(0) {}

	TableHeader(unsigned recSize, unsigned tblPos, unsigned colPos):
		recordsPosition(colPos),  recordCount(0), recordSize(recSize), tablePosition(tblPos), columnsPosition(colPos) {}
};

#endif /* HEADER_H_ */
