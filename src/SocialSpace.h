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
#include "Point.h"

class SocialSpace: public IdentifiedObject, public DrawnObject{
public:
	// --- CONSTRUCTOR & DESTRUCTOR
	SocialSpace(Point p = Point(), int id = 0);
	virtual ~SocialSpace();

	// --- METHOD
	virtual void draw(World* world, Point p = Point()) = 0;

};

#endif /* SRC_SOCIALSPACE_H_ */
