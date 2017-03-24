/*
 * Formation.h
 *
 *  Created on: Mar 24, 2017
 *      Author: paco
 */

#ifndef SRC_FORMATION_H_
#define SRC_FORMATION_H_

#include "Person.h"

class Formation {
public:
	Formation(std::vector<Person*> p);
	virtual ~Formation();

	void push(Person*);

private:
	Ospace ospace;
	std::vector<Person*> related_persons;
};

#endif /* SRC_FORMATION_H_ */
