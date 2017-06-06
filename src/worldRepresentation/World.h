/*
 * World.h
 *
 *  Created on: Mar 29, 2017
 *      Author: paco
 */

#ifndef SRC_WORLD_H_
#define SRC_WORLD_H_

#include "DrawnObject.h"

class World: public DrawnObject {
public:
	World(double w, double h, int wv, int hv, Vector3d position = Vector3d(), double theta = 0);
	virtual ~World();

	void draw(World* world);
	void draw();
	double getHeight() const;
	void setHeight(double height);
	double getHeightView() const;
	void setHeightView(double heightView);
	double getWidth() const;
	void setWidth(double width);
	double getWidthView() const;
	void setWidthView(double widthView);

	double width;
	double height;
	double widthView;
	double heightView;

};

#endif /* SRC_WORLD_H_ */
