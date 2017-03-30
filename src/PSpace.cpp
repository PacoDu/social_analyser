/*
 * PSpace.cpp
 *
 *  Created on: Mar 27, 2017
 *      Author: paco
 */

#include "PSpace.h"


PSpace::PSpace(double innerRadius, double outerRadius, std::vector<Agent*>& a, double x, double y, int id):
		GroupSocialSpace(a,x,y,id), inner_radius(innerRadius), outer_radius(outerRadius){
}

PSpace::PSpace(double innerRadius, double outerRadius, double x, double y, int id):
		GroupSocialSpace(x,y,id), inner_radius(innerRadius), outer_radius(outerRadius){
}

PSpace::~PSpace() {
	// TODO Auto-generated destructor stub
}

void PSpace::draw(double x, double y) {
	ofPushMatrix();
		ofSetHexColor(0xefbbff);
		ofTranslate(x+this->getX(), y+this->getY());

//		ofNoFill();
//		ofSetLineWidth(this->getOuterRadius() - this->getInnerRadius());
		ofDrawCircle(0, 0, this->getOuterRadius());
//		ofFill();

//		ofSetHexColor(0x011f4b);
//		ofDrawCircle(0,0,5);
	ofPopMatrix();
}
