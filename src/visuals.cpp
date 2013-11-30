#include <string.h>
#include <math.h>

#include "visuals.h"

#include "Object.h"
#include "Light.h"

#include "GL/glut.h"

Object mesh;

Light light1(
	GL_LIGHT0,
	L1_X, L1_Y, L1_Z, 1.0,
	0.2, 0.2, 0.2, 1.0,
	0.3, 0.3, 0.3, 1.0,
	1.0, 1.0, 1.0, 1.0);

Light light2(
	GL_LIGHT1,
	L2_X, L2_Y, L2_Z, 1.0,
	0.2, 0.2, 0.2, 1.0,
	0.3, 0.3, 0.3, 1.0,
	1.0, 1.0, 1.0, 1.0);


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

	glTranslatef(-3, 0 ,0);

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
	//angle+=1;

	light1.update();
	light2.update();

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
	glColorMaterial( GL_FRONT, GL_AMBIENT || GL_DIFFUSE || GL_SPECULAR );

	GLfloat specref[4];
	specref[0] = 0.247; specref[1] = 0.225; specref[2] = 0.065; specref[3] = 1.0;
	glMaterialfv(GL_FRONT,GL_AMBIENT,specref);
	specref[0] = 0.346; specref[1] = 0.314; specref[2] = 0.090; specref[3] = 1.0;
	glMaterialfv(GL_FRONT,GL_DIFFUSE,specref);
	specref[0] = 0.797; specref[1] = 0.724; specref[2] = 0.208; specref[3] = 1.0;
	glMaterialfv(GL_FRONT,GL_SPECULAR,specref);
	glMaterialf(GL_FRONT, GL_SHININESS,128);
	

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	//glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

	
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
	//glFrontFace(GL_CCW);

	// Black background
	glClearColor(0.0f,0.0f,0.0f,1.0f);
}

