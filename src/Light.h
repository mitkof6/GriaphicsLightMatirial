#ifndef LIGHT_H_
#define LIGHT_H_

#include <math.h>

#include "GL/glut.h"

#define PI 3.14

class Light{

public:
	Light(
		int light,
		float px, float py, float pz, float pw,
		float ax, float ay, float az, float aw,
		float dx, float dy, float dz, float dw,
		float sx, float sy, float sz, float sw);
	~Light(void);

	void update();

private:
	GLfloat position[4];
	GLfloat ambientLight[4];
	GLfloat diffuseLight[4];
	GLfloat specularLight[4];
	int light;
	float angle;

};

#endif

