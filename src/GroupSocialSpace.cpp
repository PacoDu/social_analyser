/*
 * GroupSocialSpace.cpp
 *
 *  Created on: Mar 29, 2017
 *      Author: paco
 */

#include "GroupSocialSpace.h"

// --- CONSTRUCTOR & DESTRUCTOR
GroupSocialSpace::GroupSocialSpace(Point p, int id):
		SocialSpace(p,id), AgentContainer(){
}
GroupSocialSpace::GroupSocialSpace(std::vector<Agent*>& a, Point p, int id):
		SocialSpace(p,id), AgentContainer(a){
}

GroupSocialSpace::~GroupSocialSpace() {
	// TODO Auto-generated destructor stub
}

