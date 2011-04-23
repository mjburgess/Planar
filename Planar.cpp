//============================================================================
// Name        : Planar.cpp
// Author      : Michael J. Burgess
// Version     :
// Copyright   : December 2010
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "Plane.h"

using namespace std;
using namespace Planar;
using namespace Planar::Types;

struct Movie : RecordAbstract {
	char name[Text::Attribute];
	short rating;
	Movie(const char *Name, short rating) : rating(rating) {
		strncpy(name, Name, Text::Attribute);
		setID(0);
	}

	Movie(int id, const char *Name, short rating): rating(rating) {
		strncpy(name, Name, Text::Attribute);
		setID(id);
	}

	Movie(Movie *m) : rating(m->rating){
		strncpy(name, m->name, Text::Attribute);
		setID(m->getID());
	}
};

int main(int argc, string *argv) {
//	Plane<Movie> Movies("movies.plane", Plane<Movie>::Write);
//
//		Movies.with("RowID",  Numeric::Integer, true)
//			  .with("Name",   Text::Attribute)
//			  .with("Rating", Numeric::Short);
//
//		Movies.create(new Movie("Superman", 80))
//			  .create(new Movie("Lives of Others", 90))
//			  .save();
//
////		Movies.update(new Movie(1, "Superman", 82));
//		Movies.destroy(1);


	if(argc < 1) {
		cout << "Please specify a filename" << endl;
		return 0;
	}

	Plane<Movie> MoviePlane(argv[1], Plane<Movie>::Read);

	cout << describe<Movie>(MoviePlane);

	vector<Movie *> results = MoviePlane.findAll();
	if(results.size() > 0) {
		cout << "Found " << results.size() << " Records" << endl;
		for(vector<Movie *>::iterator it = results.begin(); it != results.end(); ++it) {
			cout << "Record ID " << (*it)->getID() << ", Name: " << (*it)->name << ", Rating: " << (*it)->rating << endl;
		}
	} else {
		cout << "No Records Found";
	}

	cin.get();

	return 0;
}
