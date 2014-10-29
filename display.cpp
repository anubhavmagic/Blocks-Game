#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include <C:\Program Files (x86)\CodeBlocks\MinGW\include\SOIL\src\SOIL.h>
#include <C:\Users\anubhavmagic\Documents\cs360\Bakchodi\lib3ds\src\lib3ds.h>
#include <fstream>
#include <iostream>
#include <vector>
#include "controls.h"
#include "main.h"
#include "fonts.h"
#include "start_screen.h"
#include "plane.h"

float angle = 0.0f;
float plane_x = 0.0f;
float plane_y = 0.0f;
float plane_z = -13.2f;
float plane_x2 = 0.0f;
float plane_y2 = 0.0f;
float plane_z2 = -13.0f;
// float runspeed = 0.01f;
float speed = 0.01f;
// float increase = 0.01f;
float xx = (float)(rand()%5);
float yy = (float)(rand()%4);
float zz = -1.0*((float)(rand()%10));

float tunnel_z = 0.0f,tunnel_z2=-120.0f;

int frame = 0;
char s[60];
long time = 0, timebase;
int score = 1;
//#define INFINITY    100
struct Point3f
{
    GLfloat x, y, z;
};

struct Plane
{
    GLfloat a, b, c, d;
};

// Structure Describing An Object's Face
struct Face
{
    int vertexIndices[3];           // Index Of Each Vertex Within An Object That Makes Up The Triangle Of This Face
    Point3f normals[3];         // Normals To Each Vertex
    Plane planeEquation;            // Equation Of A Plane That Contains This Triangle
    int neighbourIndices[3];        // Index Of Each Face That Neighbours This One Within The Object
    bool visible;               // Is The Face Visible By The Light?
};

struct ShadowedObject
{
    int nVertices;
    Point3f *pVertices;         // Will Be Dynamically Allocated

    int nFaces;
    Face *pFaces;               // Will Be Dynamically Allocated
};
void setOrthographicProjection()
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	// set a 2D orthographic projection
	gluOrtho2D(0, w, h, 0);
	// invert the y axis, down is positive
	//glScalef(1, -1, 1);
	// mover the origin from the bottom left corner
	// to the upper left corner
	//glTranslatef(0, -h, 0);
	glMatrixMode(GL_MODELVIEW);
}

void restorePerspectiveProjection()
{
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}


void reshapeWindow(int ww, int hh)
{
    w = ww;
    h = hh;
	if (h == 0)
		h = 1;

	float ratio =  w * 1.0 / h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
}
void My_mouse_routine(int x, int y)
{
    int mx,my;
    mx = x - w/2;
    my = y - h/2;
    if((((float) mx)/w)*20>4.25f)
        plane_x2 = 4.25f;
    else if((((float) mx)/w)*20<-4.25f)
        plane_x2 = -4.25f;
    else
        plane_x2 = (((float) mx)/w)*20;
    //-----------------
    if(-(((float) my)/h)*20>2.8f)
        plane_y2 = 2.8f;
    else if(-(((float) my)/h)*20<-2.8f)
        plane_y2 = -2.8f;
    else
        plane_y2 = -(((float) my)/h)*20;
// printf("x:%d y:%d \n",x,y);
}

void renderDisplay(void)
{
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Orignial camera setup
   //  gluLookAt(	0.0f, 0.0f, 0.0f,
			// 0.0f, 0.0f,  -1.0f,
			// 0.0f, 1.0f,  0.0f);

    gluLookAt(  (plane_x+plane_x2)/2, (plane_y+plane_y2)/5, 0.0f,
            (plane_x+plane_x2)/2, (plane_y+plane_y2)/5,  -1.0f,
            0.0f, 1.0f,  0.0f);

if(GetAsyncKeyState(VK_UP))
{
    if(plane_y<2.8)
    plane_y=plane_y+0.01f;
    else
    plane_y = 2.8f;
}
if(GetAsyncKeyState(VK_DOWN))
{
    if(plane_y>-2.8)
    plane_y=plane_y-0.01f;
    else
    plane_y = -2.8f;
}
if(GetAsyncKeyState(VK_LEFT))
{
    if(plane_x>-4.25)
    plane_x=plane_x-0.01f;
    else
    plane_x = -4.25f;
}
if(GetAsyncKeyState(VK_RIGHT))
{
    if(plane_x<4.25)
    plane_x=plane_x+0.01f;
    else
    plane_x = 4.25f;
}
    drawTunnel();
    drawTunnel2();

    glutPassiveMotionFunc( My_mouse_routine );

    // printf("x:%d y:%d \n",plane_x,plane_y);
    glPushMatrix();
    drawplane(plane_x2,plane_y2,plane_z2,1);
    glPopMatrix();
    glPushMatrix();
    drawplane(plane_x,plane_y,plane_z,2);
    glPopMatrix();

    if(tunnel_z >= 120.0f && tunnel_z <= 121.000f)
        tunnel_z = -120.0f+(speed*2);
    tunnel_z += speed;
    if(tunnel_z2 >= 120.0f  && tunnel_z2 <= 121.000f)
        tunnel_z2 = -120.0f+(speed*2);
    tunnel_z2 += speed;

    time++;
    if(time == 1000)
    {
        score += 1;
        speed = log(score+5)/150;
        time = 0;
    }

	//if (time - timebase > 1000) {
    sprintf(s,"Score:%4d",score);
		//timebase = time;
		//frame = 0;


    setOrthographicProjection();
    glPushMatrix();
	glLoadIdentity();
	void *font= GLUT_BITMAP_HELVETICA_18;
	glColor3f(0.0f, 0.0f, 0.0f);
	renderBitmapString(30,30,1,font,s);
	glPopMatrix();
    restorePerspectiveProjection();
    glutSwapBuffers();
    glDisable(GL_TEXTURE_2D);
}



