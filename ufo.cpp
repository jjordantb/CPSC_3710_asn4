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

float ufoOneRot = 0, ufoTwoRot = 0;
float xMove = 0, yMove = 2;
bool vert = true, up = true, hor = false, left = true;

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
    float u[3] = {xPrime, 0 - 0.1, zPrime};
    float v[3] = {xPrimeNot, 0 - 0.1, zPrimeNot};
    float n[3] = {u[1] * v[2] - u[2] * v[1], u[2] * v[0] - u[0] * v[2], u[0] * v[1] - u[1] * v[0]};
    glBegin(GL_TRIANGLES);
      glColor3f(0, 0.6, 0.6);
      //Bottom
      glNormal3f(0, -1, 0);
      glVertex3f(0, -0.1, 0);
      glVertex3f(xPrime, 0, zPrime);
      glVertex3f(xPrimeNot, 0, zPrimeNot);
      //Top
      glNormal3f(n[0], n[1], n[2]);
      glVertex3f(0, 0.1, 0);
      glVertex3f(xPrime, 0, zPrime) ;
      glVertex3f(xPrimeNot, 0, zPrimeNot);
    glEnd();
  }
}

void ncp(float size) {
  glBegin(GL_QUADS);
    glColor3f(0.5, 0, 0);

    glNormal3f(0, -1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, -size);
    glVertex3f(size, 0, -size);
    glVertex3f(size, 0, 0);

    glNormal3f(0, 0, -1);
    glVertex3f(0.0f, 0.0f, -size);
    glVertex3f(0.0f, size / 2, -size);
    glVertex3f(size, size / 2, -size);
    glVertex3f(size, 0.0f, -size);

    glNormal3f(0, 0, 1);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(size, 0.0f, 0.0f);
    glVertex3f(size, size / 2, 0.0f);
    glVertex3f(0.0f, size / 2, 0.0f);

    glNormal3f(-1, 0, 0);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, size / 2, 0.0f);
    glVertex3f(0.0f, size / 2, -size);
    glVertex3f(0.0f, 0.0f, -size);

    glNormal3f(0, 1, 0);
    glVertex3f(0.0f, size / 2, 0.0f);
    glVertex3f(size / 2, size / 2, 0.0f);
    glVertex3f(size / 2, size / 2, -size);
    glVertex3f(0.0f, size / 2, -size);

    glNormal3f(1, 0, 0);
    glVertex3f(size, 0.0f, 0.0f);
    glVertex3f(size, size, 0.0f);
    glVertex3f(size, size, -size);
    glVertex3f(size, 0.0f, -size);

    glNormal3f(0, 0, -1);
    glVertex3f(size / 2, size / 2, -size);
    glVertex3f(size / 2, size, -size);
    glVertex3f(size, size, -size);
    glVertex3f(size, size / 2, -size);

    glNormal3f(0, 0, 1);
    glVertex3f(size / 2, size / 2, 0);
    glVertex3f(size, size / 2, 0);
    glVertex3f(size, size, 0);
    glVertex3f(size / 2, size, 0);

    glNormal3f(0, 1, 0);
    glVertex3f(size / 2, size, 0);
    glVertex3f(size, size, 0);
    glVertex3f(size, size, -size);
    glVertex3f(size / 2, size, -size);

    glNormal3f(-1, 0, 0);
    glVertex3f(size / 2, size / 2, 0.0f);
    glVertex3f(size / 2, size, 0.0f);
    glVertex3f(size / 2, size, -size);
    glVertex3f(size / 2, size / 2, -size);

    glNormal3f(0, 1, 0);
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
  glTranslatef(xMove, yMove, 3);
  ufo(10);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(-3, 1, 0);
  glRotatef(ufoOneRot, 0, 1, 0);
  glTranslatef(0, 0, 0);
  ufo(5);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(2, 5, 0);
  glRotatef(ufoTwoRot, 0, 1, 0);
  glTranslatef(0, 0, 0);
  ufo(6);
  glPopMatrix();

  glPushMatrix();
  glRotatef(ufoTwoRot, 0, 1, 0);
  glTranslatef(3, 4, 0);
  ufo(8);
  glPopMatrix();

  glPushMatrix();
  glRotatef(ufoOneRot, 0, 1, 0);
  glTranslatef(2, 3, 0);
  ufo(10);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(-2.0, 0, 2.0);
  ncp(0.8);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0, 0, -2.0);
  glRotatef(270, 1, 0, 0);
  ncp(1.5);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(4.0, 0, 2.0);
  glRotatef(90, 0, 1, 0);
  ncp(1.0);
  glPopMatrix();

  // glPushMatrix();
  // glBegin(GL_QUADS);
  //   glColor3f(0, 0.5, 0);
  //   glNormal3f(0, 0, 1);
  //   glVertex3f(0, 0, 0);
  //   glVertex3f(0, 1, 0);
  //   glVertex3f(1, 1, 0);
  //   glVertex3f(1, 0, 0);
  //
  //   glNormal3f(1, 0, 0);
  //   glVertex3f(0, 0, 0);
  //   glVertex3f(0, 0, -1);
  //   glVertex3f(0, 1, -1);
  //   glVertex3f(0, 1, 0);
  // glEnd();
  // glPopMatrix();

  glutSwapBuffers();

  ufoOneRot += 2;
  ufoTwoRot += 1;

  if (vert) {
    if (up) {
      yMove += 0.05;
      if (yMove > 4) {
        up = false;
      }
    } else {
      yMove -= 0.05;
      if (yMove < 1) {
        up = true;
      }
    }
  }

  if (hor) {
    if (left) {
      xMove -= 0.05;
      if (xMove < -2) {
        left = false;
      }
    } else {
      xMove += 0.05;
      if (xMove > 2) {
        left = true;
      }
    }
  }

}


void CallBackKeyPressed(unsigned char key, int x, int y) {
  switch (key) {
    case 'u':
      vert = !vert;
    break;
    case 'f':
      hor = !hor;
    break;
  }
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
  GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
  GLfloat mat_shininess[] = { 50.0 };
  GLfloat light_position[] = { -2, 2, 2, 0.0 };

  GLfloat mat_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };

  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  glLightfv(GL_LIGHT1, GL_POSITION, light_position);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, mat_diffuse);

  glEnable(GL_LIGHTING);
  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHT1);
  glEnable(GL_DEPTH_TEST);

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable( GL_BLEND );
  glClearColor(0.1f, 0.1f, 0.1f, 0.0f);

  glClearDepth(1.0);

  glFrontFace(GL_CCW);
  glCullFace(GL_BACK);
  glEnable(GL_CULL_FACE);
  glShadeModel(GL_SMOOTH);

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
