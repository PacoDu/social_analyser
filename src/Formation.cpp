/*
 * Formation.cpp
 *
 *  Created on: Mar 24, 2017
 *      Author: paco
 */

// TODO Merge constructor (e.i. lower constructor call the highest with default param)
#include "Formation.h"

Formation::Formation(double ospace_radius, double pspace_radius) {
	this->ospace = new OSpace(this->getX(), this->getY(), ospace_radius);
	this->pspace = new PSpace(this->getX(), this->getY(), ospace_radius, pspace_radius);
}

Formation::Formation(double ospace_radius, double pspace_radius, std::vector<Agent*>& a):
		IdentifiedObject(), DrawnObject(), AgentContainer(a)  {
	this->ospace = new OSpace(this->getX(), this->getY(), ospace_radius);
	this->pspace = new PSpace(this->getX(), this->getY(), ospace_radius, pspace_radius);
}

Formation::~Formation() {
	// TODO Auto-generated destructor stub

}

Formation::Formation(int id, double ospace_radius, double pspace_radius):
		IdentifiedObject(id), DrawnObject(), AgentContainer() {
	this->ospace = new OSpace(this->getX(), this->getY(), ospace_radius);
	this->pspace = new PSpace(this->getX(), this->getY(), ospace_radius, pspace_radius);
}

Formation::Formation(double x, double y, double ospace_radius, double pspace_radius):
		IdentifiedObject(), DrawnObject(x,y), AgentContainer() {
	this->ospace = new OSpace(this->getX(), this->getY(), ospace_radius);
	this->pspace = new PSpace(this->getX(), this->getY(), ospace_radius, pspace_radius);
}

Formation::Formation(int id, double x, double y, double ospace_radius, double pspace_radius):
		IdentifiedObject(id), DrawnObject(x,y), AgentContainer() {
	this->ospace = new OSpace(this->getX(), this->getY(), ospace_radius);
	this->pspace = new PSpace(this->getX(), this->getY(), ospace_radius, pspace_radius);
}

Formation::Formation(int id, double ospace_radius, double pspace_radius, std::vector<Agent*>& a):
		IdentifiedObject(id), DrawnObject(), AgentContainer(a) {
	this->ospace = new OSpace(this->getX(), this->getY(), ospace_radius);
	this->pspace = new PSpace(this->getX(), this->getY(), ospace_radius, pspace_radius);
}

Formation::Formation(int id, double x, double y, double ospace_radius, double pspace_radius, std::vector<Agent*>& a):
		IdentifiedObject(id), DrawnObject(x,y), AgentContainer(a) {
	this->ospace = new OSpace(this->getX(), this->getY(), ospace_radius);
	this->pspace = new PSpace(this->getX(), this->getY(), ospace_radius, pspace_radius);
}

Formation::Formation(double x, double y, double ospace_radius, double pspace_radius, std::vector<Agent*>& a):
		IdentifiedObject(), DrawnObject(x,y), AgentContainer(a) {
	this->ospace = new OSpace(this->getX(), this->getY(), ospace_radius);
	this->pspace = new PSpace(this->getX(), this->getY(), ospace_radius, pspace_radius);
}

void Formation::draw(double x, double y) {
	ospace->draw(x,y);
	pspace->draw(x,y);
}
