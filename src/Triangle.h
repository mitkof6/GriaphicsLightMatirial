#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include <vector>

#include "Vector3D.h"
#include "Ray.h"

using namespace std;

class Triangle {
public:

	Vector3D n;
	Vector3D center;

	int a, b, c;

	Triangle(vector<Vector3D> &v, int ve0 , int ve1, int ve2);
	virtual ~Triangle();

	Vector3D v0();
	Vector3D v1();
	Vector3D v2();

	bool intersect(Ray &r);

private:

	vector<Vector3D> *vertices;

};

#endif /* TRIANGLE_H_ */
