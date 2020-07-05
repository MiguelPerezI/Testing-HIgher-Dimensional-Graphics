#include <iostream>
#include <cstdlib>
#include "VectorND.hpp"
#include "geometry.hpp"
#include <math.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>

void FacetOpenGL::updateNormal() {

	this->aux1.subVectorND(this->b, this->a);
	this->aux2.subVectorND(this->c, this->a);
	this->normal.Cross3D(this->aux1, this->aux2);
}

void FacetOpenGL::initFacetOpenGL(VectorND a, VectorND b, VectorND c) {

	if (a.dim() == 3 && b.dim() == 3 && c.dim() == 3) {

		this->a = a;
		this->b = b;
		this->c = c;
		this->aux1.zeroVectorND(3);
		this->aux2.zeroVectorND(3);
		this->normal.zeroVectorND(3);
		this->updateNormal();
	}
}

void FacetOpenGL::updatePoints(VectorND a, VectorND b, VectorND c) {

	this->a.updateVector3DP(a);
	this->b.updateVector3DP(b);
	this->c.updateVector3DP(c);
}

void FacetOpenGL::updateFacetOpenGL(VectorND a, VectorND b, VectorND c) {

	this->updatePoints(a, b, c);
	this->updateNormal();
}

void FacetOpenGL::renderFacetOpenGL(int mod, RotationMats U) {

	if (mod%8 == 0) glColor3ub(255, 255, 255);
	if (mod%8 == 1) glColor3ub(  0, 255, 255);
	if (mod%8 == 2) glColor3ub(  0,   0, 255);
	if (mod%8 == 3) glColor3ub(255,   0, 255);
	if (mod%8 == 4) glColor3ub(255, 255, 	 0);
	if (mod%8 == 5) glColor3ub(  0, 255, 	 0);
	if (mod%8 == 6) glColor3ub(255, 150, 	 0);
	if (mod%8 == 7) glColor3ub(255,   0, 	 0);

	U.rot3D(this->normal);
	glBegin(GL_TRIANGLES);
	glNormal3f( U.getAux().access(0), U.getAux().access(1), U.getAux().access(2));
	U.rot3D(this->a);
	glVertex3f( U.getAux().access(0), U.getAux().access(1), U.getAux().access(2));
	U.rot3D(this->b);
	glVertex3f( U.getAux().access(0), U.getAux().access(1), U.getAux().access(2));
	U.rot3D(this->c);
	glVertex3f( U.getAux().access(0), U.getAux().access(1), U.getAux().access(2));
	glEnd();
}