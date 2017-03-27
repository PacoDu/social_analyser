/*
 * LocalizedObject.h
 *
 *  Created on: Mar 27, 2017
 *      Author: paco
 */

#ifndef SRC_LOCALIZEDOBJECT_H_
#define SRC_LOCALIZEDOBJECT_H_

class LocalizedObject {
public:
	LocalizedObject();
	LocalizedObject(double x, double y);
	virtual ~LocalizedObject();

	double getX() const {
		return x;
	}

	void setX(double x) {
		this->x = x;
	}

	double getY() const {
		return y;
	}

	void setY(double y) {
		this->y = y;
	}

protected:
	double x;
	double y;
};

#endif /* SRC_LOCALIZEDOBJECT_H_ */
