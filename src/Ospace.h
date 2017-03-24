/*
 * Ospace.h
 *
 *  Created on: Mar 24, 2017
 *      Author: paco
 */

#ifndef SRC_OSPACE_H_
#define SRC_OSPACE_H_

class Ospace {
public:
	Ospace(double x, double y);
	virtual ~Ospace();

private:
	double x;
	double y;
	double radius;

};

#endif /* SRC_OSPACE_H_ */
