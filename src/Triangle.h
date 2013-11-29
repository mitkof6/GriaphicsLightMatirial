#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include "Vector3D.h"
#include "Ray.h"

class Triangle {
public:
	Vector3D v0, v1, v2;
	Vector3D n;
	Vector3D center;

	Triangle(Vector3D &a, Vector3D &b, Vector3D &c);
	virtual ~Triangle();

	bool intersect(Ray &r);

private:

};

#endif /* TRIANGLE_H_ */
