/*
 * DrawnObject.h
 *
 *  Created on: Mar 27, 2017
 *      Author: paco
 */

#ifndef SRC_DRAWNOBJECT_H_
#define SRC_DRAWNOBJECT_H_

#include "LocalizedObject.h"

class DrawnObject: public LocalizedObject {
public:
	DrawnObject();
	DrawnObject(double x, double y);
	virtual ~DrawnObject();

	void draw();
	virtual void draw(double x, double y) = 0;
};

#endif /* SRC_DRAWNOBJECT_H_ */
