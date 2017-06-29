/**
 * @file OSpace.h
 * @brief
 * @author Paco Dupont
 * @version 0.1
 * @date 27 mars 2017
 */

#ifndef SRC_OSPACE_H_
#define SRC_OSPACE_H_

#include "GroupSocialSpace.h"
#include "DrawnObject.h"
#include "config.h"

#undef Success // Eigen import clash with X11, dirty fix
#include "ofxMatrixEigen.h"
#include <cmath>
using namespace Eigen;

/**
 * @class OSpace
 * @brief This class is an implementation of the GroupSocialSpace
 *
 * This class is an implementation of the GroupSocialSpace represented by a
 * 2D gaussian mixture model based on interpersonal distances and a algorithm
 * to find the center of the related Formation.
 */
class OSpace: public GroupSocialSpace, public DrawnObject {
public:

	/**
	 * @brief Constructor
	 *
	 * Constructor of the OSpace class, with no Agent
	 *
	 * @param id : The unique identifier of the OSpace
	 */
	OSpace(int id = 0);

	/**
	 * @brief Constructor
	 *
	 * Constructor of the OSpace class, for the Agents in parameter
	 *
	 * @param agents : The Agents related to the GroupSocialSpace
	 * @param id : The unique identifier of the GroupSocialSpace
	 */
	OSpace(std::vector<Agent*>& agents, int id = 0);

	/**
	 * @brief Destructor
	 *
	 * Destructor of the OSpace class
	 */
	~OSpace();

#if USE_OFX
	/**
	 * @brief Openframeworks GUI drawing for visualization
	 *
	 * @param world : The main frame coordinates
	 */
	void draw(World* world);
#endif

	/**
	 * @brief Compute the gravity center of the OSpace based on Agents positions
	 */
	void computegCenter();

	/**
	 * @brief Sort AgentContainer of the OSpace in clockwise order relative to gravity center
	 */
	void sortAgents();

	/**
	 * @brief Compute the centroids of each pair of Agent of the OSpace
	 * based on the field of view of every Agent
	 */
	void computeCentroids();

	/**
	 * @brief Compute the center of the Formation based on centroids
	 */
	void computeCenter();

	/**
	 * @brief Compute the covariance matrix of the 2D gaussian mixture model
	 *
	 * Compute the covariance matrix of the 2D gaussian mixture model based on interpersonnal distance between Agents
	 *
	 */
	void computeCovarMatrix();

	/**
	 * @brief Update the OSpace by computing its gravity center, centroids and deduce the covariance matrix
	 * of the 2D gaussian mixture model
	 */
	void update();


	/**
	 * @brief Compute the value of the OSpace at a given point in space
	 *
	 * @param testedPoint : The coordinates of the point in the real frame coordinates World
	 *
	 * @return The value of the OSpace at the given point
	 */
	double phi(Vector3d testedPoint);

	/**
	 * @brief Compare two vector based on the OSpace gravity center
	 *
	 * Compare two vector based on the OSpace gravity center to order them clockwise
	 *
	 * @param a : The first Agent position
	 * @param b : The second Agent position
	 * @return 1 if a Agent is before b Agent in clockwise order relative to gCenter, 0 otherwise
	 */
	bool less(Vector3d a, Vector3d b);

	/**
	 * @brief Simple getter
	 * @return center
	 */
	Vector3d getCenter() const;

	/**
	 * @brief Simpler setter
	 * @param center
	 */
	void setCenter(const Vector3d& center);

	/**
	 * @brief Simple getter
	 * @return gCenter
	 */
	Vector3d getgCenter() const;

	/**
	 * @brief Simple setter
	 * @param gCenter
	 */
	void setgCenter(const Vector3d& gCenter);

protected:
	std::vector<std::vector<Vector3d>> dh_seg; //!< List of DH vector representing the interpersonnal distance between the Agents
	std::vector<std::vector<Vector3d>> di_seg; //!< List of DI vector representing the distance between field of view intersection of Agents
	Vector3d center; //!< The center of the OSpace
	Vector3d gCenter; //!< The gravity center based on the Agents position
	double rotation = 0.0f; //!< The rotation applied to the 2D gaussian mixture model
	std::vector<Vector3d> intersectionPoints; //!< List of field of view intersection point between Agents
	std::vector<Vector3d> centroids; //!< List of the centroid points based on intersection points and Agents position
	Matrix<double,2,2> covarMatrix; //!< The covariance matrix of the 2D gaussian mixture model
};

#endif /* SRC_OSPACE_H_ */
