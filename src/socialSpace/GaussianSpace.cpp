/**
 * @file GaussianSpace.cpp
 * @brief
 * @author Paco Dupont
 * @version 0.1
 * @date 28 mars 2017
 */

#include "GaussianSpace.h"
#include "math.h"
#include "utils.h"

// --- CONSTRUCTOR & DESTRUCTOR
GaussianSpace::GaussianSpace(Agent * a, int id):
		PersonnalSocialSpace(a, id){
}

GaussianSpace::~GaussianSpace() {
	// TODO Auto-generated destructor stub
}

// --- METHOD
double GaussianSpace::phi(Vector3d testedRealPoint){
// Gaussian representation of the personnal social space

	double sig = 0.45/2;

	Matrix<double,2,2> sigF;
	sigF <<
			sig, 0,
			0, 4*sig;

	Matrix<double,2,2> sigR;
	sigR <<
			sig, 0,
			0, sig;

	Matrix<double,2,2> rot;
	rot <<
			cos(this->_agent->getTheta()-M_PI/2), sin(this->_agent->getTheta()-M_PI/2),
			-sin(this->_agent->getTheta()-M_PI/2), cos(this->_agent->getTheta()-M_PI/2);

//	ofLogNotice("GaussianSpace::phi") << "Theta= " << getTheta();
//	ofLogNotice("GaussianSpace::phi") << rot;


//	Vector2d testedV(testedRealPoint.x,testedRealPoint.y), agentV(this->_agent->getX(),this->_agent->getY());
	Vector3d v = testedRealPoint-this->_agent->getPosition();

	// convert to vector2 for rotation
	Vector2d v2 = v.head<2>();
	// Apply rotation for model:
	v2 = rot*v2;

	int delta = planSide(testedRealPoint, this->_agent->getDirection(), this->_agent->getPosition());
	Matrix<double, 1, 2> i;
//	ofLogNotice("d") << " agent direction " << this->_agent->getDirection();

//	ofLogNotice("d") << "tested x=" << testedRealPoint.x << " y=" << testedRealPoint.y << " agent x=" << this->_agent->getX() << " delta=" << delta;
	if(delta > 0){
		i = v2.transpose()*sigF.inverse();
	}else {
		i = v2.transpose()*sigR.inverse();
	}

	double j =i*v2;
//
	double ret = exp(-0.5*j);
	return ret>GAUSSIAN_SPACE_INFLUENCE_TRESHOLD?ret:0;
}

