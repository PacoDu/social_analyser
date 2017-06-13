/*
 * Robot.h
 *
 *  Created on: Jun 7, 2017
 *      Author: paco
 */

#ifndef SRC_AGENTMANAGEMENT_ROBOT_H_
#define SRC_AGENTMANAGEMENT_ROBOT_H_

#include "IdentifiedObject.h"
#include "DrawnObject.h"

#include <chrono>
#include "World.h"
#include "GridCell.h"
#include "Agent.h"

class Robot: public IdentifiedObject, public DrawnObject {
public:
	Robot(Vector3d position=Vector3d(0,0,0), double theta=0);
	virtual ~Robot();

	void draw(World * world);
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
