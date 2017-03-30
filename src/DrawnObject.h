/*
 * DrawnObject.h
 *
 *  Created on: Mar 27, 2017
 *      Author: paco
 */

#ifndef SRC_DRAWNOBJECT_H_
#define SRC_DRAWNOBJECT_H_

#include "LocalizedObject.h"
#include "Point.h"

#include "ofMain.h"
class World;

class DrawnObject: public LocalizedObject {
public:
	// --- CONSTRUCTOR & DESTRUCTOR
	DrawnObject(Point p = Point(), double theta = 0);
	virtual ~DrawnObject();

	// --- METHOD
	Point real_to_pixel(World* world, Point p);
	Point pixel_to_real(World* world, Point p);
	double getX(){return this->position.x;}
	double getY(){return this->position.y;}
	void setX(int x){this->position.x = x;}
	void setY(int y){this->position.y = y;}

	virtual void draw(World* world, Point p = Point()) = 0;

};

#endif /* SRC_DRAWNOBJECT_H_ */
