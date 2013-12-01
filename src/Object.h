#ifndef OBJECT_H_
#define OBJECT_H_

#include <vector>
#include <string>
#include <stdio.h>
#include <cmath>

#include "Vector3D.h"
#include "Triangle.h"
#include "Ray.h"


#include "GL/glut.h"

#define OFFSET 10
#define M_PI 3.14

using namespace std;

class Object {
public:
	Object();
	virtual ~Object();

	void loadObj(string filename, bool ccw);
	void correctNormalDirection();
	void calculatePerVertexNormals();

	void draw();

private:
	vector<Vector3D> vertices;
	vector<Vector3D> normals;
	vector<Triangle> triangles;

	Vector3D mapToSpherical(Vector3D v);
	void setColorFromSpherical(Vector3D v);
};

#endif /* OBJECT_H_ */
