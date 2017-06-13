/**
 * @file LocalizedObject.h
 * @brief
 * @author Paco Dupont
 * @version 0.1
 * @date 27 mars 2017
 */

#ifndef SRC_LOCALIZEDOBJECT_H_
#define SRC_LOCALIZEDOBJECT_H_

#undef Success // Eigen import clash with X11, dirty fix
#include "ofxMatrixEigen.h"
#include <cmath>

using namespace Eigen;

class LocalizedObject {
public:
	// --- CONSTRUCTOR & DESTRUCTOR
	LocalizedObject(Vector3d p = Vector3d(), double theta = 0);
	virtual ~LocalizedObject();

	// METHOD
	Vector3d getDirection();
	double getX() const;
	void setX(double x);
	double getY() const;
	void setY(double y);

	// --- Getter & Setter
	Vector3d getPosition() const;
	void setPosition(Vector3d position);
	double getTheta() const;
	void setTheta(double theta);

protected:
	Vector3d position;
	double theta;
};

#endif /* SRC_LOCALIZEDOBJECT_H_ */
