/*
 * PSpace.cpp
 *
 *  Created on: Mar 27, 2017
 *      Author: paco
 */

#include "PSpace.h"

PSpace::~PSpace() {
	// TODO Auto-generated destructor stub
}

PSpace::PSpace(double innerRadius, double outerRadius):
		SocialSpace(), inner_radius(innerRadius), outer_radius(outerRadius) {
}

PSpace::PSpace(int id, double innerRadius, double outerRadius):
		SocialSpace(id), inner_radius(innerRadius), outer_radius(outerRadius) {
}

PSpace::PSpace(double x, double y, double innerRadius, double outerRadius):
		SocialSpace(x,y), inner_radius(innerRadius), outer_radius(outerRadius) {
}

PSpace::PSpace(int id, double x, double y, double innerRadius,
		double outerRadius): SocialSpace(id, x, y), inner_radius(innerRadius), outer_radius(outerRadius) {
}

PSpace::PSpace(double innerRadius, double outerRadius, std::vector<Agent*>& a):
		SocialSpace(a), inner_radius(innerRadius), outer_radius(outerRadius){
}

PSpace::PSpace(int id, double innerRadius, double outerRadius,
		std::vector<Agent*>& a):
		SocialSpace(id, a), inner_radius(innerRadius), outer_radius(outerRadius){
}

PSpace::PSpace(int id, double x, double y, double innerRadius,
		double outerRadius, std::vector<Agent*>& a):
		SocialSpace(id, x, y, a), inner_radius(innerRadius), outer_radius(outerRadius){
}

PSpace::PSpace(double x, double y, double innerRadius, double outerRadius,
		std::vector<Agent*>& a):
		SocialSpace(x,y,a), inner_radius(innerRadius), outer_radius(outerRadius){
}

void PSpace::draw(double x, double y) {
	ofPushMatrix();
		ofSetHexColor(0xefbbff);
		ofTranslate(x+this->getX(), y+this->getY());

		ofNoFill();
		ofSetLineWidth(this->getOuterRadius() - this->getInnerRadius());
		ofDrawCircle(0, 0, this->getInnerRadius());
		ofFill();

//		ofSetHexColor(0x011f4b);
//		ofDrawCircle(0,0,5);
	ofPopMatrix();
}
