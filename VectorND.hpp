#include <stdarg.h>

#ifndef VECTORND_H
#define VECTORND_H

#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

class VectorND {
    private:
        
        int n;
        double * A;
        double norma;

    public:
        
        void initVectorND(int, ...);
        void initVectorNDType2(int n);
        int dim();
        double norm();
        void zeroVectorND(int);
        void escVectorND();
        int digitCounter(double);
        void updateVector3D(double x, double y, double z);
        void updateVector3DP(VectorND p);
        double access(int i);
        void AddVector3D(VectorND b);
        void SumVector3D(VectorND b, VectorND c);
        void MinusVector3D(VectorND b);
        void SubVector3D(VectorND b, VectorND c);

        void subVectorND(VectorND a, VectorND b);
        void Cross3D(VectorND b, VectorND C);
};

class Vector3D: public VectorND {

    int n;
    double * A;
    double norma;
}; 

#endif
