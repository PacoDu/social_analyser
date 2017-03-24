/*
 * Population.h
 *
 *  Created on: Mar 24, 2017
 *      Author: paco
 */

#ifndef SRC_POPULATION_H_
#define SRC_POPULATION_H_

#include "ofMain.h"
#include "Person.h"

class Population {
public:
	Population();
	virtual ~Population();

	void draw(int x, int y);
	void push(Person* p);
	void clear();

	ofVec2f getBoundX();
	ofVec2f getBoundY();

	void addFormation(std::vector<Person*>);

private:
	std::vector<Person*> _population;
	std::vector<Formation*> _formations;
};

#endif /* SRC_POPULATION_H_ */
