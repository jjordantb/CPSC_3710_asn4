#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <math.h>
#include <iostream>

int Window_Width = 600;
int Window_Height = 400;

float ufoOneRot = 0;

static void PrintString(void *font, char *str)
{
   int i,len=strlen(str);

   for(i=0;i < len; i++)
      glutBitmapCharacter(font,*str++);
}

/*
  Because of accuracy size must divide 360 evenly
*/
void ufo(int size) {
  for (size_t i = 0; i < size; i++) {
    float step = ((360 / size) * M_PI) / 180;
    float angle = step * i;
    float x = 0.5;
    float z = x * tan((((360 / size) / 2) * M_PI) / 180);
    float zPrime = z * cos(angle) - x * sin(angle);
    float xPrime = z * sin(angle) + x * cos(angle);
    float zPrimeNot = z * cos(angle + step) - x * sin(angle + step);
    float xPrimeNot = z * sin(angle + step) + x * cos(angle + step);
    glBegin(GL_TRIANGLES);
      glColor3f(1, 1, 1);
      //Bottom
      glVertex3f(0, -0.1, 0);
      glVertex3f(xPrime, 0, zPrime);
      glVertex3f(xPrimeNot, 0, zPrimeNot);
      //Top
      glVertex3f(0, 0.1, 0);
      glVertex3f(xPrime, 0, zPrime) ;
      glVertex3f(xPrimeNot, 0, zPrimeNot);
    glEnd();
  }
}

void ncp(float size) {
  glBegin(GL_QUADS);
    glColor3f(0.5, 0, 0);

    glVertex3f(0, 0, 0);
    glVertex3f(size, 0, 0);
    glVertex3f(size, 0, -size);
    glVertex3f(0, 0, -size);

    glVertex3f(0.0f, 0.0f, -size);
    glVertex3f(size, 0.0f, -size);
    glVertex3f(size, size / 2, -size);
    glVertex3f(0.0f, size / 2, -size);

    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(size, 0.0f, 0.0f);
    glVertex3f(size, size / 2, 0.0f);
    glVertex3f(0.0f, size / 2, 0.0f);

    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, size / 2, 0.0f);
    glVertex3f(0.0f, size / 2, -size);
    glVertex3f(0.0f, 0.0f, -size);

    glVertex3f(0.0f, size / 2, 0.0f);
    glVertex3f(size / 2, size / 2, 0.0f);
    glVertex3f(size / 2, size / 2, -size);
    glVertex3f(0.0f, size / 2, -size);

    glVertex3f(size, 0.0f, 0.0f);
    glVertex3f(size, size, 0.0f);
    glVertex3f(size, size, -size);
    glVertex3f(size, 0.0f, -size);

    glVertex3f(size / 2, size / 2, -size);
    glVertex3f(size, size / 2, -size);
    glVertex3f(size, size, -size);
    glVertex3f(size / 2, size, -size);

    glVertex3f(size / 2, size / 2, 0);
    glVertex3f(size, size / 2, 0);
    glVertex3f(size, size, 0);
    glVertex3f(size / 2, size, 0);

    glVertex3f(size / 2, size, 0);
    glVertex3f(size, size, 0);
    glVertex3f(size, size, -size);
    glVertex3f(size / 2, size, -size);

    glVertex3f(size / 2, size / 2, 0.0f);
    glVertex3f(size / 2, size, 0.0f);
    glVertex3f(size / 2, size, -size);
    glVertex3f(size / 2, size / 2, -size);

    glVertex3f(0, size / 2, 0);
    glVertex3f(size / 2, size / 2, 0);
    glVertex3f(size / 2, size / 2, -size);
    glVertex3f(0, size / 2, -size);
  glEnd();
}

void CallBackRenderScene(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  gluLookAt(-10, 10, 10, 0, 0, 0, 0, 1, 0);

  glPushMatrix();
  glRotatef(ufoOneRot, 0, 1, 0);
  glTranslatef(2, 3, 0);
  ufo(10);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(-2.0, 0, 2.0);
  ncp(0.8);
  glTranslatef(0, 0, -2.0);
  ncp(1.5);
  glTranslatef(4.0, 0, 2.0);
  ncp(1.0);
  glPopMatrix();

  glutSwapBuffers();

  ufoOneRot += 2;
}


void CallBackKeyPressed(unsigned char key, int x, int y) {

}

void CallBackResizeScene(int Width, int Height) {
   if (Height == 0)
      Height = 1;

   glViewport(0, 0, Width, Height);

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,100.0f);

   glMatrixMode(GL_MODELVIEW);

   Window_Width  = Width;
   Window_Height = Height;
}

int init(int Width, int Height) {
  GLfloat mat_diffuse[] = { 1, 1, 1, 1 };
  GLfloat mat_shininess[] = { 50.0 };
  GLfloat light_position[] = { 0.0, 3.0, 0.0, 0.0 };

  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);

  glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_DEPTH_TEST);

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable( GL_BLEND );
  glClearColor(0.1f, 0.1f, 0.1f, 0.0f);

  glClearDepth(1.0);

  glEnable(GL_CULL_FACE);
  glShadeModel(GL_SMOOTH);
  glDepthFunc(GL_LESS);
  glDepthMask(GL_TRUE);
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

  CallBackResizeScene(Width,Height);
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowSize(Window_Width, Window_Height);
  glutCreateWindow("UFO");

  glutDisplayFunc(&CallBackRenderScene);
  glutIdleFunc(&CallBackRenderScene);
  glutReshapeFunc(&CallBackResizeScene);
  glutKeyboardFunc(&CallBackKeyPressed);

  init(Window_Width, Window_Height);

  glutMainLoop();
  return 1;
}
