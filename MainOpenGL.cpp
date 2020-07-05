#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include "VectorND.hpp"
#include "matrix.hpp"
#include "geometry.hpp"

//////////////////////////////////////
//                                  //
//                                  //
//        VARIABLES GLOBALES        //
//                                  //
//                                  //
//////////////////////////////////////

/*variables*/ 
int ciclo = 0;
int cicloSegund = 0;
int color = 0;
double count = 0.0;
double rotSpeed = 0.0;
int iter = 5;

/*Definimos Vectores que nos pueden ayudar a generar el espacio*/
VectorND center, I, J, K, minusI, minusJ, minusK;

/*Systema de rotacion para vectores*/
RotationMats U;

/*facets*/
FacetOpenGL facet, facet0, facet1, facet2;

/*Funciones para dibujar sin pensar en OpenGL*/
void Setup();
void Draw();
void updateProcessingProto();

void ProcessingProto();

//////////////////////////////////////
//                                  //
//                                  //
//        Processing Prototype      //
//                                  //
//                                  //
//////////////////////////////////////

/*Here we build our memory space and filled it with data using initObject methods corresponding to each class.*/
/*initObjects methods are functions that should build memory space and fill it with data*/


///////////////////     SETUP       ///////////////////////
void Setup() {

  if (ciclo == 0) {

          printf("\n\n\n                  ---> Setup ---> \n\n\nCenter of Vector Space := ");
          center.zeroVectorND(3);
          I.initVectorND(3, 1.0, 0.0, 0.0);
          J.initVectorND(3, 0.0, 1.0, 0.0);
          K.initVectorND(3, 0.0, 0.0, 1.0); 
          minusI.initVectorND(3,-1.0, 0.0, 0.0);
          minusJ.initVectorND(3, 0.0,-1.0, 0.0);
          minusK.initVectorND(3, 0.0, 0.0,-1.0); 
          center.escVectorND();
      
          U.initRotationMats(count);
      
          printf("\nInit facet's-----");
          facet.initFacetOpenGL(I, J, K);
          facet0.initFacetOpenGL(J, minusI, K);
          facet1.initFacetOpenGL(minusI, minusJ, K);
          facet2.initFacetOpenGL(minusJ, I, K);
  }
}

//////////////////    UPDATE AUXILIARY FUNCTION ///////////////////

/*In this function we call any method that updates an object in a class.*/
/*Our goal is to define our memory space with initial values.*/
/*Having a memory space filled with initial values we are now able to update these initial values.*/

void updateProcessingProto() {

    if (ciclo > 0) {

          /*For example here we are updating our matrix rotation system.*/
          U.updateRotationMats(count);

          /*We update the vector K in order to create an ocilation efect.*/
          K.updateVector3D(0.0, 0.0, 1.5 * cos(count));

          /*Udate the ocilation afect onto the semi-Octahedron by updating the facet with respect to K.*/
          facet.updateFacetOpenGL(I, J, K);
          facet0.updateFacetOpenGL(J, minusI, K);
          facet1.updateFacetOpenGL(minusI, minusJ, K);
          facet2.updateFacetOpenGL(minusJ, I, K);
    }
}

///////////////////     DRAW       ///////////////////////

/*Everything is made up of triangles and each class of geometrical objects have triangle drawing methods.*/
void Draw() {

  if (ciclo > 0) {
    /*Draw Here*/
          
          facet.renderFacetOpenGL(0, U);
          facet0.renderFacetOpenGL(1, U);
          facet1.renderFacetOpenGL(2, U);
          facet2.renderFacetOpenGL(3, U);
  }

}

void ProcessingProto() {

  Setup();
  updateProcessingProto();
  Draw();
}

/**/
/**/
/**/
/**/
/**/
/**/
/**/
/**/
/**/
/**/
/**/
/**/
/**/
/**/
/**/
/**/
/**/
/**/
/**/
/**/
/**/
/**/
/**/
/**/
/**/
/**/
/**/
/**/
/**/
/**/
/**/
/**/
/**/
/**/
/**/
/**/
/**/
/**/
/**/

//////////////////////////////////////
//                                  //
//                                  //
//       OPENGL AS BACKGROUND       //
//                                  //
//                                  //
//////////////////////////////////////

/*Posición y color de luz*/
GLfloat light_diffuse[] = {1.0, 1.0, 1.0, 1.0};
GLfloat light_position[] = {1.0, 1.0, 0.25, 0.0};

/*Funciones de OpenGL*/
void display(void);
void init(double theta);
void TimerFunction(int value);
void keyboard(unsigned char key, int x, int y);
void ProcessMenu(int value);

int main(int argc, char **argv)
{
  
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(1300, 1300);
  glutCreateWindow(" ------- Fractals ------- ");
  ProcessMenu(1);
  init(count);

  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  glutTimerFunc(20, TimerFunction, 1);

  glutMainLoop();
  return 0;             /* ANSI C requires main to return int. */
}

void display(void) {
  
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(1.0, 1.0, 1.0, 1.0);
  ProcessingProto();
  glutSwapBuffers();
}

void init(double theta)
{
  /* Setup data. */
  GLfloat ambientLight[] = { 0.3f, 0.3f, 0.3f, 1.0f };
  GLfloat diffuseLight[] = { 0.7f, 0.7f, 0.7f, 1.0f };
  GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f};
  GLfloat specref[] = { 1.0f, 1.0f, 1.0f, 1.0f };

  /* Enable a single OpenGL light. */
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHTING);

  /* Use depth buffering for hidden surface elimination. */
  glEnable(GL_DEPTH_TEST);
  glFrontFace(GL_CCW);
  //glEnable(GL_CULL_FACE);

  /*Enable color tracking*/
  glEnable(GL_COLOR_MATERIAL);

  /* Set material properties to follow glColor values*/
  glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

  /*All materials have high shine*/
  glMaterialfv(GL_FRONT, GL_SPECULAR, specref);
  glMateriali(GL_FRONT, GL_SHININESS, 128);

  /* Setup the view of the cube. */
  glMatrixMode(GL_PROJECTION);
  gluPerspective( /* field of view in degree */ 40.0,
                              /* aspect ratio */ 1.0,
                                    /* Z near */ 0.5, 
                                    /* Z far */ 10000.0);
  glMatrixMode(GL_MODELVIEW);
  gluLookAt( 5.0, 5.0, 5.0,      /* eye is at (0,0,5) */
             0.0, 0.0, 0.0,      /* center is at (0,0,0) */
             0.0, 0.0, 1.0);      /* up is in positive Y direction */

  /* Adjust Board position to be asthetic angle. */
  //glTranslatef(0.0, 0.15, -0.0);
  glRotatef(90, 0.0, 0.0, 1.0);

  glEnable(GL_NORMALIZE);
}

void TimerFunction(int value) {

  count += 0.05;
  rotSpeed += 0.00;
  ciclo += 1;

  if (count > 2 * M_PI) count = 0;
  if (ciclo > 100) ciclo = 1;

  glutPostRedisplay();
  glutTimerFunc(20, TimerFunction, 1);
}

void keyboard(unsigned char key, int x, int y) {
  GLint params[2];

  switch (key) {

    case 'w': 
      ciclo += 1;
      break;

    case 'n': 
      cicloSegund += 1;
      break;

    case 'c': 
      color += 1;
      break;

    case 'i': 
      iter += 3;
      break;

    case 'I': 
      iter -= 1;
      break;

    case 'r': 
      rotSpeed += 0.02;
      break;

    case 'R': 
      rotSpeed -= 0.02;
      break;
  }

  glutPostRedisplay();
}

void ProcessMenu(int value) {
  switch(value) {
    case 1:
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      glEnable(GL_BLEND);
      glEnable(GL_POINT_SMOOTH);
      glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
      glEnable(GL_LINE_SMOOTH);
      glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
      glEnable(GL_POLYGON_SMOOTH);
      glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
      break;

    case 2:
      glDisable(GL_BLEND);
      glDisable(GL_LINE_SMOOTH);
      glDisable(GL_POINT_SMOOTH);
      glDisable(GL_POLYGON_SMOOTH);
      break;
    
    default:
      break;
  }

  glutPostRedisplay();
}
