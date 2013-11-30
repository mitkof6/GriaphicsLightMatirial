#include "Object.h"
#include <iostream>

Object::Object(int s,
		float ax, float ay, float az, float aw,
		float dx, float dy, float dz, float dw,
		float sx, float sy, float sz, float sw) {

	shininess = s;

	ambient[0] = ax;
	ambient[1] = ay;
	ambient[2] = az;
	ambient[3] = aw;

	diffuse[0] = dx;
	diffuse[1] = dy;
	diffuse[2] = dz;
	diffuse[3] = dw;

	specular[0] = sx;
	specular[1] = sy;
	specular[2] = sz;
	specular[3] = sw;


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

void Object::correctNormalsDirection(){

	
	Ray ray = Ray(
		triangles[0].center+triangles[0].n*OFFSET,
		triangles[0].n);
	int counter = 0;

	for(unsigned j = 0;j<triangles.size();j++){
		if(0!=j){
			if(triangles[j].intersect(ray)){
				counter++;
			}
		}
	}

	if(counter%2!=0){
		//std::cout<<"Intersections: "<<counter<<"\n";
		//triangles[i].n = triangles[i].n*(-1);
		glFrontFace(GL_CCW);
	}else{
		glFrontFace(GL_CW);
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
	glColor3f(1.0, 0.5+v.y/(M_PI/2), .5+v.z/(2*M_PI));
}


