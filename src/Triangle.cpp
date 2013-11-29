#include "Triangle.h"

Triangle::Triangle(vector<Vector3D> &v, int ve0 , int ve1, int ve2) {

	vertices = &v;

	a = ve0;
	b = ve1;
	c = ve2;

	Vector3D v0 = v[a];
	Vector3D v1 = v[b];
	Vector3D v2 = v[c];

	center = (v0+v1+v2)/3.0;

	n = ((v1-v0).cross(v0-v2)).normalize();
}

Triangle::~Triangle() {
	//delete vertices;
}

Vector3D Triangle::v0(){
	return vertices->at(a);
}

Vector3D Triangle::v1(){
	return vertices->at(b);
}

Vector3D Triangle::v2(){
	return vertices->at(c);
}

bool Triangle::intersect(Ray &r) {
	Vector3D v0v1 = v1() - v0();
	Vector3D v0v2 = v2() - v0();

	Vector3D N = v0v1.cross(v0v2);

	float nDotRay = N.dot(r.dir);

	if (N.dot(r.dir) == 0) return false;

	// ray parallel to triangle
	float d = N.dot(v0());
	float t = -(N.dot(r.orig) + d) / nDotRay;

	// inside-out test
	Vector3D Phit = r.getPoint(t);//r(t)

	// inside-out test edge0
	Vector3D v0p = Phit - v0();
	float v = N.dot(v0v1.cross(v0p));
	if (v < 0) return false;

	// P outside triangle
	// inside-out test edge1

	Vector3D v1p = Phit - v1();
	Vector3D v1v2 = v2() - v1();

	float w = N.dot(v1v2.cross(v1p));
	if (w < 0) return false;

	// P outside triangle
	// inside-out test edge2
	Vector3D v2p = Phit - v2();
	Vector3D v2v0 = v0() - v2();
	float u = N.dot(v2v0.cross(v2p));
	if (u < 0) return false;

	// P outside triangle
	return true;

}
