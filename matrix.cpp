#include <iostream>
#include <cstdlib>
#include "matrix.hpp"
#include <math.h>
#include <string>

/*Este metodo pide al sistema el tamaño y tipo de memoria*/
/*que necesitamos para una matriz*/
/*Se usa como   	Matriz matGo;      */
/*					matGo.initMat(5, 5)*/
void Matrix::initMat(int m, int n){

	this->m = m;
	this->n = n;
	this->A = (double **) malloc (m * sizeof(double*));
	for (int i = 0; i < m; i++)
		this->A[i] = (double *) malloc (n * sizeof(double));

}

/*Con este metodo puedes acceder al número de filas.*/
/*int a = matGo.numFila();*/
int Matrix::numFila() {
	return this->m;
}

/*Con este metodo puedes acceder al número de columnas.*/
int Matrix::numCol() {
	return this->n;
}

/*Este metodo actualiza a la matriz haciendola la matriz*/
/*nula. No regresa nada.*/
/* matGo.zeroMat(4, 4)*/
void Matrix::zeroMat(int m, int n) {

	this->initMat(m, n);
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			this->A[i][j] = 0;
}

/*Este metodo actualiza */
/*matGo.diagonalIgualAUno*/
void Matrix::diagonalIgualAUno(int m, int n) {

	this->initMat(m, n);
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (i == j) this->A[i][j] = 1;
			else this->A[i][j] = 0;
		}
	}
}

/*Cuenta cuantos digitos tiene un double*/
/*int a = matGo.digitCounter(0.3434)*/
int Matrix::digitCounter(double a) {
	
	string hello = to_string(a);
	int ret = hello.length();
	return ret;
}

/*Este metodo escribe en pantalla de manera ordenada*/
/*matGo.escMat();*/
void Matrix::escMat() {

	int k = 20;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			cout << to_string(this->A[i][j]);
			int l = (this)->digitCounter(this->A[i][j]);
			for (int r = 0; r < k - l; r++)
				cout << " ";
		}
		cout << "\n\n";
	}	
}

/*Accede a una entrada de la matriz*/
/*double x = matGo.getMat(3, 2);*/
double Matrix::getMat(int i, int j) {

	return this->A[i][j];
}

/*Este metodo accede a una entrada de la matriz y coloca*/
/*un double en el jejejejeje como un bebé.*/
/*matGo.accessMat(4, 3, 0.34222222);*/
void Matrix::accessMat(int i, int j, double x) {

	if (0 <= i && i < this->m)
		if (0 <= j && j < this->n)
			this->A[i][j] = x;
}

/*Este metodo intercambia dos filas.*/
/*matGo.swap(2, 5);*/
void Matrix::swap(int i, int k) {

	double * temp = (double *) malloc (this->n * sizeof(double));
	for (int j = 0; j < this->n; j++)
		temp[j] = this->A[i][j];	

	for (int j = 0; j < this->n; j++)
		this->A[i][j] = this->A[k][j];

	for (int j = 0; j < this->n; j++)
		this->A[k][j] = temp[j];

	free(temp);
	temp = NULL;	
}

/*Revisa si dos números reals son iguales.*/
/*Ya que al solo poner x == y siendo x e y números*/
/*reales pues puede que regrese un error. Entonces*/
/*mejor usamos una vecindad con epsilon muuy pequeño.*/
int Matrix::doubleEqual(double x, double y) {

	double d = x - y;
	double s = sqrt(d * d);

	if (s < 1.0e-20) return 1;
	else return 0;

} 

/*Muy importante ya que ordena la matriz.*/
/*Ejecuta una vez para que veas que hace exactamente.*/
/*matGo.order();*/
void Matrix::order() {

	int cont1 = 0;
	for (int j = 0; j < this->n; j++) {
		int cont = cont1;
		for (int i = cont1; i < this->m; i++) {
			if (doubleEqual(this->A[cont][j], 0) == 0) {
				(this)->swap(cont1, cont); cont1 += 1;
			}
			cont += 1;
		}
	}
}

/*Esta funcion multiplica la fila i por el inverso de su*/
/*primera entrada y luego por el inverso aditivo de la primera*/
/*entrada de la fila j. Despues suma la fila i a la fila j.*/
/*Esta ya te la sabes carnal.*/
void Matrix::fixRowRespectTo_i(int i, int j, int i0) {

	//cout << "\n" << "row := " << i << "   col := " << j << "\n";
	//cout << "ATTACK row := " << i0 << "\n";

	if (doubleEqual(this->A[i][j], 0) != 1) {

		double * tempRow = (double *) malloc (this->n * sizeof(double));
	
		for (int j0 = 0; j0 < this->n; j0++)
			tempRow[j0] = this->A[i][j0];
	
		for (int j0 = 0; j0 < this->n; j0++)
			tempRow[j0] *= (1/this->A[i][j]);
	
		for (int j0 = 0; j0 < this->n; j0++)
			tempRow[j0] *= (-1) * (this->A[i0][j]);
	
		//for (int j0 = 0; j0 < this->n; j0++)
		//	cout << tempRow[j0] << "    ";
		//cout << "\n\n";
	
		for (int j0 = 0; j0 < this->n; j0++)
			this->A[i0][j0] += tempRow[j0];
	
		free(tempRow);
		tempRow = NULL;

	}
}

/*Este metodo revisa si hay filas o columnas cero.*/
int Matrix::revisaCeros() {

	int k = 0;

	/*Aquí revisamos si hay columnas cero.*/
	int j = 0;
	double cero;
	while (j < this->n) {

		cero = 0;
		for (int i = 0; i < this->m; i++)
			cero += this->A[i][j];

		if (this->doubleEqual(cero, 0) == 1) {
			k = 1;
			break;
		}

		j += 1;
	}

	/*Aquí revisamos si hay filas cero.*/
	while (j < this->m) {

		cero = 0;
		for (int i = 0; i < this->n; i++)
			cero += this->A[i][j];

		if (this->doubleEqual(cero, 0) == 1) {
			k = 1;
			break;
		}

		j += 1;
	}

	return k;
}

/*Este metodo pone la matriz en su forma Echelon.*/
/*matGo.rowEchelonForm();*/
void Matrix::rowEchelonForm() {

	/*PRIMERO ORDENAMOS BIEN LA MATRIZ*/
	//this->order();

	/*UNA VEZ ORDENADA ANALIZAMOS LAS SIGUIENTES CASOS:*/
	if (this->revisaCeros() == 1) {
		cout << "\n\nEl método revisaCeros arrojo código 1. No podemos calcular el determinante.\n\n";
	} else {

		if (this->m != this->n) cout << "\n\nNo se puede calcular el determinante por que la matriz dada no es cuadrada.\n\n";
		else {

			cout << "\n\nCalculando Row Echlon Form.\n\n";

			int i = 0;

			for (int j = 0; j < this->n; j++) { /**//*ESTE j RECORRE CADA COLUMNA PARA CORREJIRLA*/

				//cout << "---->Quitando todos los no-ceros de la " << j << "-esima columna.\n";

				/************************/
				//						//
				//	AQUI MODIFICAMOS
				//	LAS COLUMNAS		//
				//
		     /////************************/
			/**/	for (int i0 = j+1; i0 < this->m; i0++) {
			/**/
			/**/
			/**/	
			/**/		if (doubleEqual(this->A[i0][j], 0) == 1) {
			/**/	
			/**/			/*SI (i, j) == 0 PASAR A LA SIGUIENTE FILA*/
			/**/			//cout << "(" << i0 << ", " << j << ") no fix\n";
			/**/		}
			/**/		else {
			/**/			/*SI (i, j) != 0 MULTIPLICAR LA FILA i-1 por el inverso principal de la fila i.*/
			/**/			//cout << "(" << i0 << ", " << j << ") fix\n";
			/**/			this->fixRowRespectTo_i(i, j, i0);
			/**/		}
			/**/	}
			/**/	
			/**/	i += 1;
			/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/



			}
		}
	}///
}

/*Al fin se cálcula el determinante.*/
/*matGo.determinant();*/
/*Observa y admira que tan corto queda carnal.*/
double Matrix::determinant() {

	/*Ordenamos la matriz*/
	this->order();
	//this->escMat();
	cout << "\n";
	this->rowEchelonForm();
	//this->escMat();

	double det = 1;
	for (int i = 0; i < this->m; i++)
		for (int j = 0; j < this->n; j++) {
			if (i == j) {
				det *= this->A[i][j];
				//cout << det << "   in " << i << "  " << j << "\n";
			}
		}

	//cout << "\nDET := " << det;
	return det;
}

void RotationMats::initRotationMats(double theta) {

	this->theta = theta;
	this->rotZ.initMat(3, 3);

	this->rotZ.accessMat(0, 0, cos(theta));
	this->rotZ.accessMat(1, 0, sin(theta));
	this->rotZ.accessMat(2, 0,        0.0);

	this->rotZ.accessMat(0, 1,-sin(theta));
	this->rotZ.accessMat(1, 1, cos(theta));
	this->rotZ.accessMat(2, 1,        0.0);

	this->rotZ.accessMat(0, 2,        0.0);
	this->rotZ.accessMat(1, 2,        0.0);
	this->rotZ.accessMat(2, 2,        1.0);

	this->aX.initVectorND(3, rotZ.getMat(0, 0), rotZ.getMat(1, 0), rotZ.getMat(2, 0));
	this->aY.initVectorND(3, rotZ.getMat(0, 1), rotZ.getMat(1, 1), rotZ.getMat(2, 1));
	this->aZ.initVectorND(3, rotZ.getMat(0, 2), rotZ.getMat(1, 2), rotZ.getMat(2, 2));

	this->aux.zeroVectorND(3);
}

void RotationMats::updateRotationMats(double theta) {

	this->theta = theta;
	this->rotZ.accessMat(0, 0, cos(theta));
	this->rotZ.accessMat(1, 0, sin(theta));
	this->rotZ.accessMat(2, 0,        0.0);

	this->rotZ.accessMat(0, 1,-sin(theta));
	this->rotZ.accessMat(1, 1, cos(theta));
	this->rotZ.accessMat(2, 1,        0.0);

	this->rotZ.accessMat(0, 2,        0.0);
	this->rotZ.accessMat(1, 2,        0.0);
	this->rotZ.accessMat(2, 2,        1.0);

	this->aX.initVectorND(3, rotZ.getMat(0, 0), rotZ.getMat(1, 0), rotZ.getMat(2, 0));
	this->aY.initVectorND(3, rotZ.getMat(0, 1), rotZ.getMat(1, 1), rotZ.getMat(2, 1));
	this->aZ.initVectorND(3, rotZ.getMat(0, 2), rotZ.getMat(1, 2), rotZ.getMat(2, 2));
}

void RotationMats::escRotationMats() {

	this->rotZ.escMat();
}

void RotationMats::rot3D(VectorND v) {

	this->aux.updateVector3D(
		(v.access(0) * this->aX.access(0)) + (v.access(1) * this->aX.access(1)) + (v.access(2) * this->aX.access(2)), 
		(v.access(0) * this->aY.access(0)) + (v.access(1) * this->aY.access(1)) + (v.access(2) * this->aY.access(2)), 
		(v.access(0) * this->aZ.access(0)) + (v.access(1) * this->aZ.access(1)) + (v.access(2) * this->aZ.access(2))
	);
} 

VectorND RotationMats::getAux() {

	return this->aux;
}