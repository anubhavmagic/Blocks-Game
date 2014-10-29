#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

float angle = 45.0f;
float red = 1.0f;
float green = 1.0f;
float blue = 1.0f;

float angle1 = 0.0f;
float lx = 0.0f, lz = -1.0f;
float x = 0.0f, z = 5.0f;

// the key states. These variables will be zero
//when no key is being presses
float deltaAngle = 0.0f;
float deltaMove = 0;

void snowman()
{
    glColor3f(red,green,blue);

    //Draw BODY
    glTranslatef(0.0f,0.75f,0.0f);
    glutSolidSphere(0.75f,50,50);

    //Draw HEAD
    glTranslatef(0.0f,1.0f,0.0f);
    glutSolidSphere(0.25f,20,20);

    //Draw EYES
    glPushMatrix();
    glColor3f(0.0f,0.0f,0.0f);
    glTranslatef(0.05f,0.10f,0.18f);
    glutSolidSphere(0.05f,10,10);
    glTranslatef(-0.1f, 0.0f, 0.0f);
	glutSolidSphere(0.05f,10,10);
	glPopMatrix();

	// Draw NOSE
	glColor3f(1.0f, 0.5f , 0.5f);
	glutSolidCone(0.08f,0.5f,10,2);

}

void mouse(int button, int state, int x, int y)
{

}

void normalKeyboard(unsigned char key, int x, int y)
{
    if(key == 27)
    {
        exit(0);
    }
    else if (key == 49)
    {
        red = 1.0;
		green = 0.0;
		blue = 0.0;
    }
    else if (key == 50)
    {
        red = 0.0;
		green = 1.0;
		blue = 0.0;
    }
    else if (key == 51)
    {
        red = 0.0;
        green = 0.0;
		blue = 1.0;
    }
    else if (key == 52)
    {
        int mod = glutGetModifiers();
        if (mod == GLUT_ACTIVE_ALT)                     //Only ALT is working
        {
            red = 0.0;
            green = 0.0;
            blue = 0.0;
        }
        else
        {
            red = 0.5;
            green = 0.5;
            blue = 0.5;
        }
    }
}

void specialKeyboard(int key, int x, int y)
{
    float fraction = 0.2f;
    switch(key)
    {
    //case GLUT_KEY_F1:
        //Code for opening HELP menu
    //case GLUT_KEY_F2:
        //Code for GAME refresh
    case GLUT_KEY_DOWN:
        //Code to move DOWN
        x -= lx*fraction;
        z -= lz*fraction;
        break;
    case GLUT_KEY_UP:
        //Code to move UPWN
        x += lx*fraction;
        z += lz*fraction;
        break;
    case GLUT_KEY_LEFT:
        //Code to move LEFT
        angle1 -= 0.1f;
        lx = sin(angle1);
        lz = -cos(angle1);
        break;
    case GLUT_KEY_RIGHT:
        //Code to move RIGHT
        angle1 += 0.1f;
        lx = sin(angle1);
        lz = -cos(angle1);
        break;
    }
}

void pressKey(int key, int x, int y)
{
    switch(key)
    {
        case GLUT_KEY_DOWN: deltaMove = -0.5f; break;
        case GLUT_KEY_UP: deltaMove = 0.5f; break;
        case GLUT_KEY_LEFT: deltaAngle = -0.01f; break;
        case GLUT_KEY_RIGHT: deltaAngle = 0.01f; break;
    }
}

void releaseKey(int key, int x, int y)
{
    switch(key)
    {
        case GLUT_KEY_DOWN:
        case GLUT_KEY_UP: deltaMove = 0; break;
        case GLUT_KEY_LEFT:
        case GLUT_KEY_RIGHT: deltaAngle = 0.0f; break;
    }
}

void computePos(float deltaMove)
{
    x += deltaMove*lx*0.1f;
    z += deltaMove*lz*0.1f;
}

void computeDir(float deltaAngle)
{
    angle1 += deltaAngle;
    lx = sin(angle1);
    lz = -cos(angle1);
}

void reshape(int w, int h)
{
    if(h==0) h=1;       //Prevent a divide by zero if window's height is too small

    float ratio = 1.0*w/h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glViewport(0,0,w,h);

    gluPerspective(45,ratio,1,1000);        //Set the proper perspective

    glMatrixMode(GL_MODELVIEW);
}

void renderScene(void)
{
    if (deltaMove)
        computePos(deltaMove);
    if (deltaAngle)
        computeDir(deltaAngle);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Reset Transformations
    glLoadIdentity();

    //Set the camera
    gluLookAt(	x, 1.0f, z,
                x+lx, 1.0f,  z+lz,
                0.0f, 1.0f,  0.0f);
	//glRotatef(angle, 0.0, 0.0, 1.0);
	//Draw GROUND
	glColor3f(0.9f,0.9f,0.9f);
    glBegin(GL_QUADS);
		glVertex3f(-100.0f, 0.0f, -100.0f);
		glVertex3f(-100.0f, 0.0f,  100.0f);
		glVertex3f( 100.0f, 0.0f,  100.0f);
		glVertex3f( 100.0f, 0.0f, -100.0f);
	glEnd();

	//angle+=0.10f;
    //Draw 36 Snowmen
    for(int i=-3;i<3;i++)
    {
        for(int j=-3;j<3;j++)
        {
            glPushMatrix();
            glTranslatef(i*10.0,0,j*10.0);
            snowman();
            glPopMatrix();
        }
    }

    glutSwapBuffers();
}
int main(int argc, char **argv)
{
    //Initialize and create GLUT window
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_ALPHA);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(700,600);
    glutCreateWindow("Game of Life");

    //Register Callbacks
    glutDisplayFunc(renderScene);
    glutIdleFunc(renderScene);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(normalKeyboard);
    glutSpecialFunc(specialKeyboard);

    glutIgnoreKeyRepeat(1);
    glutSpecialUpFunc(releaseKey);


    glutMouseFunc(mouse);
    glEnable(GL_DEPTH_TEST);

    //GLUT event processing loop
    glutMainLoop();
    return 1;
}
