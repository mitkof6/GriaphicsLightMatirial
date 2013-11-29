#include "Object.h"
#include <iostream>

Object::Object() {

}

Object::~Object() {

}

void Object::loadObj(string filename, bool ccw){

	Vector3D v;
	int f1, f2, f3;
	char line[128];
	FILE *objfile;
	float mX = 0, mY = 0, mZ = 0;

	if (!(objfile = fopen(filename.c_str(), "rt"))) return;

	while (fgets(line, 128, objfile)) {
		switch (line[0]) {
		case 'v':
			sscanf(&line[1],"%f %f %f", &v.x, &v.y, &v.z);
			mX += v.x;
			mY += v.y;
			mZ += v.z;

			vertices.push_back(v);
			break;
		case 'f':
			sscanf(&line[1],"%d%d%d", &f1, &f2, &f3);
			if (ccw){
				triangles.push_back(
						Triangle(
								vertices[--f1],
								vertices[--f3],
								vertices[--f2]));
			}else{
				triangles.push_back(
						Triangle(
								vertices[--f1],
								vertices[--f2],
								vertices[--f3]));
			}
			break;
		default:
			continue;
		};
	}

	fclose(objfile);
}

void Object::correctNormalsDirection(){

	for(unsigned i = 0;i<triangles.size();i++){
		Ray ray = Ray(
				triangles[i].center+triangles[i].n*OFFSET,
				triangles[i].n);
		int counter = 0;

		for(unsigned j = 0;j<triangles.size();j++){
			if(i!=j){
				if(triangles[j].intersect(ray)){
					counter++;
				}
			}
		}

		if(counter%2!=0){
			//std::cout<<"Intersections: "<<counter<<"\n";
			triangles[i].n = triangles[i].n*(-1);
		}
	}
}

void Object::draw(){

	glPushMatrix();

	glBegin(GL_TRIANGLES);
		glColor3f(.5, .5, .5);
		for(unsigned i = 0;i<triangles.size();i++){

			glNormal3f(
					normals[i].x,
					normals[i].y,
					normals[i].z);

			glVertex3f(
					triangles[i].v0.x,
					triangles[i].v0.y,
					triangles[i].v0.z);
			glVertex3f(
					triangles[i].v1.x,
					triangles[i].v1.y,
					triangles[i].v1.z);
			glVertex3f(
					triangles[i].v2.x,
					triangles[i].v2.y,
					triangles[i].v2.z);



		}

	glEnd();

	glPopMatrix();

}

void Object::calculatePerVertexNormals(){

	for(unsigned i = 0;i<vertices.size();i++){
		Vector3D accum(0, 0, 0);
		for(unsigned j = 0;j<triangles.size();j++){
			if(
				vertices[i].equals(triangles[j].v0)||
				vertices[i].equals(triangles[j].v1)||
				vertices[i].equals(triangles[j].v2)){

				accum = accum + triangles[j].n;

			}
		}
		normals.push_back(accum.normalize());
	}

}


