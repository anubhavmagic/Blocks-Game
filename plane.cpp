#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <windows.h>
#include <C:\Program Files (x86)\CodeBlocks\MinGW\include\SOIL\src\SOIL.h>
#include <C:\Users\anubhavmagic\Documents\cs360\Bakchodi\lib3ds\src\lib3ds.h>
#include "main.h"
#include "display.h"
#include "fonts.h"
#include "start_screen.h"
void drawplane(float plane_x, float plane_y, float plane_z,int num)
{
    glTranslatef(plane_x, plane_y, plane_z);  // Move right and into the screen
    glColorMaterial( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE ) ;
    glEnable(GL_COLOR_MATERIAL);
    glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
      // Top face (y = 1.0f)
      // Define vertices in counter-clockwise (CCW) order with normal pointing out
    if(num==1)
      glColor3f(0.0f, 1.0f, 0.0f);     // Green
    else if(num==2)
      glColor3f(0.0f, 0.8f, 0.0f);
      glVertex3f( 1.0f, 1.0f, -1.0f);
      glVertex3f(-1.0f, 1.0f, -1.0f);
      glVertex3f(-1.0f, 1.0f,  1.0f);
      glVertex3f( 1.0f, 1.0f,  1.0f);

      // Bottom face (y = -1.0f)
      if(num==1)
      glColor3f(1.0f, 0.5f, 0.0f);     // Orange
      else if(num==2)
      glColor3f(0.0f, 1.0f, 0.0f);

      glVertex3f( 1.0f, -1.0f,  1.0f);
      glVertex3f(-1.0f, -1.0f,  1.0f);
      glVertex3f(-1.0f, -1.0f, -1.0f);
      glVertex3f( 1.0f, -1.0f, -1.0f);

      // Front face  (z = 1.0f)
      if(num==1)
      glColor3f(1.0f, 0.0f, 0.0f);     // Red
      else if(num==2)
      glColor3f(0.0f, 0.9f, 0.0f);
      glVertex3f( 1.0f,  1.0f, 1.0f);
      glVertex3f(-1.0f,  1.0f, 1.0f);
      glVertex3f(-1.0f, -1.0f, 1.0f);
      glVertex3f( 1.0f, -1.0f, 1.0f);

      // Back face (z = -1.0f)
      if(num==1)
      glColor3f(1.0f, 1.0f, 0.0f);     // Yellow
      else if(num==2)
      glColor3f(0.0f, 0.7f, 0.0f);
      glVertex3f( 1.0f, -1.0f, -1.0f);
      glVertex3f(-1.0f, -1.0f, -1.0f);
      glVertex3f(-1.0f,  1.0f, -1.0f);
      glVertex3f( 1.0f,  1.0f, -1.0f);

      // Left face (x = -1.0f)
      if(num==1)
      glColor3f(0.0f, 0.0f, 1.0f);     // Blue
      else if(num==2)
      glColor3f(0.2f, 1.0f, 0.4f);
      glVertex3f(-1.0f,  1.0f,  1.0f);
      glVertex3f(-1.0f,  1.0f, -1.0f);
      glVertex3f(-1.0f, -1.0f, -1.0f);
      glVertex3f(-1.0f, -1.0f,  1.0f);

      // Right face (x = 1.0f)
      if(num==1)
      glColor3f(1.0f, 0.0f, 0.5f);     // Magenta
      else if(num==2)
      glColor3f(0.2f, 0.4f, 0.0f);
      glVertex3f(1.0f,  1.0f, -1.0f);
      glVertex3f(1.0f,  1.0f,  1.0f);
      glVertex3f(1.0f, -1.0f,  1.0f);
      glVertex3f(1.0f, -1.0f, -1.0f);
    glEnd();  // End of drawing color-cube
    glColor3f(0.0f, 0.9f, 0.9f);
    glDisable(GL_COLOR_MATERIAL);
}
