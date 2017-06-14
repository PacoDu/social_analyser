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

/**
 * @class LocalizedObject
 * @brief This class is an interface for object that are localized in real World
 *
 * This class is an interface for object that are localize in real World with x, y, z and Theta coordinates
 */
class LocalizedObject {
public:
	/**
	 * @brief Constructor
	 *
	 * Constructor of the LocalizedObject class
	 *
	 * @param position : The initial position of the object
	 * @param theta : The initial angle  of the object relative to X axis in radian
	 */
	LocalizedObject(Vector3d position = Vector3d(), double theta = 0);

	/**
	 * @brief Destructor
	 *
	 * Destructor of the LocalizedObject class
	 */
	virtual ~LocalizedObject();

	/**
	 * @brief Compute the direction vector of the object from its angle
	 * @return The direction Vector3d
	 */
	Vector3d getDirection();

	/**
	 * @brief Simple getter
	 * @return X coordinate of the position vector
	 */
	double getX() const;

	/**
	 * @brief Simple setter
	 * @param x
	 */
	void setX(double x);

	/**
	 * @brief Simple getter
	 * @return Y coordinate of the position vector
	 */
	double getY() const;

	/**
	 * @brief Simple setter
	 * @param y
	 */
	void setY(double y);

	/**
	 * @brief Simple getter
	 * @return position
	 */
	Vector3d getPosition() const;

	/**
	 * @brief Simple setter
	 * @param position
	 */
	void setPosition(Vector3d position);

	/**
	 * @brief Simple getter
	 * @return theta
	 */
	double getTheta() const;

	/**
	 * @brief Simple setter
	 * @param theta
	 */
	void setTheta(double theta);

protected:
	Vector3d position; //!< The position of the object
	double theta; //!< The angle of the object relative to X axis (1,0,0) (arround Z axis (0,0,1)) and in radian normalized between [0,2PI]
};

#endif /* SRC_LOCALIZEDOBJECT_H_ */
