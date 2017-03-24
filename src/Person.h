/*
 * Person.h
 *
 *  Created on: Mar 24, 2017
 *      Author: paco
 */

#ifndef SRC_PERSON_H_
#define SRC_PERSON_H_

#include "ofMain.h"

class Person {
public:
	Person(int id);
	Person(int id, double x, double y, double theta);
	virtual ~Person();

	ofVec2f getPosition();
	ofVec2f getDirection();

	int getId() const;
	void setId(int id);
	double getX() const;
	void setX(double x);
	double getY() const;
	void setY(double y);
	double getTheta() const;
	void setTheta(double theta);


protected:
	double x;
	double y;
	double theta;

private:
	int id;

};

#endif /* SRC_PERSON_H_ */
