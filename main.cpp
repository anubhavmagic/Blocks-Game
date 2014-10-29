#include <GL/gl.h>
#include <GL/glut.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include <C:\Program Files (x86)\CodeBlocks\MinGW\include\SOIL\src\SOIL.h>
#include <C:\Users\anubhavmagic\Documents\cs360\Bakchodi\lib3ds\src\lib3ds.h>
// C:\Users\anubhavmagic\Documents\cs360\Bakchodi\lib3ds\src
#include <fstream>
#include <iostream>
#include <vector>
#include "controls.h"
#include "display.h"
#include "fonts.h"
#include "start_screen.h"
#include "plane.h"

int mainWindow;
int h, w;
int start_flag = 1;
GLuint texture[1];

bool blend;
bool bp;

int LoadGLTextures()                                    // Load Bitmaps And Convert To Textures
{
    /* load an image file directly as a new OpenGL texture */
    texture[0] = SOIL_load_OGL_texture
        (
        "try.bmp",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
        );
    printf("%d",texture[0]);
    if(texture[0] == 0)
        return false;


    // Typical Texture Generation Using Data From The Bitmap
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 2, 2, 0, GL_RGB, GL_FLOAT, texture[0]);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    //float color[] = { 1.0f, 0.0f, 0.0f, 1.0f };
    //glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, color);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

//    float pixels[] = {
//    0.0f, 0.0f, 0.0f,   1.0f, 1.0f, 1.0f,
//    1.0f, 1.0f, 1.0f,   0.0f, 0.0f, 0.0f};
    return true;                                        // Return Success
}



void drawObstacle(float xx, float yy, float zz)
{
    glTranslatef(xx, yy, zz);
    glEnable(GL_BLEND);     // Turn Blending On
    glDisable(GL_DEPTH_TEST);
    glColorMaterial( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE ) ;
    glEnable(GL_COLOR_MATERIAL);
    glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads

        //Back face
      glColor4f(1.0f, 1.0f, 0.0f, 0.2f);     // Yellow
      glVertex3f( 1.0f, -1.0f, -0.1f);
      glVertex3f(-1.0f, -1.0f, -0.1f);
      glVertex3f(-1.0f,  1.0f, -0.1f);
      glVertex3f( 1.0f,  1.0f, -0.1f);

        // Bottom face (y = -1.0f)
      glColor4f(1.0f, 0.5f, 0.0f, 0.2f);     // Orange
      glVertex3f( 1.0f, -1.0f,  1.0f);
      glVertex3f(-1.0f, -1.0f,  1.0f);
      glVertex3f(-1.0f, -1.0f, -1.0f);
      glVertex3f( 1.0f, -1.0f, -1.0f);

        //Top face
      glColor4f(0.0f, 1.0f, 0.0f, 0.2f);     // Green
      glVertex3f(1.0f, 1.0f, 1.0);
      glVertex3f(1.0f, 1.0f, 1.0);
      glVertex3f(1.0f, 1.0f, 1.0);
      glVertex3f(1.0f, 1.0f, 1.0);

      // Front face  (z = 1.0f)
      glColor4f(1.0f, 0.0f, 0.0f, 0.2f);     // Red
      glVertex3f( 1.0f,  1.0f, 1.0f);
      glVertex3f(-1.0f,  1.0f, 1.0f);
      glVertex3f(-1.0f, -1.0f, 1.0f);
      glVertex3f( 1.0f, -1.0f, 1.0f);

      // Left face (x = -1.0f)
      glColor4f(0.0f, 0.0f, 1.0f, 0.2f);     // Blue
      glVertex3f(-1.0f,  1.0f,  1.0f);
      glVertex3f(-1.0f,  1.0f, -1.0f);
      glVertex3f(-1.0f, -1.0f, -1.0f);
      glVertex3f(-1.0f, -1.0f,  1.0f);

      // Right face (x = 1.0f)
      glColor4f(1.0f, 0.0f, 1.0f, 0.2f);     // Magenta
      glVertex3f(1.0f,  1.0f, -1.0f);
      glVertex3f(1.0f,  1.0f,  1.0f);
      glVertex3f(1.0f, -1.0f,  1.0f);
      glVertex3f(1.0f, -1.0f, -1.0f);
    glEnd();  // End of drawing color-cube

    glDisable(GL_COLOR_MATERIAL);
    glDisable(GL_BLEND);        // Turn Blending Off
    glEnable(GL_DEPTH_TEST);
}
/*
void drawPlane()
{
    glTranslatef(plane_x, plane_y, plane_z);  // Move right and into the screen

    glColorMaterial( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE ) ;
    glEnable(GL_COLOR_MATERIAL);
    glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
      // Top face (y = 1.0f)
      // Define vertices in counter-clockwise (CCW) order with normal pointing out
      glColor3f(0.0f, 1.0f, 0.0f);     // Green
      glVertex3f( 1.0f, 1.0f, -1.0f);
      glVertex3f(-1.0f, 1.0f, -1.0f);
      glVertex3f(-1.0f, 1.0f,  1.0f);
      glVertex3f( 1.0f, 1.0f,  1.0f);

      // Bottom face (y = -1.0f)
      glColor3f(1.0f, 0.5f, 0.0f);     // Orange
      glVertex3f( 1.0f, -1.0f,  1.0f);
      glVertex3f(-1.0f, -1.0f,  1.0f);
      glVertex3f(-1.0f, -1.0f, -1.0f);
      glVertex3f( 1.0f, -1.0f, -1.0f);

      // Front face  (z = 1.0f)
      glColor3f(1.0f, 0.0f, 0.0f);     // Red
      glVertex3f( 1.0f,  1.0f, 1.0f);
      glVertex3f(-1.0f,  1.0f, 1.0f);
      glVertex3f(-1.0f, -1.0f, 1.0f);
      glVertex3f( 1.0f, -1.0f, 1.0f);

      // Back face (z = -1.0f)
      glColor3f(1.0f, 1.0f, 0.0f);     // Yellow
      glVertex3f( 1.0f, -1.0f, -1.0f);
      glVertex3f(-1.0f, -1.0f, -1.0f);
      glVertex3f(-1.0f,  1.0f, -1.0f);
      glVertex3f( 1.0f,  1.0f, -1.0f);

      // Left face (x = -1.0f)
      glColor3f(0.0f, 0.0f, 1.0f);     // Blue
      glVertex3f(-1.0f,  1.0f,  1.0f);
      glVertex3f(-1.0f,  1.0f, -1.0f);
      glVertex3f(-1.0f, -1.0f, -1.0f);
      glVertex3f(-1.0f, -1.0f,  1.0f);

      // Right face (x = 1.0f)
      glColor3f(1.0f, 0.0f, 0.5f);     // Magenta
      glVertex3f(1.0f,  1.0f, -1.0f);
      glVertex3f(1.0f,  1.0f,  1.0f);
      glVertex3f(1.0f, -1.0f,  1.0f);
      glVertex3f(1.0f, -1.0f, -1.0f);
    glEnd();  // End of drawing color-cube
    glColor3f(0.0f, 0.9f, 0.9f);
    glDisable(GL_COLOR_MATERIAL);
}
*/
void drawTunnel()
{
    glEnable(GL_TEXTURE_2D);
    glColor3f(0.0f, 1.0f, 1.0f);

  glBegin(GL_QUADS);
      glTexCoord2f(0.0f,0.0f);
	  glVertex3f(-5.75f, -4.1f, tunnel_z);
	    glTexCoord2f(1.0f,0.0f);
    glVertex3f(-5.75f, -4.1f, -120.0f+ (tunnel_z));
        glTexCoord2f(1.0f,1.0f);
		glVertex3f(-5.75f, 4.1f, -120.0f + (tunnel_z));
        glTexCoord2f(0.0f,1.0f);
		glVertex3f(-5.75f, 4.1f, tunnel_z);
	glEnd();

    glColor3f(0.7f, 0.7f, 0.9f);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f,0.0f);
		glVertex3f(-5.75f, 4.1f,tunnel_z);
		glTexCoord2f(1.0f,0.0f);
        glVertex3f(-5.75f, 4.1f, (tunnel_z)-120.0f);
        glTexCoord2f(1.0f,1.0f);
		glVertex3f(5.75f, 4.1f, (tunnel_z)-120.0f);
        glTexCoord2f(0.0f,1.0f);
		glVertex3f(5.75f, 4.1f, tunnel_z);
	glEnd();

    glColor3f(0.1f, 0.1f, 0.1f);
	glBegin(GL_QUADS);
        glTexCoord2f(0.0f,0.0f);
		glVertex3f(5.75f, 4.1f, tunnel_z);
		    glTexCoord2f(1.0f,0.0f);
    glVertex3f(5.75f, 4.1f, (tunnel_z)-120.0f);
        glTexCoord2f(1.0f,1.0f);
		glVertex3f(5.75f, -4.1f, (tunnel_z)-120.0f);
		glTexCoord2f(0.0f,1.0f);
		glVertex3f(5.75f, -4.1f, tunnel_z);
	glEnd();

glDisable(GL_TEXTURE_2D);

    glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
		glVertex3f(5.75f, -4.1f, tunnel_z);
    glVertex3f(5.75f, -4.1f, (tunnel_z)-120.0f);
		glVertex3f(-5.75f, -4.1f, (tunnel_z)-120.0f);
		glVertex3f(-5.75f, -4.1f, tunnel_z);
	glEnd();
}

void drawTunnel2()
{
    glEnable(GL_TEXTURE_2D);
    glColor3f(0.0f, 1.0f, 1.0f);

  glBegin(GL_QUADS);
      glTexCoord2f(0.0f,0.0f);
    glVertex3f(-5.75f, -4.1f, tunnel_z2);
      glTexCoord2f(1.0f,0.0f);
    glVertex3f(-5.75f, -4.1f, -120.0f+ (tunnel_z2));
        glTexCoord2f(1.0f,1.0f);
    glVertex3f(-5.75f, 4.1f, -120.0f + (tunnel_z2));
        glTexCoord2f(0.0f,1.0f);
    glVertex3f(-5.75f, 4.1f, tunnel_z2);
  glEnd();

    glColor3f(0.7f, 0.7f, 0.9f);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f,0.0f);
    glVertex3f(-5.75f, 4.1f,tunnel_z2);
    glTexCoord2f(1.0f,0.0f);
        glVertex3f(-5.75f, 4.1f, (tunnel_z2)-120.0f);
        glTexCoord2f(1.0f,1.0f);
    glVertex3f(5.75f, 4.1f, (tunnel_z2)-120.0f);
        glTexCoord2f(0.0f,1.0f);
    glVertex3f(5.75f, 4.1f, tunnel_z2);
  glEnd();

    glColor3f(0.1f, 0.1f, 0.1f);
  glBegin(GL_QUADS);
        glTexCoord2f(0.0f,0.0f);
    glVertex3f(5.75f, 4.1f, tunnel_z2);
        glTexCoord2f(1.0f,0.0f);
    glVertex3f(5.75f, 4.1f, (tunnel_z2)-120.0f);
        glTexCoord2f(1.0f,1.0f);
    glVertex3f(5.75f, -4.1f, (tunnel_z2)-120.0f);
    glTexCoord2f(0.0f,1.0f);
    glVertex3f(5.75f, -4.1f, tunnel_z2);
  glEnd();

glDisable(GL_TEXTURE_2D);

    glColor3f(0.0f, 0.0f, 0.0f);
  glBegin(GL_QUADS);
    glVertex3f(5.75f, -4.1f, tunnel_z2);
    glVertex3f(5.75f, -4.1f, (tunnel_z2)-120.0f);
    glVertex3f(-5.75f, -4.1f, (tunnel_z2)-120.0f);
    glVertex3f(-5.75f, -4.1f, tunnel_z2);
  glEnd();
}

void init()
{
    if (!LoadGLTextures())                          // Jump To Texture Loading Routine ( NEW )
    {
        printf("Texture loading failed!\n");                          // If Texture Didn't Load Return FALSE ( NEW )
    }

    // Clipping view volume
    // glFrustum(-20.0f,20.f,-20.f,20.f,0.0f,-0.5f);

    glEnable(GL_TEXTURE_2D);

    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections

    //Handle Keyboard
    glutKeyboardFunc(normalKeyboard);
    glutSpecialFunc(specialKeyboard);

    //Handle Mouse
    glutMouseFunc(mouseClick);
    //glutMotionFunc(mouseActive);
    //glutPassiveMotionFunc(mousePassive);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
    glShadeModel(GL_SMOOTH);

   GLfloat mat_specular[] = { 0.50, 0.30, 0.70, 1.0 };
   GLfloat mat_ambient[] = { 0.20, 0.20, 0.20, 1.0 };
   GLfloat mat_shininess[] = { 50.0 };
   GLfloat light_ambient[] = { 0.50, 0.50, 0.50, 1.0 };
   GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
   GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
   GLfloat light_position[] = { 5.0, 2.0, 0.0, 1.0 };
   GLfloat spot_direction[] = { 0.0, -0.1, -3.0 };

   //glClearColor(0.0, 0.0, 0.0, 0.0);

   GLfloat light1_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
   GLfloat light1_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
   GLfloat light1_specular[] = { 1.0, 1.0, 1.0, 1.0 };
   GLfloat light1_position[] = { -0.50, -0.5, -1.0, 1.0 };


   GLfloat lmodel_ambient[] = { 0.3, 0.3, 0.3, 1.0 };
   glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);

   glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);



   glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
   glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
   glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
   glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
   glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
   glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
   glLightfv(GL_LIGHT0, GL_POSITION, light_position);

   glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
   glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
   glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
   glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
   glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 45.0);
   glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction);
   glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 2.0);


   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glEnable(GL_LIGHT1);

   glBlendFunc(GL_SRC_ALPHA,GL_ONE);

   // To remove mouse pointer from screen
   

}

int main(int argc, char **argv)
{
    //Initialize GLUT window
  // Lib3dsFile* myfile = lib3ds_file_load("SR71A.3DS");
  // Lib3dsMesh* miObjeto = lib3ds_file_mesh_by_name(myfile, "airplane");

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_RGBA | GLUT_ALPHA | GLUT_DOUBLE);
    glutInitWindowPosition(200,100);
    glutInitWindowSize(700,500);
    mainWindow = glutCreateWindow("Ho Lee Fuk");

    //Register Display callbacks for Main Window
    glutDisplayFunc(renderDisplayStart);
    glutIdleFunc(renderDisplayStart);
    glutReshapeFunc(reshapeWindow);
    init();

    //Add initial sound
    //PlaySound("starwars.wav", NULL, SND_ASYNC|SND_FILENAME|SND_LOOP);

    // Gets mouse location
    
    //Enter main control loop
    glutMainLoop();

    return 1;
}
