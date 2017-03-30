/*
 * Point.h
 *
 *  Created on: Mar 30, 2017
 *      Author: paco
 */

#ifndef SRC_POINT_H_
#define SRC_POINT_H_

class Point {
public:
	Point();
	Point(double x, double y, double z = 0);
	virtual ~Point();

	double x;
	double y;
	double z;
};

#endif /* SRC_POINT_H_ */
