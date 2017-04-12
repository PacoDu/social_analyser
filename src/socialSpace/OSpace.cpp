/*
 * OSpace.cpp
 *
 *  Created on: Mar 27, 2017
 *      Author: paco
 */

#include "OSpace.h"
#include "utils.h"
#include "ofMain.h"

// --- CONSTRUCTOR & DESTRUCTOR
OSpace::OSpace(std::vector<Agent*>& a, int id): GroupSocialSpace(a, id), DrawnObject(){
	this->update();
}

OSpace::OSpace(int id): GroupSocialSpace(id){
}

OSpace::~OSpace() {
	// TODO Auto-generated destructor stub
}

// --- METHOD
// TODO:
// - order agents vector clockwise
// - compute ospace center (C)
// - phi gaussian representation of ospace knowing C
// - compute social map
// - draw social map
void OSpace::update() {
	this->intersectionPoints.resize(this->_agents.size());
	this->centroids.resize(this->_agents.size());

	this->computeCenter();
	this->sortAgents();
	this->computeCentroids();
}


void OSpace::draw(World* world) {

//	Point pView = real_to_pixel(world, Point(center.x, center.y));
//	ofPushMatrix();
//		ofTranslate(pView.x, pView.y);
////		ofRotateZ(ofRadToDeg(this->_agent->getTheta()-PI/2));
//		ofTranslate(-width/2, -height/2);
//		ofSetHexColor(0xFFFFFF);
//		frame.draw(0,0);
//	ofPopMatrix();

	Vector3d pView = real_to_pixel(world, center);
	ofPushMatrix();
		ofSetHexColor(0xd896ff);
		ofTranslate(pView.x(), pView.y());
		ofDrawCircle(0, 0, 30);
	ofPopMatrix();
//
//	for(unsigned int i=0; i < intersectionPoints.size(); i++){
//		pView = real_to_pixel(world, intersectionPoints[i]);
//		ofPushMatrix();
//			ofSetHexColor(0x0000FF);
//			ofTranslate(pView.x, pView.y);
//			ofDrawCircle(0, 0, 10);
//		ofPopMatrix();
//	}
//
//	for(unsigned int i=0; i < centroids.size(); i++){
//		pView = real_to_pixel(world, centroids[i]);
//		ofPushMatrix();
//			ofSetHexColor(0xFF0000);
//			ofTranslate(pView.x, pView.y);
//			ofDrawCircle(0, 0, 20);
//		ofPopMatrix();
//	}
//
//	pView = real_to_pixel(world, Point(center.x, center.y));
//	ofPushMatrix();
//		ofTranslate(pView.x, pView.y);
//		ofRotateZ(ofRadToDeg(this->getTheta()));
//		ofTranslate(-width/2, -height/2);
//		ofSetHexColor(0xFFFFFF);
//		frame.draw(0,0);
//	ofPopMatrix();
}

// Getter & Setter
void OSpace::computeCenter() {
	this->center << 0,0,0 ;
	for(unsigned int i=0; i < this->_agents.size(); i++){
		this->center += this->_agents[i]->getPosition();
	}

	this->center /= this->_agents.size();
}

void OSpace::sortAgents() {
//	if(this->_agents.size() > 2){
//
//	}
	bool shifted = false;
	for(unsigned int i=0; i < this->_agents.size()-1; i++){
		bool test = less(_agents[i]->getPosition(), _agents[i+1]->getPosition());
		if(test){
			Agent* tmp = _agents[i];
			_agents[i] = _agents[i+1];
			_agents[i+1] = tmp;

			shifted = true;
		}
	}

//	for(unsigned int i=0; i < this->_agents.size(); i++){
//		_agents[i]->setId(i);
//	}

	if(shifted) this->sortAgents();
}

bool OSpace::less(Vector3d a, Vector3d b)
{
    if (a.x() - center.x() >= 0 && b.x() - center.x() < 0)
        return true;
    if (a.x() - center.x() < 0 && b.x() - center.x() >= 0)
        return false;
    if (a.x() - center.x() == 0 && b.x() - center.x() == 0) {
        if (a.y() - center.y() >= 0 || b.y() - center.y() >= 0)
            return a.y() > b.y();
        return b.y() > a.y();
    }

    // compute the cross product of vectors (center -> a) x (center -> b)
    int det = (a.x() - center.x()) * (b.y() - center.y()) - (b.x() - center.x()) * (a.y() - center.y());
    if (det < 0)
        return true;
    if (det > 0)
        return false;

    // Points a and b are on the same line from the center
    // check which Point is closer to the center
    int d1 = (a.x() - center.x()) * (a.x() - center.x()) + (a.y() - center.y()) * (a.y() - center.y());
    int d2 = (b.x() - center.x()) * (b.x() - center.x()) + (b.y() - center.y()) * (b.y() - center.y());
    return d1 > d2;
}

double OSpace::phi(Vector3d testedRealPoint, double dh, double di) {
	using namespace Eigen;

//	ofLogNotice("DEbug") << "dh=" << dh << " di=" << di;
//	ofLogNotice("DEBUG") << "testedRealPoint(" << testedRealPoint.x << "," << testedRealPoint.y << ")";
	Matrix<double,2,2> sig;
	sig <<
			dh/4, 0,
			0, di/2;

	Vector2d v = (testedRealPoint-center).head<2>();
//	int delta = testedRealPoint.planSide(this->_agent->getDirection(), ofVec3f(this->_agent->getX(), this->_agent->getY()));
	Matrix<double, 1, 2> i;

	i = v.transpose()*sig.inverse();

	double j =i*v;

	return exp(-0.5*j);
}

//void OSpace::compute(World* world) {
//	if(_agents.size() > 1){
//		this->computeCenter();
//		this->sortAgents();
//		this->computeCentroids();
//
//
//		double dh = sqrt((_agents[_agents.size()-1]->getX() - _agents[0]->getX())*(_agents[_agents.size()-1]->getX() - _agents[0]->getX()) + (_agents[_agents.size()-1]->getY() - _agents[0]->getY())*(_agents[_agents.size()-1]->getY() - _agents[0]->getY()));
//		for(unsigned int i=1; i < _agents.size()-1; i++){
//			dh += sqrt((_agents[i+1]->getX() - _agents[i]->getX())*(_agents[i+1]->getX() - _agents[i]->getX()) + (_agents[i+1]->getY() - _agents[i]->getY())*(_agents[i+1]->getY() - _agents[i]->getY()));
//		}
//		dh /= _agents.size();
//
//
//			// TODO di = 0 when agents.size = 2
//		double di = sqrt((centroids[centroids.size()-1].x - centroids[0].x)*(centroids[centroids.size()-1].x - centroids[0].x) + (centroids[centroids.size()-1].y - centroids[0].y)*(centroids[centroids.size()-1].y - centroids[0].y));
//		for(unsigned int i=1; i < centroids.size()-1; i++){
//			di += sqrt((centroids[i+1].x - centroids[i].x)*(centroids[i+1].x - centroids[i].x) + (centroids[i+1].y - centroids[i].y)*(centroids[i+1].y - centroids[i].y));
//		}
//		di /= centroids.size();
//		di *= 2;
//
////		this->phi(x,y, dh, di);
//
//		double max = -INFINITY, min = INFINITY;
//		// Fill buffer with phi result
//		for(int i = 0; i < this->width; i++){
//			for(int j = 0; j < this->height; j++){
//				Point pv(center.x, center.y);
//				Point agentViewPoint = real_to_pixel(world, pv);
//				Point computedViewPoint = Point(agentViewPoint.x+i-width/2, agentViewPoint.y+j-height/2);
//				Point computedRealPoint = pixel_to_real(world, computedViewPoint);
//				buffer[i][j] = phi(computedRealPoint, dh, di);
//				if(buffer[i][j] > max) max = buffer[i][j];
//				if(buffer[i][j] < min) min = buffer[i][j];
//
////				ofLogNotice("DEBUG") << " phi=" << phi(computedRealPoint, dh, di);
//			}
//		}
//
//		// Compute normalized map (0-255)
//		for(int i = 0; i < this->width; i++){
//			for(int j = 0; j < this->height; j++){
//				buffer[i][j] = ofMap(buffer[i][j], min, max, 0, 255);
//				ofColor c = ofColor(0xFF, 0xBF, 0x58, buffer[i][j]);
//				frame.setColor((int)i,(int)j, c);
//			}
//		}
//
//		frame.update();
//
//		// Compute rotation TODO ...
//		ofVec3f a(this->_agents[0]->getPosition().x, this->_agents[0]->getPosition().y);
//		ofVec3f b(this->center.x, this->center.y);
//		ofVec3f dir(b.x-a.x, b.y-a.y);
//		this->setTheta(dir.angleRad(ofVec3f(1,0,0)));
//
//		ofLogNotice("DEBUG") << "Gaussian space computed for Formation #" << this->getId();
//
//	}
//}

void OSpace::computeCentroids() {
	intersectionPoints.resize(_agents.size());
	centroids.resize(_agents.size());

	Vector3d realCenter;

	for(unsigned int i=0; i < this->_agents.size(); i++){

		unsigned int neighborIndex = i+1;
		if(neighborIndex >= this->_agents.size()) neighborIndex = 0;

		if(abs(ofRadToDeg(_agents[i]->getTheta())) == abs(ofRadToDeg(_agents[neighborIndex]->getTheta()))){
			// TODO ...
			Vector3d p(0,0,0);
			intersectionPoints[i] = p;
			continue;
		}

		// Get line equation from agent position and direction:
		Vector3d ps1 = _agents[i]->getPosition();
		Vector3d pe1;
		pe1.x() = _agents[i]->getX()+_agents[i]->getDirection().x();
		pe1.y() =  _agents[i]->getY()+_agents[i]->getDirection().y();

		Vector3d ps2 = _agents[neighborIndex]->getPosition();
		Vector3d pe2;
		pe2.x() = _agents[neighborIndex]->getX() + _agents[neighborIndex]->getDirection().x();
		pe2.y() = _agents[neighborIndex]->getY() + _agents[neighborIndex]->getDirection().y();

		// compute intersection
		intersectionPoints[i] = lineIntersectionPoint(ps1, pe1, ps2, pe2);

		// compute centroïds
		Vector3d centro;
		centro.x() = (intersectionPoints[i].x() + ((_agents[neighborIndex]->getX() + _agents[i]->getX())/2))/2;
		centro.y() = (intersectionPoints[i].y() + ((_agents[neighborIndex]->getY() + _agents[i]->getY())/2))/2;
		centroids[i] = centro;

		realCenter += centro;
	}

	realCenter /=  this->_agents.size();
	center << realCenter.x(), realCenter.y(), realCenter.z();
}

Vector3d OSpace::getCenter() const {
	return center;
}

void OSpace::setCenter(const Vector3d& center) {
	this->center = center;
}
