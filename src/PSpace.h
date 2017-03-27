/*
 * PSpace.h
 *
 *  Created on: Mar 27, 2017
 *      Author: paco
 */

#ifndef SRC_PSPACE_H_
#define SRC_PSPACE_H_

#include "SocialSpace.h"

class PSpace: public SocialSpace {
public:
	PSpace(double innerRadius, double outerRadius);
	PSpace(int id, double innerRadius, double outerRadius);
	PSpace(double x, double y, double innerRadius, double outerRadius);
	PSpace(int id, double x, double y, double innerRadius, double outerRadius);

	PSpace(double innerRadius, double outerRadius, std::vector<Agent*>& a);
	PSpace(int id, double innerRadius, double outerRadius, std::vector<Agent*>& a);
	PSpace(int id, double x, double y, double innerRadius, double outerRadius, std::vector<Agent*>& a);
	PSpace(double x, double y, double innerRadius, double outerRadius, std::vector<Agent*>& a);

	~PSpace();

	void draw(double x, double y);


	// Getters & Setters
	double getInnerRadius() const {
		return inner_radius;
	}

	void setInnerRadius(double innerRadius) {
		inner_radius = innerRadius;
	}

	double getOuterRadius() const {
		return outer_radius;
	}

	void setOuterRadius(double outerRadius) {
		outer_radius = outerRadius;
	}

private:
	double inner_radius;
	double outer_radius;
};

#endif /* SRC_PSPACE_H_ */
