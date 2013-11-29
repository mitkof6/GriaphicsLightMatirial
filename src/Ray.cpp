/*
 * Ray.cpp
 *
 *  Created on: Nov 29, 2013
 *      Author: crow
 */

#include "Ray.h"

Ray::Ray(Vector3D o, Vector3D d) {
	orig = o;
	dir = d;
}

Ray::~Ray() {

}

Vector3D Ray::getPoint(float t){
	return orig+dir*t;
}
