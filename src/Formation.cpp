/*
 * Formation.cpp
 *
 *  Created on: Mar 24, 2017
 *      Author: paco
 */

#include "Formation.h"

Formation::Formation(std::vector<Person*> p) {
	related_persons.swap(p);
}

Formation::~Formation() {
	// TODO Auto-generated destructor stub

}
