/**
 * @file GroupDetector.h
 * @brief
 * @author Paco Dupont
 * @version 0.1
 * @date 10 avril 2017
 */

#ifndef SRC_GROUPDETECTOR_H_
#define SRC_GROUPDETECTOR_H_

#include "Population.h"
#include "Agent.h"

#undef Success // Eigen import clash with X11, dirty fix
#include "ofxMatrixEigen.h"
#include <cmath>

using namespace Eigen;

/**
 * @class GroupDetector
 * @brief This class is dedicated to process every Agents in the Population and create every Formation
 *
 * @todo This class should be an interface and actual logic should be implemented has BasicGroupDetector
 */
class GroupDetector {
public:
	/**
	 * @brief Constructor
	 *
	 * Constructor of the GroupDetector class
	 *
	 * @param pop : The Population that the detector will process
	 */
	GroupDetector(Population* pop);

	/**
	 * @brief Destructor
	 *
	 * Destructor of the GroupDetector class, it does not call the related Population destructor
	 */
	virtual ~GroupDetector();

	/**
	 * @brief Find and create every Formations in the Population
	 *
	 */
	void detect();

	/**
	 * @brief Check if existing Formations are empty or if Agent is alone in a Formation and remove them
	 */
	void checkExistingFormation();

protected:
	Population* _population; //!< The Population processed by the GroupDetector
	//dirty
	int formationId = 0; //!< The actual increment for unique identifier of the Formations created
};

#endif /* SRC_GROUPDETECTOR_H_ */
