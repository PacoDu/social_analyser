/*
 * Robot.cpp
 *
 *  Created on: Jun 7, 2017
 *      Author: paco
 */

#include "Robot.h"
#include "utils.h"
#include "ofMain.h"

Robot::Robot(Vector3d position, double theta): DrawnObject(position, theta) {

}

Robot::~Robot() {
	// TODO Auto-generated destructor stub
}

// --- METHOD
void Robot::draw(World * world) {
	Vector3d pView = real_to_pixel(world, this->getPosition());
	double shoulderLength = real_to_pixel(world, Vector3d(0,0.35,0)).y() - world->getPosition().y();
	double headRadius = real_to_pixel(world, Vector3d(0.14,0,0)).x() - world->getPosition().x();
	ofPushMatrix();
		ofSetHexColor(0x6497b1);
		ofTranslate(pView.x(), pView.y());
		ofRotateZ(ofRadToDeg(this->getTheta()));

//		ofDrawBitmapString("#"+ofToString(this->getId()), -shoulderLength/2, -shoulderLength/2);

//		ofSetHexColor(0x6497b1);
		ofSetHexColor(0x00FF00);
		ofDrawTriangle(0, shoulderLength/2, shoulderLength, 0, 0, -shoulderLength/2);

//		ofSetHexColor(0x011f4b);
		ofSetHexColor(0xEEEEEE);
		ofDrawCircle(0,0,headRadius);
		ofSetHexColor(0xFF0000);
		ofDrawCircle(0,0,1);
	ofPopMatrix();
}

GridCell* Robot::getGoal() const {
	return goal;
}

void Robot::resetPathFinding() {
	ofLogNotice("DEBUG") << " RESET ROBOT PATHFINDING";
	this->goal = nullptr;
	this->path.clear();
	this->pathIndex = 0;
	this->initPoint = 1;
}

void Robot::setGoal(GridCell* goal) {
	this->goal = goal;
}

int min(int a, int b){ return a>b?b:a; };

void Robot::update() {
	if(goal != nullptr){
		if(initPoint && path.size() > 1){
			int nextPathIndex = pathIndex + 5;

			ofLogNotice("DEBUG") << "PathIndex = " << pathIndex << " nextPathIndex=" << min(nextPathIndex, path.size()-1);

			startMarker = path[min(pathIndex, path.size()-1)];
			endMarker = path[min(nextPathIndex, path.size()-1)];
			startMoveTime = std::chrono::system_clock::now();
			moveDist = distance(startMarker->getPosition(), endMarker->getPosition());

			startAngle = this->getTheta();
			int angleDelta = 2;
			Vector3d rDirection = vectLerp(path[min(pathIndex+angleDelta, path.size()-2)]->getPosition(), path[min(nextPathIndex+angleDelta, path.size()-1)]->getPosition(), 1) - this->getPosition();
			targetAngle = atan2(rDirection.y(), rDirection.x()) - atan2(0,1);
			startRotTime = std::chrono::system_clock::now();


//			if(targetAngle < 0) targetAngle += 2 * M_PI;
//
			initPoint = 0;

		}

		if(finalTargetAngle && pathIndex + 5 > path.size())
			targetAngle = *finalTargetAngle;

		while (targetAngle > this->getTheta() + M_PI )
			targetAngle -= 2* M_PI;

		while (targetAngle < this->getTheta() - M_PI )
			targetAngle += 2* M_PI;

		ofLogNotice("Robot::update") << " targetAngle = " << targetAngle << " pathIndex = " << pathIndex << " RobotTheta="<< getTheta() <<" rotDist=" << targetAngle - getTheta();



//		ofLogNotice("ROBOT") << "Dist covered = " << distCovered << " fracMove = " << fracMove << " deltaT =" << deltaT.count();
//		ofLogNotice("ROBOT") << "Move distance = " << moveDist;

//		ofLogNotice("DEBUG") << "StarMarker = " << startMarker->getId() << " endMarker=" << endMarker->getId();

		rotDist = targetAngle - this->getTheta();
		if(rotDist > M_PI){
			rotDist = - M_PI - rotDist;
		}
		else if(rotDist < -M_PI){
			rotDist = M_PI + rotDist;
		}

		if(pathIndex != 0 || abs(rotDist) < ROBOT_MAX_ROT_DELTA_BEFORE_MOVE){
			std::chrono::duration<double> deltaT= std::chrono::system_clock::now() - startMoveTime;

			double distCovered =  deltaT.count() * moveSpeed;
			double fracMove = distCovered / (moveDist+0.001);
			Vector3d estimatedPosition = vectLerp(startMarker->getPosition(), endMarker->getPosition(), fracMove);

			this->setPosition(this->getPosition()*(1-alphaMove) + estimatedPosition * alphaMove);

			if(this->getX() > 5 || this->getY() > 5 || this->getX() != this->getX()){
				ofLogNotice("DEBUG") << "Robot out of bounds !!!!";
			}
			if(fracMove >= 1){
				initPoint = 1;
//				if(pathIndex + 5 < path.size()){
				pathIndex+=5;
//				}
//				else{
//					pathIndex+=1;
//				}
			}
		}
		else{
			startMoveTime = std::chrono::system_clock::now();
		}

//		if(finalTargetAngle && pathIndex > path.size()- 20){
//			this->setTheta(this->getTheta()*(1-alphaRot)+finalTargetAngle * alphaRot);
//		}else{

			this->setTheta(this->getTheta()*(1-alphaRot)+targetAngle * alphaRot);
//		}

	}
}

std::vector<GridCell*> Robot::getPath() const {
	return path;
}

void Robot::setPath(std::vector<GridCell*> path) {
	this->path = path;
}
