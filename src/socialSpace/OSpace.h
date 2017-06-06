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

	std::vector<std::vector<Vector3d>> dh_seg;
	std::vector<std::vector<Vector3d>> di_seg;
	// --- METHOD
	void draw(World* world);
	void update();
	void computeCovarMatrix();
	void computegCenter();
	void computeCentroids();
	void sortAgents();
	double phi(Vector3d testedPoint);
	bool less(Vector3d a, Vector3d b);

	// --- Getter & Setter
	Vector3d getCenter() const;
	void setCenter(const Vector3d& center);
	Vector3d getgCenter() const;
	void setgCenter(const Vector3d& gCenter);

protected:
	Vector3d center;
	Vector3d gCenter;
	double rotation = 0.0f;
	std::vector<Vector3d> intersectionPoints;
	std::vector<Vector3d> centroids;
	Matrix<double,2,2> covarMatrix;
};

#endif /* SRC_OSPACE_H_ */
