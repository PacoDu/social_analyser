/*
 * utils.h
 *
 *  Created on: Apr 12, 2017
 *      Author: paco
 */

#ifndef SRC_UTILS_H_
#define SRC_UTILS_H_

#include <stdbool.h>
#include <math.h>
#include <float.h>

#undef Success // Eigen import clash with X11, dirty fix
#include "ofxMatrixEigen.h"
#include <cmath>
using namespace Eigen;

float vProjection(float value, float inputMin, float inputMax, float outputMin, float outputMax, bool clamp = false);
double distance(Vector3d a, Vector3d b);
int planSide(Vector3d testedPoint, Vector3d planeNormalA, Vector3d a);
Vector3d lineIntersectionPoint(Vector3d ps1, Vector3d pe1, Vector3d ps2, Vector3d pe2);
int rayIntersectionPoint(Vector3d as, Vector3d ad, Vector3d bs, Vector3d bd, Vector3d* intersection);

#endif /* SRC_UTILS_H_ */
