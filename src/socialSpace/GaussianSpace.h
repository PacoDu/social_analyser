/**
 * @file GaussianSpace.h
 * @brief
 * @author Paco Dupont
 * @version 0.1
 * @date 28 mars 2017
 */

#ifndef SRC_GAUSSIANSPACE_H_
#define SRC_GAUSSIANSPACE_H_

#include "PersonnalSocialSpace.h"

#undef Success // Eigen import clash with X11, dirty fix
#include "ofxMatrixEigen.h"
#include <cmath>

using namespace Eigen;

/**
 * @class GaussianSpace
 * @brief This class is an implementation of the PersonnalSocialSpace
 *
 * This class is an implementation of the PersonnalSocialSpace represented by a
 * 2D gaussian mixture model model based on interpersonal distances.
 */
class GaussianSpace: public PersonnalSocialSpace {
public:

	/**
	 * @brief Constructor
	 *
	 * Constructor of the GaussianSpace class
	 *
	 * @param agent : The Agent related to the GaussianSpace
	 * @param id : The unique identifier of the GaussianSpace
	 */
	GaussianSpace(Agent * agent, int id=0);

	/**
	 * @brief Destructor
	 *
	 * Destructor of the GaussianSpace class
	 */
	virtual ~GaussianSpace();

	/**
	 * @brief Compute the value of the GaussianSpace at a given point in space
	 *
	 * @param testedRealPoint : The coordinates of the point in the real frame coordinates World
	 *
	 * @return The value of the GaussianSpace at the given point
	 */
	double phi(Vector3d testedRealPoint);

};

#endif /* SRC_GAUSSIANSPACE_H_ */
