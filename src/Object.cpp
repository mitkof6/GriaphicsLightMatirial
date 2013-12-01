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
						Triangle(vertices,--f1, --f3, --f2));
			}else{
				triangles.push_back(
						Triangle(vertices,--f1, --f2, --f3));
			}
			break;
		default:
			continue;
		};
	}

	//centered
	Vector3D centroid(
			mX/vertices.size(),
			mY/vertices.size(),
			mZ/vertices.size());
	for(unsigned i = 0;i<vertices.size();i++){
		vertices[i] = vertices[i] - centroid;
	}

	fclose(objfile);
}

void Object::correctNormalDirection(){

	Ray ray = Ray(
		triangles[0].v0(),
		triangles[0].n);

	int counter = 0;

	for(unsigned j = 0;j<triangles.size();j++){
		if(triangles[j].intersect(ray)){
			counter++;
		}
	}
	std::cout<<"Intersections: "<<counter<<"\n";
	if(counter%2!=0){
		//
		for(unsigned j = 0;j<triangles.size();j++){
			triangles[j].n = triangles[j].n*(-1);
		}
	}
}

void Object::draw(){

	glPushMatrix();

	glBegin(GL_TRIANGLES);
		//glColor3f(1.0, 1.0, 0.0);
		for(unsigned i = 0;i<triangles.size();i++){
			//normals[triangles[i].a].toString();
			glNormal3f(
					normals[triangles[i].a].x,
					normals[triangles[i].a].y,
					normals[triangles[i].a].z);
			setColorFromSpherical(mapToSpherical(triangles[i].v0()));
			glVertex3f(
					triangles[i].v0().x,
					triangles[i].v0().y,
					triangles[i].v0().z);

			glNormal3f(
					normals[triangles[i].b].x,
					normals[triangles[i].b].y,
					normals[triangles[i].b].z);
			setColorFromSpherical(mapToSpherical(triangles[i].v1()));
			glVertex3f(
					triangles[i].v1().x,
					triangles[i].v1().y,
					triangles[i].v1().z);

			glNormal3f(
					normals[triangles[i].c].x,
					normals[triangles[i].c].y,
					normals[triangles[i].c].z);
			setColorFromSpherical(mapToSpherical(triangles[i].v2()));
			glVertex3f(
					triangles[i].v2().x,
					triangles[i].v2().y,
					triangles[i].v2().z);



		}

	glEnd();

	glPopMatrix();

}

void Object::calculatePerVertexNormals(){

	for(unsigned i = 0;i<vertices.size();i++){
		Vector3D accum(0, 0, 0);
		for(unsigned j = 0;j<triangles.size();j++){
			if(
				vertices[i].equals(triangles[j].v0())||
				vertices[i].equals(triangles[j].v1())||
				vertices[i].equals(triangles[j].v2())){

				accum = accum + triangles[j].n;

			}
		}
		normals.push_back(accum.normalize());
	}

}

Vector3D Object::mapToSpherical(Vector3D v){
	v = v.normalize();
	float r = v.magnitude();
	float th = atan2(v.z, r);
	float phi = atan2(v.y, v.x);

	return Vector3D(r, th, phi);
}

void Object::setColorFromSpherical(Vector3D v){
	glColor3f(1.0, (v.y+M_PI/2)/(M_PI), (v.z+M_PI)/(2*M_PI));
}


