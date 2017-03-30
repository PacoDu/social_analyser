/*
 * Population.h
 *
 *  Created on: Mar 24, 2017
 *      Author: paco
 */

#ifndef SRC_POPULATION_H_
#define SRC_POPULATION_H_

#include "Agent.h"
#include "Formation.h"
#include "IdentifiedObject.h"
#include "DrawnObject.h"
#include "AgentContainer.h"
#include "ofMain.h"
#include "Population.h"

class Population: public IdentifiedObject, public DrawnObject, public AgentContainer {
public:
	// --- CONSTRUCTOR & DESTRUCTOR
	Population(Point p = Point(), int id = 0);
	Population(std::vector<Agent*> a, Point p = Point(), int id = 0);
	~Population();

	// --- METHOD
	void draw(World* world);
	void clear();

	ofVec2f getBoundX();
	ofVec2f getBoundY();

	void pushFormation(Formation* f);
	void clearFormations();
	int removeFormation(unsigned int formationId);

	// --- Getter & Setter
	const std::vector<Formation*>& getFormations() const;
	void setFormations(const std::vector<Formation*>& formations);

private:
	std::vector<Formation*> _formations;
};

#endif /* SRC_POPULATION_H_ */
