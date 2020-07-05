#include <stdarg.h>
#include <GL/glut.h>
#include "VectorND.hpp"
#include "matrix.hpp"

#ifndef GEOMETRY
#define GEOMETRY

#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

class FacetOpenGL {
    private:
        VectorND a;
        VectorND b;
        VectorND c;
        VectorND normal;
        VectorND aux1;
        VectorND aux2;
    public:
        void updateNormal();
        void initFacetOpenGL(VectorND a, VectorND b, VectorND c);
        void renderFacetOpenGL(int mod, RotationMats U);
        void updatePoints(VectorND a, VectorND b, VectorND c);
        void updateFacetOpenGL(VectorND a, VectorND b, VectorND c);
};
#endif
