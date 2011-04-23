/*
 * Planar.h
 *
 *  Created on: 27 Dec 2010
 *      Author: Michael
 */

#ifndef PLANAR_H_
#define PLANAR_H_

#include <iostream>
#include <string>
#include <sstream>
#include <cstring>
#include <exception>
#include <stdexcept>
#include <fstream>

#include <vector>

#include "TableHeader.h"
#include "Table.h"
#include "Column.h"
#include "Types.h"
#include "RecordAbstract.h"

using namespace std;

namespace Planar {
	template <class Record> class Plane {
	public:
		static const bool Write = true;
		static const bool Read = false;

		Plane(string name, bool write = true);
		Plane(Table *t, const char *filename);
		~Plane();

		Plane<Record> &with(string name, size_t size, bool idColumn = false);

		Plane<Record> &create(Record *r, bool firstNull = false);
		vector<Record *> findAll();
		vector<Record *> find(const int id);
		vector<Record *> find(const string column, const void *value);
		vector<Record *> find(const Column *c, const char *searchTerm);
		Plane<Record> &update(Record *r);
		Plane<Record> &destroy(const int id);

		void save() ;
		Table *getTable() const;
	private:
		fstream *file;
		Table   *table;
		TableHeader *header;

		void read(size_t position, size_t amount, char *dest);
		void write(size_t position, size_t amount, const char *src);

		void writeHeader();
		void readHeader();

		void writeTable();
		void readTable();

		void writeColumns();
		void readColumns();

		void writeRecord(RecordAbstract *r);
		void readRecord(RecordAbstract *r);
	};


	template <class Record>
	void save(const Record *r, const Plane<Record> &p) {
		return p->writeRecord(r->id);
	}

	template <class Record>
	string describe(const Plane<Record> &p) {
		Table *T = p.getTable();
		ostringstream out;

		out << "Table[" << T->name << "][" << T->columnCount << "]" << endl;

		map<string, Column *>::iterator it;
		for (it = T->columns->begin(); it != T->columns->end(); ++it) {
			out << "Column[" << it->second->end - it->second->start
					<< ":" << it->second->name << "] @ "
					<<  it->second->start << endl;
		}

		return out.str();
	}

	template <class Record>
	Plane<Record>::Plane(string name, bool write) {
		table  = new Table(name.substr(0, name.find('.', 1)).c_str());
		header = new TableHeader(sizeof(Record), sizeof(TableHeader), sizeof(TableHeader) + sizeof(Table));

		if(!ifstream(name.c_str())) {
			ofstream(name.c_str(), ios_base::out)
			.write(reinterpret_cast<const char *>(header), sizeof(TableHeader));
		}

		file   = new fstream(name.c_str(), ios::out | ios::in);
		readHeader();

		if(!write) {
			readTable();
		}
	}

	template <class Record>
	Plane<Record>::Plane(Table *t, const char *name) {
		table = t;

		if(!ifstream(name)) {
			ofstream(name, ios_base::out);
		}
		writeTable();
	}

	template <class Record>
	Plane<Record>::~Plane() {
		writeHeader();
		delete file;
		delete table;
	}

	template <class Record>
	vector<Record *> Plane<Record>::findAll() {
		vector<Record *>  records;

		char *temp = new char[sizeof(Record)];
		for(unsigned i = 1; i <= header->recordCount; i++) {
			read(header->recordsPosition + i * sizeof(Record), sizeof(Record), temp);
			records.push_back(new Record(reinterpret_cast<Record *>(temp)));
		}
		delete temp;

		return records;
	}

	template <class Record>
	vector<Record *> Plane<Record>::find(const int id) {
		vector<Record *> records;
		records.push_back(new Record);

		readRecord(id, records[0]);
	}

	template <class Record>
	vector<Record *> Plane<Record>::find(const string column, const void *value) {
		Column *c = (*table->columns)[column];
		return find(c, reinterpret_cast<const char *>(value));
	}

	template <class Record>
	vector<Record *> Plane<Record>::find(const Column *c, const char *searchTerm) {
		vector<Record *>  records;

		char *temp = new char[sizeof(Record)];
		for(unsigned i = 0; i <= header->recordCount; i++) {
			read(header->recordsPosition + i * sizeof(Record), sizeof(Record), temp);

			if(strncmp(searchTerm, temp + c->start, c->end) == 0) {
				records.push_back(new Record(reinterpret_cast<Record *>(temp)));
			}
		}
		delete temp;

		return records;
	}

	template <class Record>
	Plane<Record> &Plane<Record>::with(string name, size_t size, bool idColumn) {
		header->recordsPosition += sizeof(Column);
		table->newColumn(name, size, idColumn);
		return *this;
	}

	template <class Record>
	Plane<Record> &Plane<Record>::create(Record *r, bool firstNull) {
		r->setID(0);
		writeRecord(r);
		return *this;
	}
	template <class Record>
	Plane<Record> &Plane<Record>::update(Record *r) {
		writeRecord(r);
		return *this;
	}
	template <class Record>
	Plane<Record> &Plane<Record>::destroy(const int id) {
		RecordAbstract r;
		r.setID(id);
		writeRecord(&r);
		return *this;
	}

	template <class Record>
	void Plane<Record>::save() {
		writeTable();
		writeHeader();
	}

	template <class Record>
	Table *Plane<Record>::getTable() const {
		return table;
	}

	template <class Record>
	void Plane<Record>::read(size_t position, size_t amount, char *dest) {
		file->seekg(position, ios_base::beg);
		file->read(dest, amount);
	}

	template <class Record>
	void Plane<Record>::write(size_t position, size_t amount, const char *src) {
		file->seekp(position, ios_base::beg);
		file->write(src, amount);
		file->flush();
	}

	template <class Record>
	void Plane<Record>::writeHeader(){
		write(0, sizeof(TableHeader), reinterpret_cast<const char *>(header));
	}

	template <class Record>
	void Plane<Record>::readHeader() {
		read(0, sizeof(TableHeader), reinterpret_cast<char *>(header));
	}

	template <class Record>
	void Plane<Record>::writeTable() {
		write(header->tablePosition, sizeof(Table), reinterpret_cast<const char *>(table));
		writeColumns();
	}

	template <class Record>
	void Plane<Record>::readTable()  {
		read(sizeof(TableHeader), sizeof(Table), reinterpret_cast<char *>(table));
		readColumns();
	}

	template <class Record>
	void Plane<Record>::writeColumns() {
		map<string, Column *>::iterator it = table->columns->begin();
		Column *c;
		for (int i = 0; it != table->columns->end(); ++it, i++) {
			c = it->second;
			write(header->columnsPosition + i * sizeof(Column),
					sizeof(Column), reinterpret_cast<const char *>(it->second));
		}
	}

	template <class Record>
	void Plane<Record>::readColumns() {
		table->columns = new map<string, Column *>;

		Column c;
		for (unsigned i = 0; i < table->columnCount; i++) {
			read(header->columnsPosition + i * sizeof(Column),
					sizeof(Column), reinterpret_cast<char *>(&c));

			(*table->columns)[string(c.name)] = new Column(c.name, c.start, c.end);
		}
	}

	template <class Record>
	void Plane<Record>::writeRecord(RecordAbstract *r) {
		if(r->getID() == 0) {
			r->setID(++header->recordCount);
		}
		write(header->recordsPosition + r->getID() * sizeof(Record),
			sizeof(Record), reinterpret_cast<const char *>(r));
	}

	template <class Record>
	void Plane<Record>::readRecord(RecordAbstract *r) {
		write(header->recordsPosition + r->getID() * sizeof(Record),
				sizeof(Record), reinterpret_cast<const char *>(r));
	}
} //end namespace
#endif /* PLANAR_header_ */
