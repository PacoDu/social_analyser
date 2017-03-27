/*
 * SocialSpace.cpp
 *
 *  Created on: Mar 27, 2017
 *      Author: paco
 */

#include "SocialSpace.h"

SocialSpace::SocialSpace():
IdentifiedObject(), DrawnObject(), AgentContainer() {
}

SocialSpace::SocialSpace(int id):
		IdentifiedObject(id), DrawnObject(), AgentContainer() {
}

SocialSpace::SocialSpace(double x, double y):
		IdentifiedObject(), DrawnObject(x,y), AgentContainer() {
}

SocialSpace::SocialSpace(int id, double x, double y):
		IdentifiedObject(id), DrawnObject(x,y), AgentContainer() {
}

SocialSpace::SocialSpace(std::vector<Agent*>& a):
		IdentifiedObject(), DrawnObject(), AgentContainer(a) {
}

SocialSpace::SocialSpace(int id, std::vector<Agent*>& a):
		IdentifiedObject(id), DrawnObject(), AgentContainer(a) {
}

SocialSpace::SocialSpace(int id, double x, double y, std::vector<Agent*>& a):
		IdentifiedObject(id), DrawnObject(x,y), AgentContainer(a) {
}

SocialSpace::SocialSpace(double x, double y, std::vector<Agent*>& a):
		IdentifiedObject(), DrawnObject(x,y), AgentContainer(a){
}

SocialSpace::~SocialSpace() {
}
