/*
 * GaussianSpace.cpp
 *
 *  Created on: Mar 28, 2017
 *      Author: paco
 */

#include "GaussianSpace.h"

GaussianSpace::GaussianSpace() {
	// TODO Auto-generated constructor stub
	frame.allocate(400, 400, OF_IMAGE_COLOR);
	this->compute();
}

GaussianSpace::GaussianSpace(double x, double y) {
	// TODO Auto-generated constructor stub
	frame.allocate(400, 400, OF_IMAGE_COLOR);
	frame.setColor(ofColor::white);
	frame.update();
	this->setX(x);
	this->setY(y);
	this->compute();
}

GaussianSpace::~GaussianSpace() {
	// TODO Auto-generated destructor stub
}

void GaussianSpace::compute() {
	ofLogNotice("DEBUG") << "Value : " << std::endl
			<< "phi(0,0)=" << phi(0,0) << std::endl
			<< "phi(0.01,0.01)=" << phi(0.01,0.01) << std::endl
			<< "phi(0.1,0.1)=" << phi(0.1,0.1) << std::endl
			<< "phi(1,1)=" << phi(1,1) << std::endl
			<< "phi(10,10)=" << phi(10,10) << std::endl;

	ofLogNotice("DEBUG") << "Computing social gaussian space";
	for(double i = 0; i < 4; i+=0.01){
		for(double j = 0; j < 4; j+=0.01){
			double result = this->phi(i,j);
			int a = i*100;
			int b = j*100;
			buffer[a][b] = result;
		}
	}

	ofLogNotice("DEBUG") << "Buffer computed";

	int max = -INFINITY;
	int min = INFINITY;

	for(unsigned int i=0;i<400;i++){
		for(unsigned int j=0;j<400;j++){
			if(max < buffer[i][j]) max = buffer[i][j];
			if(min > buffer[i][j]) min = buffer[i][j];
		}
	}

	ofPixels pix = frame.getPixels();
	int k = 0;
	for(unsigned int i=0;i<400;i++){
		for(unsigned int j=0;j<400;j++){
			buffer[i][j] = buffer[i][j] / max * 255;
			pix[k] = buffer[i][j];
			pix[k+1] = buffer[i][j];
			pix[k+2] = buffer[i][j];
			k+=3;
		}
	}
	frame.setFromPixels(pix);
	frame.update();
	ofLogNotice("DEBUG") << "Data normalized k=" << k;
}

double GaussianSpace::phi(double x, double y){
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

	Vector2d q(x,y), p(2,2);
	Vector2d v = q-p;
	Matrix<double, 1, 2> i;
	if(v[1] > 0){
		i = v.transpose()*sigF.inverse();
	}else {
		i = v.transpose()*sigR.inverse();
	}

	double j =i*v;

	return exp(-0.5*j);
}

void GaussianSpace::draw(double x, double y) {
	ofPushMatrix();
		ofTranslate(this->getX(), this->getY());
		ofSetHexColor(0xFFFFFF);
		frame.draw(0,0);
	ofPopMatrix();
}
