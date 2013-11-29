#include "Triangle.h"

Triangle::Triangle(Vector3D &a, Vector3D &b, Vector3D &c) {
	v0 = a;
	v1 = b;
	v2 = c;

	center = (a+b+c)/3.0;

	n = ((b-a).cross(a-c)).normalize();
}

Triangle::~Triangle() {

}

bool Triangle::intersect(Ray &r) {
	Vector3D v0v1 = v1 - v0;
	Vector3D v0v2 = v2 - v0;

	Vector3D N = v0v1.cross(v0v2);

	float nDotRay = N.dot(r.dir);

	if (N.dot(r.dir) == 0) return false;

	// ray parallel to triangle
	float d = N.dot(v0);
	float t = -(N.dot(r.orig) + d) / nDotRay;

	// inside-out test
	Vector3D Phit = r.getPoint(t);//r(t)

	// inside-out test edge0
	Vector3D v0p = Phit - v0;
	float v = N.dot(v0v1.cross(v0p));
	if (v < 0) return false;

	// P outside triangle
	// inside-out test edge1

	Vector3D v1p = Phit - v1;
	Vector3D v1v2 = v2 - v1;

	float w = N.dot(v1v2.cross(v1p));
	if (w < 0) return false;

	// P outside triangle
	// inside-out test edge2
	Vector3D v2p = Phit - v2;
	Vector3D v2v0 = v0 - v2;
	float u = N.dot(v2v0.cross(v2p));
	if (u < 0) return false;

	// P outside triangle
	return true;

}
