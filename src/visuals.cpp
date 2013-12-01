#include <string.h>
#include <iostream>
#include <cmath>
#include "Object.h"

#include "visuals.h"

Object mesh;

GLfloat light_position1[] = { L1_X, L1_Y, L1_Z, 1.0 };
GLfloat light_position2[] = { L2_X, L2_Y, L2_Z, 1.0 };

GLfloat ambientLight[] = { 0.2, 0.2, 0.2, 1.0 };
GLfloat diffuseLight[] = { 0.8, 0.8, 0.8, 1.0 };
GLfloat specularLight[] = { 1.0, 1.0, 1.0, 1.0 };

float rotationA = 90;
float lightAngle = 0;

void updateLightPosition(){
	light_position1[0] = L1_X*sin(lightAngle*M_PI/360.0);
	light_position1[2] = L1_Z*cos(lightAngle*M_PI/360.0);

	light_position2[0] = L2_X*sin(lightAngle*M_PI/360.0);
	light_position2[2] = L2_Z*cos(lightAngle*M_PI/360.0);

	glLightfv( GL_LIGHT0, GL_POSITION, light_position1);
	glLightfv( GL_LIGHT1, GL_POSITION, light_position2);

}

void updateLightIntensity(){

	float temp[4];

	temp[0] = ambientLight[0]*((sin(lightAngle*M_PI/360.0)+1)/2.0f);
	temp[1] = ambientLight[1]*((cos(lightAngle*M_PI/360.0)+1)/2.0f);
	temp[2] = ambientLight[2];
	temp[3] = ambientLight[3];
	glLightfv( GL_LIGHT0, GL_AMBIENT, temp );

	temp[0] = diffuseLight[0]*((sin(lightAngle*M_PI/360.0)+1)/2.0f);
	temp[1] = diffuseLight[1]*((cos(lightAngle*M_PI/360.0)+1)/2.0f);
	temp[2] = diffuseLight[2];
	temp[3] = diffuseLight[3];
	glLightfv( GL_LIGHT0, GL_DIFFUSE, temp );

	temp[0] = specularLight[0]*((sin(lightAngle*M_PI/360.0)+1)/2.0f);
	temp[1] = specularLight[1]*((cos(lightAngle*M_PI/360.0)+1)/2.0f);
	temp[2] = specularLight[2];
	temp[3] = specularLight[3];
	glLightfv( GL_LIGHT0, GL_SPECULAR, specularLight);

	temp[0] = ambientLight[0]*((sin(lightAngle*M_PI/360.0)+1)/2.0f);
	temp[1] = ambientLight[1];
	temp[2] = ambientLight[2]*((cos(lightAngle*M_PI/360.0)+1)/2.0f);
	temp[3] = ambientLight[3];
	glLightfv( GL_LIGHT1, GL_AMBIENT, temp );

	temp[0] = diffuseLight[0]*((sin(lightAngle*M_PI/360.0)+1)/2.0f);
	temp[1] = diffuseLight[1];
	temp[2] = diffuseLight[2]*((cos(lightAngle*M_PI/360.0)+1)/2.0f);
	temp[3] = diffuseLight[3];
	glLightfv( GL_LIGHT1, GL_DIFFUSE, temp );

	temp[0] = specularLight[0]*((sin(lightAngle*M_PI/360.0)+1)/2.0f);
	temp[1] = specularLight[1];
	temp[2] = specularLight[2]*((cos(lightAngle*M_PI/360.0)+1)/2.0f);
	temp[3] = specularLight[3];
	glLightfv( GL_LIGHT1, GL_SPECULAR, specularLight);
}

void updateMatirial(){

	GLfloat specref[4];
	specref[0] = 0.175;
	specref[1] = 0.012*((sin(lightAngle*M_PI/360.0)+1)/2.0f);
	specref[2] = 0.012*((cos(lightAngle*M_PI/360.0)+1)/2.0f);
	specref[3] = 0.55;
	glMaterialfv(GL_FRONT,GL_DIFFUSE,specref);

	specref[0] = 0.614*((sin(lightAngle*M_PI/360.0)+1)/2.0f);
	specref[1] = 0.041;
	specref[2] = 0.041*((cos(lightAngle*M_PI/360.0)+1)/2.0f);
	specref[3] = 0.55;
	glMaterialfv(GL_FRONT,GL_SPECULAR,specref);

	glMaterialf(GL_FRONT,GL_SHININESS,76.8);
}

void Render(){
	//CLEARS FRAME BUFFER ie COLOR BUFFER& DEPTH BUFFER (1.0)
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// and the depth buffer
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	glTranslatef(0,0,-10);
	glRotatef(rotationA, 0,  1, 0);

	mesh.draw();

	//glTranslatef(-3, 0, 0);
	//glutSolidTeapot(1);

	glutSwapBuffers();
}

//-----------------------------------------------------------

void Resize(int w, int h){

	// define the visible area of the window ( in pixels )
	if (h==0) h=1;
	glViewport(0,0,w,h);

	// Setup viewing volume

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60.0, (float)w/(float)h, 1.0, 500.0);
}

void Idle(){
	if(ROTATE){
		rotationA+=0.1;
	}
	
	if(!DEFAULT_LIGHT){
		lightAngle++;
		updateLightPosition();
		updateLightIntensity();
	}

	if(!COLOR_MAPING){
		updateMatirial();
	}

	glutPostRedisplay();
}

void Setup(){
	//obj
	mesh.loadObj(PATH, false);
	mesh.correctNormalDirection();
	mesh.calculatePerVertexNormals();

	//Parameter handling
	if(SMOOTH){
		glShadeModel (GL_SMOOTH);
	}else{
		glShadeModel(GL_FLAT);
	}

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glClearDepth(1);

	if(COLOR_MAPING){
		glEnable(GL_COLOR_MATERIAL);
		glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE || GL_SPECULAR);
	}
	
	if(!DEFAULT_LIGHT){
		glEnable(GL_LIGHT1);

	}else{
		GLfloat light_position[] = {L1_X, L1_Y, L1_Z, 1.0 };
		glLightfv( GL_LIGHT0, GL_POSITION, light_position);

		GLfloat ambientLight[] = { 0.3, 0.3, 0.3, 1.0 };
		GLfloat diffuseLight[] = { 0.8, 0.8, 0.8, 1.0 };
		GLfloat specularLight[] = { 1.0, 1.0, 1.0, 1.0 };

		glLightfv( GL_LIGHT0, GL_AMBIENT, ambientLight );
		glLightfv( GL_LIGHT0, GL_DIFFUSE, diffuseLight );
		glLightfv( GL_LIGHT0, GL_SPECULAR, specularLight);

		glMaterialfv(GL_FRONT,GL_SPECULAR,specularLight);
		glMaterialf(GL_FRONT,GL_SHININESS,76.8);
	}

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	
	

	if(FILL){
		glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	}else{
		glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	}

	// Black background
	glClearColor(0.0f,0.0f,0.0f,1.0f);

}

