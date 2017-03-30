/*
 * GroupSocialSpace.cpp
 *
 *  Created on: Mar 29, 2017
 *      Author: paco
 */

#include "GroupSocialSpace.h"

// --- CONSTRUCTOR & DESTRUCTOR
GroupSocialSpace::GroupSocialSpace(double x, double y, int id):
		SocialSpace(x,y,id), AgentContainer(){
}
GroupSocialSpace::GroupSocialSpace(std::vector<Agent*>& a, double x, double y, int id):
		SocialSpace(x,y,id), AgentContainer(a){
}

GroupSocialSpace::~GroupSocialSpace() {
	// TODO Auto-generated destructor stub
}

