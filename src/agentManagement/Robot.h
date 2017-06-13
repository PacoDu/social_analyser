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

	void update();

	void resetPathFinding();
	GridCell* getGoal() const;
	void setGoal(GridCell* goal);
	std::vector<GridCell*> getPath() const;
	void setPath(std::vector<GridCell*> path);

	GridCell * goal;
	std::vector<GridCell*> path;
	int pathIndex;
	GridCell * startMarker;
	GridCell * endMarker;
	std::chrono::time_point<std::chrono::system_clock> startMoveTime;
	std::chrono::time_point<std::chrono::system_clock> startRotTime;

	Agent * gazeTarget;

	double targetAngle;
	double * finalTargetAngle;
	double startAngle;
	double rotDist;

	double alphaMove = 0.05;
	double alphaRot = 0.05;

	double moveDist;
	double moveSpeed = 0.5f;
	double rotSpeed = 4.0f;
	bool initPoint = 1;
};

#endif /* SRC_AGENTMANAGEMENT_ROBOT_H_ */
