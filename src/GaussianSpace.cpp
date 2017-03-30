/*
 * GaussianSpace.cpp
 *
 *  Created on: Mar 28, 2017
 *      Author: paco
 */

#include "GaussianSpace.h"

// --- CONSTRUCTOR & DESTRUCTOR
GaussianSpace::GaussianSpace(Agent * a, Point p, double theta):
		PersonnalSocialSpace(a,p,id){
	buffer = std::vector<std::vector<double>>(width, std::vector<double>(height));
	frame.allocate(width, height, OF_IMAGE_COLOR);
	frame.setColor(ofColor::white);
	frame.update();
	this->compute();
	a->setSocialSpace(this);
}

GaussianSpace::~GaussianSpace() {
	// TODO Auto-generated destructor stub
}

// --- METHOD
void GaussianSpace::compute() {
//	ofLogNotice("DEBUG") << "Value : " << std::endl
//			<< "phi(0,0)=" << phi(0,0) << std::endl
//			<< "phi(0.01,0.01)=" << phi(0.01,0.01) << std::endl
//			<< "phi(0.1,0.1)=" << phi(0.1,0.1) << std::endl
//			<< "phi(1,1)=" << phi(1,1) << std::endl
//			<< "phi(10,10)=" << phi(10,10) << std::endl;

	ofLogNotice("DEBUG") << "Computing social gaussian space";
	int a = 0, b = 0;
	for(double i = this->_agent->getX() - (width/2), a = 0; i < this->_agent->getX() + width/2; i+=0.01, a++){
		for(double j = this->_agent->getY() - (height/2), b = 0; j < this->_agent->getY() + height/2; j+=1, b++){
			buffer[a][b] = this->phi(Point(i,j));
		}
	}

	ofLogNotice("DEBUG") << "Buffer computed";

	int max = -INFINITY;
	int min = INFINITY;

	for(unsigned int i=0;i<width;i++){
		for(unsigned int j=0;j<height;j++){
			if(max < buffer[i][j]) max = buffer[i][j];
			if(min > buffer[i][j]) min = buffer[i][j];
		}
	}

	ofPixels pix = frame.getPixels();
	int k = 0;
	for(unsigned int i=0;i<width;i++){
		for(unsigned int j=0;j<height;j++){
			buffer[i][j] = buffer[i][j] / max * 255;
			pix[k] = buffer[i][j];
			pix[k+1] = buffer[i][j];
			pix[k+2] = buffer[i][j];
			k+=3;
		}
	}
	frame.setFromPixels(pix);
	frame.update();
	ofLogNotice("DEBUG") << "Data normalized";
}

double GaussianSpace::phi(Point testedSpace){
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

	Vector2d q(testedSpace.x,testedSpace.y), p(this->getX(),this->getY());
	Vector2d v = q-p;
	Matrix<double, 1, 2> i;

	// TODO use point.planSide ?
	if(v[1] > 0){
		i = v.transpose()*sigF.inverse();
	}else {
		i = v.transpose()*sigR.inverse();
	}

	double j =i*v;

	return exp(-0.5*j);
}

void GaussianSpace::draw(World* world) {
	Point pView = real_to_pixel(world, this->getPosition());
//	ofPushMatrix();
//		ofTranslate(this->getPosition().x + this->getX() - width/2 + x, this->node->getParent()->getPosition().y+this->getY() - height/2 + y);
//		ofSetHexColor(0xFFFFFF);
//		frame.draw(0,0);
//	ofPopMatrix();
}
