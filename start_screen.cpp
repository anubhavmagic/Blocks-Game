#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include "controls.h"
#include "main.h"
#include "fonts.h"
#include "display.h"
#include "plane.h"

void drawStart(float zz)
{
    glColor3f(0.9f, 0.9f, 0.9f);

    glBegin(GL_POLYGON);
		glVertex3f(0.0f, -1.0f, zz);
        glVertex3f(1.0f, -1.0f, zz);
		glVertex3f(1.5f, -0.5f, zz);
		glVertex3f(1.5f, 0.5f, zz);
		glVertex3f(1.0f, 1.0f, zz);
        glVertex3f(-1.0f, 1.0f, zz);
		glVertex3f(-1.5f, 0.5f, zz);
		glVertex3f(-1.5f, -0.5f, zz);
		glVertex3f(-1.0f, -1.0f, zz);
        glVertex3f(0.0f, -1.0f, zz);

	glEnd();

    setOrthographicProjection();
	renderBitmapString(-1.0f, 0.0f, 0.5f,fontBitmap,(char *)"START");
	restorePerspectiveProjection();
}
void renderDisplayStart(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(	0.0f, 0.0f, 10.0f,
			0.0f, 0.0f,  0.0f,
			0.0f, 1.0f,  0.0f);

    drawStart(0.0f);
    setOrthographicProjection();
    glPushMatrix();
    glLoadIdentity();
    glColor3f(0.0f, 0.0f, 1.0f);
    renderBitmapString(315,250,1,fontBitmap,(char *)"START");
    glPopMatrix();
    restorePerspectiveProjection();
    glutSwapBuffers();
}
