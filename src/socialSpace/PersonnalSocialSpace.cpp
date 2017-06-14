/**
 * @file PersonnalSocialSpace.cpp
 * @brief
 * @author Paco Dupont
 * @version 0.1
 * @date 29 mars 2017
 */

#include "PersonnalSocialSpace.h"
#include "Agent.h"

PersonnalSocialSpace::PersonnalSocialSpace(Agent* a, int id):
		SocialSpace(id), _agent(a) {
}

PersonnalSocialSpace::~PersonnalSocialSpace() {
	// TODO Auto-generated destructor stub
}

