/*
 * LocalizedObject.h
 *
 *  Created on: Mar 27, 2017
 *      Author: paco
 */

#ifndef SRC_LOCALIZEDOBJECT_H_
#define SRC_LOCALIZEDOBJECT_H_

#include "Point.h"

class LocalizedObject {
public:
	// --- CONSTRUCTOR & DESTRUCTOR
	LocalizedObject(Point p = Point(), double theta = 0);
	virtual ~LocalizedObject();

	// --- Getter & Setter
	Point getPosition() const;
	void setPosition(Point position);
	double getTheta() const;
	void setTheta(double theta);

protected:
	Point position;
	double theta;
};

#endif /* SRC_LOCALIZEDOBJECT_H_ */
