#include <stdio.h>
#include <string.h>
#include <math.h>
#include "GL/glut.h"

#include "visuals.h"

#include "Object.h"

Object mesh;

GLfloat light_position1[] = { L1_X, L1_Y, L1_Z, 0.0 };
GLfloat light_position2[] = { L2_X, L2_Y, L2_Z, 0.0 };

float angle = 90;
float lightAngle = 0;
void Render(){
	//CLEARS FRAME BUFFER ie COLOR BUFFER& DEPTH BUFFER (1.0)
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// and the depth buffer
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	glTranslatef(0,0,-10);
	glRotatef(angle, 0, 1, 0);

	mesh.draw();

	glTranslatef(-3*cos(lightAngle*PI/180.0), 0, -3*sin(lightAngle*PI/180.0));
	glutSolidTeapot(1);

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
	// Light source movement
	//angle+=0.1;
	lightAngle++;

	light_position1[0] = L1_X*cos(lightAngle*PI/180.0);
	light_position1[2] = L1_Z*sin(lightAngle*PI/180.0);

	light_position2[0] = L2_X*cos(lightAngle*PI/180.0);
	light_position2[2] = L2_Z*sin(lightAngle*PI/180.0);

	//light_position2[] = { L2_X, L2_Y, L2_Z, 0.0 };

	glLightfv( GL_LIGHT0, GL_POSITION, light_position1);
	glLightfv( GL_LIGHT1, GL_POSITION, light_position2);

	glutPostRedisplay();
}

void Setup(){
	//load obj
	mesh.loadObj("model.obj", false);
	//mesh.correctNormalsDirection();
	mesh.calculatePerVertexNormals();

	//Parameter handling
	glShadeModel (GL_SMOOTH);
	//glShadeModel(GL_FLAT);

	//(02)
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	//renders a fragment if its z value is less or equal of the stored value
	glClearDepth(1);

	// (06) // polygon rendering mode
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial( GL_FRONT, GL_AMBIENT_AND_DIFFUSE );



	GLfloat ambientLight[] = { 0.3, 0.3, 0.3, 1.0 };
	GLfloat diffuseLight[] = { 0.3, 0.3, 0.3, 1.0 };
	GLfloat specularLight[] = { 1.0, 1.0, 1.0, 1.0 };


	glLightfv( GL_LIGHT0, GL_AMBIENT, ambientLight );
	glLightfv( GL_LIGHT0, GL_DIFFUSE, diffuseLight );

	glLightfv( GL_LIGHT1, GL_AMBIENT, ambientLight );
	glLightfv( GL_LIGHT1, GL_DIFFUSE, diffuseLight );

	//(05)
	/*
	glLightfv( GL_LIGHT0, GL_SPECULAR, specularLight);
	GLfloat specref[] = { 1.0, 1.0, 1.0, 1.0 };
	glMaterialfv(GL_FRONT,GL_SPECULAR,specref);
	glMateriali(GL_FRONT,GL_SHININESS,64);
	//*/

	//(06) Material Parameters
	//(06a) for Gold
	/*
	glLightfv( GL_LIGHT0, GL_SPECULAR, specularLight);
	glLightfv( GL_LIGHT1, GL_SPECULAR, specularLight);
	GLfloat specref[4];
	specref[0] = 0.247; specref[1] = 0.225; specref[2] = 0.065; specref[3] = 1.0;
	glMaterialfv(GL_FRONT,GL_AMBIENT,specref);
	specref[0] = 0.346; specref[1] = 0.314; specref[2] = 0.090; specref[3] = 1.0;
	glMaterialfv(GL_FRONT,GL_DIFFUSE,specref);
	specref[0] = 0.797; specref[1] = 0.724; specref[2] = 0.208; specref[3] = 1.0;
	glMaterialfv(GL_FRONT,GL_SPECULAR,specref);
	glMaterialf(GL_FRONT,GL_SHININESS,83.2);
	 //*/

	//(06b) for Ruby
	/*
	glLightfv( GL_LIGHT0, GL_SPECULAR, specularLight);
	GLfloat specref[4];
	specref[0] = 0.175; specref[1] = 0.012; specref[2] = 0.012; specref[3] = 0.55;
	glMaterialfv(GL_FRONT,GL_AMBIENT,specref);
	specref[0] = 0.614; specref[1] = 0.041; specref[2] = 0.041; specref[3] = 0.55;
	glMaterialfv(GL_FRONT,GL_DIFFUSE,specref);
	specref[0] = 0.728; specref[1] = 0.308; specref[2] = 0.308; specref[3] = 0.55;
	glMaterialfv(GL_FRONT,GL_SPECULAR,specref);
	glMaterialf(GL_FRONT,GL_SHININESS,76.8);
	 //*/

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	//glEnable(GL_LIGHT1);

	// (04)
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	//glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

	//(03)
	//glEnable(GL_CULL_FACE);
	//glFrontFace(GL_CW);
	//glFrontFace(GL_CCW);



	//(01) BLENDING
	//glEnable(GL_BLEND);
	// incoming //  // stored //
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	// Black background
	glClearColor(0.0f,0.0f,0.0f,1.0f);

}

