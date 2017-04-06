/*
 * OSpace.h
 *
 *  Created on: Mar 27, 2017
 *      Author: paco
 */

#ifndef SRC_OSPACE_H_
#define SRC_OSPACE_H_

#include "ofMain.h"
#include "GroupSocialSpace.h"
#include "Point.h"

#undef Success // Eigen import clash with X11, dirty fix
#include "ofxMatrixEigen.h"
#include <cmath>

class OSpace: public GroupSocialSpace {
public:
	// --- CONSTRUCTOR & DESTRUCTOR
	OSpace(Point p = Point(), int id = 0);
	OSpace(std::vector<Agent*>& a, Point p = Point(), int id = 0);
	~OSpace();

	// --- METHOD
	void draw(World* world);
	void compute(World* world);
	void computeCenter();
	void computeCentroids();
	void sortAgents();
	double phi(Point testedPoint, double dh, double di);
	bool less(Point a, Point b);
	Point lineIntersectionPoint(Point ps1, Point pe1, Point ps2, Point pe2);


protected:
	ofPoint center;
	std::vector<Point> intersectionPoints;
	std::vector<Point> centroids;
	int width = 400;
	int height = 400;
	ofImage frame;
	std::vector<std::vector<double>> buffer;


};

#endif /* SRC_OSPACE_H_ */
