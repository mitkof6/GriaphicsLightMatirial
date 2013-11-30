#include "Light.h"


Light::Light(
		int l,
		float px, float py, float pz, float pw,
		float ax, float ay, float az, float aw,
		float dx, float dy, float dz, float dw,
		float sx, float sy, float sz, float sw){

	light = l;

	angle = 180;

	position[0] = px;
	position[1] = py;
	position[2] = pz;
	position[3] = pw;

	ambientLight[0] = ax;
	ambientLight[1] = ay;
	ambientLight[2] = az;
	ambientLight[3] = aw;

	diffuseLight[0] = dx;
	diffuseLight[1] = dy;
	diffuseLight[2] = dz;
	diffuseLight[3] = dw;

	specularLight[0] = sx;
	specularLight[1] = sy;
	specularLight[2] = sz;
	specularLight[3] = sw;

	glLightfv( light, GL_POSITION, position);
	glLightfv( light, GL_AMBIENT, ambientLight );
	glLightfv( light, GL_DIFFUSE, diffuseLight );
	glLightfv( light, GL_SPECULAR, specularLight);
	glEnable(light);

}


Light::~Light(void){

}

void Light::update(){
	angle++;

	GLfloat temp[4];
	temp[0] = position[0]*sin(angle*PI/180);
	temp[1] = position[1];
	temp[2] = position[2]*cos(angle*PI/180);
	temp[3] = position[3];
	glLightfv( light, GL_POSITION, temp);


	temp[0] = sin(angle*PI/180);
	temp[1] = ambientLight[1];
	temp[2] = cos(angle*PI/180);
	temp[3] = ambientLight[3];
	//glLightfv( light, GL_AMBIENT, ambientLight );

	temp[0] = sin(angle*PI/180);
	temp[1] = diffuseLight[1];
	temp[2] = cos(angle*PI/180);
	temp[3] = diffuseLight[3];
	glLightfv( light, GL_DIFFUSE, diffuseLight );

	temp[0] = sin(angle*PI/180);
	temp[1] = specularLight[1];
	temp[2] = cos(angle*PI/180);
	temp[3] = specularLight[3];
	glLightfv( light, GL_DIFFUSE, specularLight );

}
