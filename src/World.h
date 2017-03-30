/*
 * World.h
 *
 *  Created on: Mar 29, 2017
 *      Author: paco
 */

#ifndef SRC_WORLD_H_
#define SRC_WORLD_H_

#include "ofMain.h"
#include "DrawnObject.h"

class World: public DrawnObject {
public:
	World(double w, double h, double x = 0, double y = 0, double theta = 0);
	virtual ~World();

	void draw();

	double width;
	double height;
	double widthView;
	double heightView;
	double x;
	double y;
	double theta;

};

#endif /* SRC_WORLD_H_ */
