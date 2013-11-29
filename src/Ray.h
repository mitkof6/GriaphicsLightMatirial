#ifndef RAY_H_
#define RAY_H_

#include "Vector3D.h"

class Ray {
public:
	Vector3D orig, dir;

	Ray(Vector3D o, Vector3D d);
	virtual ~Ray();

	Vector3D getPoint(float t);

};

#endif /* RAY_H_ */
