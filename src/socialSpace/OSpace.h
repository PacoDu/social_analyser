/*
 * OSpace.h
 *
 *  Created on: Mar 27, 2017
 *      Author: paco
 */

#ifndef SRC_OSPACE_H_
#define SRC_OSPACE_H_

#include "GroupSocialSpace.h"
#include "DrawnObject.h"

#undef Success // Eigen import clash with X11, dirty fix
#include "ofxMatrixEigen.h"
#include <cmath>
using namespace Eigen;

class OSpace: public GroupSocialSpace, public DrawnObject {
public:
	// --- CONSTRUCTOR & DESTRUCTOR
	OSpace(int id = 0);
	OSpace(std::vector<Agent*>& a, int id = 0);
	~OSpace();

	// --- METHOD
	void draw(World* world);
	void update();
	void compute(World* world);
	void computeCenter();
	void computeCentroids();
	void sortAgents();
	double phi(Vector3d testedPoint, double dh, double di);
	bool less(Vector3d a, Vector3d b);

	// --- Getter & Setter
	Vector3d getCenter() const;
	void setCenter(const Vector3d& center);

protected:
	Vector3d center;
	std::vector<Vector3d> intersectionPoints;
	std::vector<Vector3d> centroids;

};

#endif /* SRC_OSPACE_H_ */
