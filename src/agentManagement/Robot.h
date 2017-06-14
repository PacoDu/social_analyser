/**
 * @file Robot.h
 * @brief
 * @author Paco Dupont
 * @version 0.1
 * @date 7 juin 2017
 */

#ifndef SRC_AGENTMANAGEMENT_ROBOT_H_
#define SRC_AGENTMANAGEMENT_ROBOT_H_

#include "IdentifiedObject.h"
#include "DrawnObject.h"

#include "World.h"
#include "GridCell.h"
#include "Agent.h"

#include <chrono>

/**
 * @class Robot
 * @brief This class represent the Robot
 *
 * This class manage the Robot and its movement
 */
class Robot: public IdentifiedObject, public DrawnObject {
public:

	/**
	 * @brief Constructor
	 *
	 * Constructor of the Robot class
	 *
	 * @param position : Initial position of the Robot in World
	 * @param theta : Initial angle of the Robot
	 */
	Robot(Vector3d position=Vector3d(0,0,0), double theta=0);

	/**
	 * @brief Destructor
	 *
	 * Destructor of the Robot class
	 */
	~Robot();


#ifdef USE_OFX
	/**
	 * @brief Openframeworks GUI drawing for visualization
	 *
	 * @param world : The main frame coordinates
	 */
	void draw(World * world);
#endif

	/**
	 * @brief Compute the movement and the rotation of the Robot based on the computed path and linear interpolation between points
	 */
	void update();

	/**
	 * @brief Reset path finding process
	 */
	void resetPathFinding();

	/**
	 * @brief Simple getter
	 * @return goal
	 */
	GridCell* getGoal() const;

	/**
	 * @brief Simple setter
	 * @param goal
	 */
	void setGoal(GridCell* goal);

	/**
	 * @brief Simple getter
	 * @return path
	 */
	std::vector<GridCell*> getPath() const;

	/**
	 * @brief Simple setter
	 * @param path
	 */
	void setPath(std::vector<GridCell*> path);

	GridCell * goal; //!< The current goal of the Robot
	std::vector<GridCell*> path; //!< The current path followed by the Robot
	int pathIndex; //!< The current path index

	GridCell * startMarker; //!< The starting GridCell
	GridCell * endMarker; //!< The goal GridCell

	std::chrono::time_point<std::chrono::system_clock> startMoveTime; //!< Start time of the movement
	std::chrono::time_point<std::chrono::system_clock> startRotTime; //!< Start time of the rotation

	Agent * gazeTarget; //!< The Robot gaze targeted Agent for social signals

	double targetAngle; //!< The current targeted angle
	double * finalTargetAngle; //!< The targeted angle at the end of the movement
	double startAngle; //!< The initial angle of the Robot

	double rotDist; //!< The rotation distance of the actual segment
	double moveDist; //!< The movement distance of the actual segment

	double alphaMove = 0.05; //!< Used by the movement formulae
	double alphaRot = 0.05; //!< Used by the rotation formulae

	double moveSpeed = 0.5f; //!< The Robot move speed in meter/s
	double rotSpeed = 4.0f; //!< The Robot move speed in radian/s
	bool initPoint = 1; //!< Enable or disable path finding segment initialization
};

#endif /* SRC_AGENTMANAGEMENT_ROBOT_H_ */
