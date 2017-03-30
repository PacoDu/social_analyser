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
	// --- CONSTRUCTOR & DESTRUCTOR
	LocalizedObject(double x = 0, double y = 0, double theta = 0);
	virtual ~LocalizedObject();

	// --- Getter & Setter
	double getX() const;
	virtual void setX(double x);
	double getY() const;
	virtual void setY(double y);
	double getTheta() const;
	void setTheta(double theta);

protected:
	double x;
	double y;
	double theta;
};

#endif /* SRC_LOCALIZEDOBJECT_H_ */
