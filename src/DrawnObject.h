/*
 * DrawnObject.h
 *
 *  Created on: Mar 27, 2017
 *      Author: paco
 */

#ifndef SRC_DRAWNOBJECT_H_
#define SRC_DRAWNOBJECT_H_

#include "LocalizedObject.h"
#include "World.h"
#include "ofMain.h"

class DrawnObject: public LocalizedObject {
public:
	// --- CONSTRUCTOR & DESTRUCTOR
	DrawnObject(double x = 0, double y = 0, double theta = 0);
	virtual ~DrawnObject();

	// --- METHOD
	int real_to_pixel(World* world, double x, double x_min, double x_max);
	double pixel_to_real(World* world, int x, int x_min, int x_max);

	virtual void draw(World* world, double x = 0, double y = 0) = 0;

	// --- Getter & Setter
	ofNode* getNode() const;
	void setNode(ofNode* node);
	void setX(double x);
	void setY(double y);

protected:
	ofNode* node;
};

#endif /* SRC_DRAWNOBJECT_H_ */
