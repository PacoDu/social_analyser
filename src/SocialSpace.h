/*
 * SocialSpace.h
 *
 *  Created on: Mar 27, 2017
 *      Author: paco
 */

#ifndef SRC_SOCIALSPACE_H_
#define SRC_SOCIALSPACE_H_

#include "IdentifiedObject.h"
#include "DrawnObject.h"
#include "AgentContainer.h"

class SocialSpace: public IdentifiedObject, public DrawnObject, public AgentContainer{
public:
	SocialSpace();
	SocialSpace(int id);
	SocialSpace(double x, double y);
	SocialSpace(int id, double x, double y);
	SocialSpace(std::vector<Agent*>& a);
	SocialSpace(int id, std::vector<Agent*>& a);
	SocialSpace(int id, double x, double y, std::vector<Agent*>& a);
	SocialSpace(double x, double y, std::vector<Agent*>& a);
	virtual ~SocialSpace();

	virtual void draw(double x, double y) = 0;

};

#endif /* SRC_SOCIALSPACE_H_ */
