/*
 * GaussianSpace.cpp
 *
 *  Created on: Mar 28, 2017
 *      Author: paco
 */

#include "GaussianSpace.h"

// --- CONSTRUCTOR & DESTRUCTOR
//GaussianSpace::GaussianSpace(Agent * a, Point p, double theta):
//		PersonnalSocialSpace(a,p,id){
//	buffer = std::vector<std::vector<double>>(width, std::vector<double>(height));
//	frame.allocate(width, height, OF_IMAGE_COLOR);
//	frame.setColor(ofColor::white);
//	frame.update();
//	a->setSocialSpace(this);
//}

GaussianSpace::GaussianSpace(World* world, Agent * a, double theta):
		PersonnalSocialSpace(a,Point(a->getX(),a->getY()), a->getTheta(), id){
	buffer = std::vector<std::vector<double>>(width, std::vector<double>(height));
	frame.allocate(width, height, OF_IMAGE_COLOR_ALPHA);
	frame.setColor(ofColor::white);
	frame.update();
	this->compute(world);
//	a->setSocialSpace(this);
}

GaussianSpace::~GaussianSpace() {
	// TODO Auto-generated destructor stub
}

// --- METHOD
void GaussianSpace::compute(World* world) {
//	ofLogNotice("DEBUG") << "Value : " << std::endl
//			<< "phi(0,0)=" << phi(0,0) << std::endl
//			<< "phi(0.01,0.01)=" << phi(0.01,0.01) << std::endl
//			<< "phi(0.1,0.1)=" << phi(0.1,0.1) << std::endl
//			<< "phi(1,1)=" << phi(1,1) << std::endl
//			<< "phi(10,10)=" << phi(10,10) << std::endl;

//	ofLogNotice("DEBUG") << "Computing social gaussian space";
//	int a = 0, b = 0;
//	for(double i = this->_agent->getX() - (width/2), a = 0; i < this->_agent->getX() + width/2; i+=0.01, a++){
//		for(double j = this->_agent->getY() - (height/2), b = 0; j < this->_agent->getY() + height/2; j+=1, b++){
//			buffer[a][b] = this->phi(Point(i,j));
//		}
//	}
//
//	ofLogNotice("DEBUG") << "Buffer computed";
//
//	int max = -INFINITY;
//	int min = INFINITY;
//
//	for(unsigned int i=0;i<width;i++){
//		for(unsigned int j=0;j<height;j++){
//			if(max < buffer[i][j]) max = buffer[i][j];
//			if(min > buffer[i][j]) min = buffer[i][j];
//		}
//	}
//
//	ofPixels pix = frame.getPixels();
//	int k = 0;
//	for(unsigned int i=0;i<width;i++){
//		for(unsigned int j=0;j<height;j++){
//			buffer[i][j] = buffer[i][j] / max * 255;
//			pix[k] = buffer[i][j];
//			pix[k+1] = buffer[i][j];
//			pix[k+2] = buffer[i][j];
//			k+=3;
//		}
//	}
//	frame.setFromPixels(pix);
//	frame.update();
//	ofLogNotice("DEBUG") << "Data normalized";

	double max = -INFINITY, min = INFINITY;
	// Fill buffer with phi result
	for(int i = 0; i < this->width; i++){
		for(int j = 0; j < this->height; j++){
			Point agentViewPoint = real_to_pixel(world, this->_agent->getPosition());
			Point computedViewPoint = Point(agentViewPoint.x+i-width/2, agentViewPoint.y+j-height/2);
			Point computedRealPoint = pixel_to_real(world, computedViewPoint);
//			ofLogNotice("e") << "crp x=" << computedRealPoint.x << " y=" << computedRealPoint.y;
			buffer[i][j] = phi(computedRealPoint);
			if(buffer[i][j] > max) max = buffer[i][j];
			if(buffer[i][j] < min) min = buffer[i][j];
		}
	}
	// TODO social map is filled for a agent direction(0,1,0) buffer need to be rotated
	// buffer map is false, only drawing is correct (-PI/2 rotation)

	// Compute normalized map (0-255)
	for(int i = 0; i < this->width; i++){
		for(int j = 0; j < this->height; j++){
			buffer[i][j] = ofMap(buffer[i][j], min, max, 0, 255);
			ofColor c = ofColor(0xbc, 0x69, 0xaa,buffer[i][j]);
			frame.setColor((int)i,(int)j, c);
		}
	}

	frame.update();

	ofLogNotice("DEBUG") << "Gaussian space computed for Agent #" << this->_agent->getId();
}

// Gaussian representation of the personnal social space
double GaussianSpace::phi(Point testedRealPoint){
	using namespace Eigen;

	double sig = 0.45/2;

	Matrix<double,2,2> sigF;
	sigF <<
			sig, 0,
			0, 4*sig;

	Matrix<double,2,2> sigR;
	sigR <<
			sig, 0,
			0, sig;


	Vector2d testedV(testedRealPoint.x,testedRealPoint.y), agentV(this->_agent->getX(),this->_agent->getY());
	Vector2d v = testedV-agentV;
//	int delta = testedRealPoint.planSide(this->_agent->getDirection(), ofVec3f(this->_agent->getX(), this->_agent->getY()));
	Matrix<double, 1, 2> i;
//	ofLogNotice("d") << " agent direction " << this->_agent->getDirection();

//	ofLogNotice("d") << "tested x=" << testedRealPoint.x << " y=" << testedRealPoint.y << " agent x=" << this->_agent->getX() << " delta=" << delta;
	if(testedRealPoint.y > this->_agent->getY()){
		i = v.transpose()*sigF.inverse();
//		return 1;
	}else {
		i = v.transpose()*sigR.inverse();
//		return 0;
	}

	double j =i*v;
//
	return exp(-0.5*j);
}

void GaussianSpace::draw(World* world) {
	Point pView = real_to_pixel(world, this->_agent->getPosition());
//	ofLogNotice("e") << pView.x << "," << pView.y;
	ofPushMatrix();
		ofTranslate(pView.x, pView.y);
		ofRotateZ(ofRadToDeg(this->_agent->getTheta()-PI/2));
		ofTranslate(-width/2, -height/2);
		ofSetHexColor(0xFFFFFF);
		frame.draw(0,0);
	ofPopMatrix();
}
