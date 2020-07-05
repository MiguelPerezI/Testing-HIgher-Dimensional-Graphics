#ifndef MATRIX3D_H
#define MATRIX3D_H

#include <iostream>
#include <cstdlib>
#include <cmath>
#include "VectorND.hpp"

using namespace std;

/*Al comenzar una clase primero necesitamos ver a la clase*/
/*como un espacio en la memoria que contiene objetos de un*/
/*tipo. Para una matriz se necesita almacenar informacion */
/*de sus dimensiones y hacemos esto con int m y int n. Estos*/
/*van a almacenar el tamaño de la matriz*/

/* El símbolo * (* A) se refiere a lo siguiente:*/

/*     (* A) apunta a uno o más doubles en una arreglo */
/*   * (* A) apunta a uno o más contenedores "(* A)" en un arreglo.*/
/* private significa que solamento podemos a acceder a m,n y * (* A)*/
/*dentro de la clase o por medio de un metodo fuera de ella.  */

class Matrix {
    private:
        /*Tipo de memoria*/

        int m, n;
        double * ( * A);

    public:
        /*Los metodos que se le pueden aplicar a la información*/
        /*guardada en el espacio creado por la clase Matriz.*/

        void initMat(int, int);
        int numFila();
        int numCol();
        double getMat(int, int);
        void zeroMat(int, int);
        void diagonalIgualAUno(int, int);
        void escMat();
        void accessMat(int, int, double);
        int digitCounter(double);
        void swap(int i, int j);
        void order();
        int revisaCeros();
        void rowEchelonForm();
        int doubleEqual(double, double);
        void fixRowRespectTo_i(int, int, int);
        double determinant();
};

class RotationMats {
    private:
        double theta;
        Matrix rotZ;
        VectorND aX;
        VectorND aY;
        VectorND aZ;
        VectorND aux;

    public:
        void initRotationMats(double theta);
        void updateRotationMats(double theta);
        void escRotationMats();
        void rot3D(VectorND v);
        VectorND getAux();
};

#endif
