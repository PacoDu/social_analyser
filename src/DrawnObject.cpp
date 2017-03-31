/*
 * DrawnObject.cpp
 *
 *  Created on: Mar 27, 2017
 *      Author: paco
 */

#include "DrawnObject.h"
#include "World.h"

// --- CONSTRUCTOR & DESTRUCTOR
DrawnObject::DrawnObject(Point p, double theta):
		LocalizedObject(p,theta) {
}

DrawnObject::~DrawnObject() {
}

// --- METHOD
Point DrawnObject::real_to_pixel(World* world, Point p) {
	Point p_pixel = Point();
	p_pixel.x = ofMap(p.x, 0, world->width, 0, world->widthView) + world->getX();
	p_pixel.y = ofMap(p.y, 0, world->height, 0, world->heightView) + world->getY();

	return p_pixel;
}

Point DrawnObject::pixel_to_real(World* world, Point p) {
	Point p_real = Point();
	p_real.x = ofMap(p.x - world->getX(), 0, world->widthView, 0, world->width);
	p_real.y = ofMap(p.y - world->getY(), 0, world->heightView, 0, world->height);

	return p_real;
}
