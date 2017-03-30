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

class SocialSpace: public IdentifiedObject, public DrawnObject{
public:
	// --- CONSTRUCTOR & DESTRUCTOR
	SocialSpace(double x = 0, double y = 0, int id = 0);
	virtual ~SocialSpace();

	// --- METHOD
	virtual void draw(double x = 0, double y = 0) = 0;

};

#endif /* SRC_SOCIALSPACE_H_ */
