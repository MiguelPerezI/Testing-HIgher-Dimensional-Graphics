#include <iostream>
#include <cstdlib>
#include "VectorND.hpp"
#include <math.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>

/*Este metodo pide al sistema el tamaño y tipo de memoria*/
/*que necesitamos para un vector*/
/*Se usa como   	VectorND vecGo;      */
/*					vecGo.initVectorND(5, 1, 1, 1, 1, 1)*/
void VectorND::initVectorND(int n, ...){

	va_list list;
	this->n = n;
	this->A = (double *) malloc (n * sizeof(double));
	int i;

	va_start(list, n);
	/**/
	/**/	for (int i = 0; i < n; i++)
	/**/		this->A[i] = va_arg(list, double);
	/**/
	va_end(list);
	
	double norma = 0;
	for (i = 0; i < this->n; i++)
		norma += this->A[i] * this->A[i];

	this->norma = sqrt(norma);
}

/*O simplemente crea un espacio de memoria vacío pero ya listo para almacenar objetos*/
void VectorND::initVectorNDType2(int n){

	this->n = n;
	this->A = (double *) malloc (n * sizeof(double));
}

/*Con este metodo puedes acceder al número de filas.*/
/*int a = vecGo.dim();*/
int VectorND::dim() {
	return this->n;
}

double VectorND::norm() {
	return this->norma;
}

void VectorND::zeroVectorND(int n) {

	this->initVectorNDType2(n);
	for (int i = 0; i < n; i++)
			this->A[i] = 0;

	this->norma = 0.0;
}

/*Cuenta cuantos digitos tiene un double*/
/*int a = vecGo.digitCounter(0.3434)*/
int VectorND::digitCounter(double a) {
	
	string hello = to_string(a);
	int ret = hello.length();
	return ret;
}

/*Este metodo escribe en pantalla de manera ordenada*/
/*matGo.escVectorND();*/
void VectorND::escVectorND() {

	int k = 20;
	printf("(");
	for (int i = 0; i < this->n; i++) {
			cout << to_string(this->A[i]);
			int l = (this)->digitCounter(this->A[i]);
			for (int r = 0; r < k - l; r++)
				cout << " ";
	}
	printf(")");

}

/*La mayoría de las veces trabajaremos con Vectores en 3D entonces haremos un metodo*/
/*Que trabaja con vectores de dimensión 3*/
void VectorND::updateVector3D(double x, double y, double z) {

	if (this->n != 3) printf("\n\nVECTORND CANDIDATE NOT AVAILABLE FOR UPDATE\n\nCHECK DIMENSION\n\n");
	else {

		/*Actualizamos cada una de las nuevas entradas*/
		this->A[0] = x;
		this->A[1] = y;
		this->A[2] = z;

		/*La norma no se actualiza sola también es necesario recalcularla*/
		double norma = 0;
		for (int i = 0; i < this->n; i++)
			norma += this->A[i] * this->A[i];

		this->norma = sqrt(norma);		
	}
}

void VectorND::updateVector3DP(VectorND p) {

	this->updateVector3D(p.A[0], p.A[1], p.A[2]);
}

double VectorND::access(int i)
{	
	if(i >= this->n) 
	{	
		return printf("The dimension is wrong");
	}
	else
	{
		return this->A[i];
	}
}

void VectorND::AddVector3D(VectorND B)
{
	if(B.dim() != this->n){
		printf("\n\n THIS OPERATION CANNOT BE EXECUTED \n\n CHECK DIMENSION \n\n");
	}

	else{
	for (int i = 0; i < this->n; i++)
		this->A[i] += B.access(i);

	double norma = 0;
	for (int i = 0; i < this->n; i++)
		norma += this->A[i] * this->A[i];

	this->norma = sqrt(norma);	
	}
}

void VectorND::SumVector3D(VectorND B, VectorND C)
{
	this-> n = 3; 

	if(C.dim() != B.dim() != this->n)
		printf("\n\n THIS OPERATION CANNOT BE EXECUTED \n\n CHECK DIMENSION \n\n");
	
	else{
		
		for(int i = 0; i < this->n; i++)
			this->A[i] = B.access(i) + C.access(i);

		double norma = 0;
		for (int i = 0; i < this->n; i++)
			norma += this->A[i] * this->A[i];

		this->norma = sqrt(norma);	

	}
}

void VectorND::MinusVector3D(VectorND B){

if(B.dim() != this->n){
		printf("\n\n THIS OPERATION CANNOT BE EXECUTED \n\n CHECK DIMENSION \n\n");
	}

	else{
	for (int i = 0; i < this->n; i++)
		this->A[i] -= B.access(i);

	double norma = 0;
	for (int i = 0; i < this->n; i++)
		norma += this->A[i] * this->A[i];

	this->norma = sqrt(norma);	
	}
}	

void VectorND::SubVector3D(VectorND B, VectorND C)
{
	this-> n = 3; 

	if(C.dim() != B.dim() != this->n)
		printf("\n\n THIS OPERATION CANNOT BE EXECUTED \n\n CHECK DIMENSION \n\n");
	
	else{
		
		for(int i = 0; i < this->n; i++)
			this->A[i] = B.access(i) - C.access(i);

		double norma = 0;
		for (int i = 0; i < this->n; i++)
			norma += this->A[i] * this->A[i];

		this->norma = sqrt(norma);	

	}
}

void VectorND::subVectorND(VectorND a, VectorND b) {

	if (a.dim() != b.dim())
		printf("\n\n THIS OPERATION CANNOT BE EXECUTED \n\n CHECK DIMENSION \n\n");
	else {

		for (int i = 0; i < this->n; i++)
			this->A[i] = a.A[i] - b.A[i];

		double norma = 0;
		for (int i = 0; i < this->n; i++)
			norma += this->A[i] * this->A[i];

		this->norma = sqrt(norma);
	}
}

void VectorND::Cross3D(VectorND B, VectorND C){
	
	this->n = 3;

	if(C.dim() != B.dim())
		printf("\n\n THIS OPERATION CANNOT BE EXECUTED \n\n CHECK DIMENSION \n\n");	
	else{
	this->A[0] = ( B.access(1) * C.access(2)) - (B.access(2) * C.access(1));
	this->A[1] = (-B.access(0) * C.access(2)) + (B.access(2) * C.access(0));
	this->A[2] = ( B.access(0) * C.access(1)) - (B.access(1) * C.access(0));	
	
	double norma = 0;	
	for (int i = 0; i < this->n; i++)
		norma += this->A[i] * this->A[i];

	this->norma = sqrt(norma);
	}
				
}