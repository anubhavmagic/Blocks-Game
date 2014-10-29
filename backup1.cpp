#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
//#include <time.h>
#include <math.h>
#include <windows.h>

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
float xOrigin = -1;

#define RED 1
#define GREEN 2
#define BLUE 3
#define ORANGE 4

#define FILL 1
#define LINE 2

#define SHRINK 1
#define NORMAL 2

// Pop up menu identifiers
int fillMenu, shrinkMenu, mainMenu, colorMenu, fontMenu;
int menuFlag = 0;
// scale of snowman
float scale = 1.0f;

// default font
//void *font = GLUT_BITMAP_TIMES_ROMAN_24;

void *font = GLUT_STROKE_ROMAN;

//#define INT_GLUT_BITMAP_8_BY_13 1
//#define INT_GLUT_BITMAP_9_BY_15 2
#define INT_GLUT_BITMAP_TIMES_ROMAN_10  3
#define INT_GLUT_BITMAP_TIMES_ROMAN_24  4
#define INT_GLUT_BITMAP_HELVETICA_10  5
#define INT_GLUT_BITMAP_HELVETICA_12  6
#define INT_GLUT_BITMAP_HELVETICA_18  7

int height, width;

int frame;
long time, timebase;
char s[50];

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

void renderBitmapString(
		float x,
		float y,
		float z,
		void *font,
		char *string) {

  char *c;
  glRasterPos3f(x, y,z);
  for (c=string; *c != '\0'; c++) {
    glutBitmapCharacter(font, *c);
  }
}

void mouseClick(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON)
    {
        if (state == GLUT_UP)
        {
            angle1 += deltaAngle;
            xOrigin = -1;
        }
        else
        {
            xOrigin = x;
        }
    }
}

void mouseActive(int x, int y)
{
    if (xOrigin >= 0)
    {
        deltaAngle = (x-xOrigin)*0.001f;

        //Update Camera's direction
        lx = sin(angle1 + deltaAngle);
		lz = -cos(angle1 + deltaAngle);

    }
    /*else
    {
        deltaAngle = 0.0f;

        //Update Camera's direction
        lx = sin(angle1 + deltaAngle);
		lz = -cos(angle1 + deltaAngle);
    }*/
}

void normalKeyboard(unsigned char key, int xx, int yy)
{

	glutSetMenu(mainMenu);
	switch (key) {
		case 27:
			glutDestroyMenu(mainMenu);
			glutDestroyMenu(fillMenu);
			glutDestroyMenu(colorMenu);
			glutDestroyMenu(shrinkMenu);
			exit(0);
			break;

		case 's':
			if (!menuFlag)
			  glutChangeToSubMenu(2,"Shrink",shrinkMenu);
			break;
		case 'c':
			if (!menuFlag)
				glutChangeToSubMenu(2,"Color",colorMenu);
			break;
	}
	if (key == 27)
		exit(0);
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
        //case GLUT_KEY_LEFT: deltaAngle = -0.01f; break;
        //case GLUT_KEY_RIGHT: deltaAngle = 0.01f; break;
    }
}

void releaseKey(int key, int x, int y)
{
    switch(key)
    {
        case GLUT_KEY_DOWN:
        case GLUT_KEY_UP: deltaMove = 0; break;
        //case GLUT_KEY_LEFT:
        //case GLUT_KEY_RIGHT: deltaAngle = 0.0f; break;
    }
}

void computePos(float deltaMove)
{
    x += deltaMove*lx*0.1f;
    z += deltaMove*lz*0.1f;
}

/*void computeDir(float deltaAngle)
{
    angle1 += deltaAngle;
    lx = sin(angle1);
    lz = -cos(angle1);
}*/

void reshape(int w, int h)
{
    height = h;
    width = w;
    if(height==0) height=1;       //Prevent a divide by zero if window's height is too small

    float ratio = 1.0*width/height;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glViewport(0,0,width,height);

    gluPerspective(45,ratio,1,1000);        //Set the proper perspective

    glMatrixMode(GL_MODELVIEW);
}
void renderStrokeFontString(
		float x,
		float y,
		float z,
		void *font,
		char *string) {

	char *c;
	glPushMatrix();
	glTranslatef(x, y,z);

	for (c=string; *c != '\0'; c++) {
		glutStrokeCharacter(font, *c);
	}

	glPopMatrix();
}

void renderSpacedBitmapString(

			float x,
			float y,
			int spacing,
			void *font,
			char *string) {

  char *c;
  int x1=x;

  for (c=string; *c != '\0'; c++) {

	glRasterPos2f(x1,y);
	glutBitmapCharacter(font, *c);
	x1 = x1 + glutBitmapWidth(font,*c) + spacing;
  }
}

void renderVerticalBitmapString(

			float x,
			float y,
			int bitmapHeight,
			void *font,
			char *string) {

  char *c;
  int i;

  for (c=string,i=0; *c != '\0'; i++,c++) {

	glRasterPos2f(x, y+bitmapHeight*i);
	glutBitmapCharacter(font, *c);
  }
}

void setOrthographicProjection() {

	// switch to projection mode
	glMatrixMode(GL_PROJECTION);

	// save previous matrix which contains the
	//settings for the perspective projection
	glPushMatrix();

	// reset matrix
	glLoadIdentity();

	// set a 2D orthographic projection
	gluOrtho2D(0, width, height, 0);

	// invert the y axis, down is positive
	//glScalef(1, -1, 1);

	// mover the origin from the bottom left corner
	// to the upper left corner
	//glTranslatef(0, -h, 0);

	// switch back to modelview mode
	glMatrixMode(GL_MODELVIEW);
}

void restorePerspectiveProjection() {

	glMatrixMode(GL_PROJECTION);
	// restore previous projection matrix
	glPopMatrix();

	// get back to modelview mode
	glMatrixMode(GL_MODELVIEW);
}

void renderScene(void)
{
    if (deltaMove)
        computePos(deltaMove);
    //if (deltaAngle)
    //    computeDir(deltaAngle);

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
    char number[3];
    for(int i=-3;i<3;i++)
    {
        for(int j=-3;j<3;j++)
        {
            glPushMatrix();
            glTranslatef(i*10.0,0,j*10.0);
            snowman();
            sprintf(number,"%d",(i+3)*6+(j+3));
			renderStrokeFontString(0.0f, 0.5f, 0.0f, (void *)font ,number);

            glPopMatrix();
        }
    }
    // Code to compute frames per second
	frame++;

	time=glutGet(GLUT_ELAPSED_TIME);
	if (time - timebase > 1000) {
		sprintf(s,"Lighthouse3D - FPS:%4.2f",
			frame*1000.0/(time-timebase));
		timebase = time;
		frame = 0;
	}

        // Code to display a string (fps) with bitmap fonts
    setOrthographicProjection();

	glPushMatrix();
	glLoadIdentity();
	renderBitmapString(5,30,0,GLUT_BITMAP_HELVETICA_18,s);
	glPopMatrix();

	restorePerspectiveProjection();

    glutSwapBuffers();
}

// -----------------------------------
//             MENUS
// -----------------------------------

void processMenuStatus(int status, int x, int y) {

	if (status == GLUT_MENU_IN_USE)
		menuFlag = 1;
	else
		menuFlag = 0;
}

void processMainMenu(int option) {

	// nothing to do in here
	// all actions are for submenus
}

void processFillMenu(int option) {

	switch (option) {

		case FILL: glPolygonMode(GL_FRONT, GL_FILL); break;
		case LINE: glPolygonMode(GL_FRONT, GL_LINE); break;
	}
}

void processShrinkMenu(int option) {

	switch (option) {

		case SHRINK: scale = 0.5f; break;
		case NORMAL: scale = 1.0f; break;
	}
}

void processColorMenu(int option) {

	switch (option) {
		case RED :
			red = 1.0f;
			green = 0.0f;
			blue = 0.0f; break;
		case GREEN :
			red = 0.0f;
			green = 1.0f;
			blue = 0.0f; break;
		case BLUE :
			red = 0.0f;
			green = 0.0f;
			blue = 1.0f; break;
		case ORANGE :
			red = 1.0f;
			green = 0.5f;
			blue = 0.5f; break;
	}
}



/*void processFontMenu(int option) {

	switch (option) {
		case INT_GLUT_BITMAP_8_BY_13:
			font = GLUT_BITMAP_8_BY_13;
			break;
		case INT_GLUT_BITMAP_9_BY_15:
			font = GLUT_BITMAP_9_BY_15;
			break;
		case INT_GLUT_BITMAP_TIMES_ROMAN_10:
			font = GLUT_BITMAP_TIMES_ROMAN_10;
			break;
		case INT_GLUT_BITMAP_TIMES_ROMAN_24:
			font = GLUT_BITMAP_TIMES_ROMAN_24;
			break;
		case INT_GLUT_BITMAP_HELVETICA_10:
			font = GLUT_BITMAP_HELVETICA_10;
			break;
		case INT_GLUT_BITMAP_HELVETICA_12:
			font = GLUT_BITMAP_HELVETICA_12;
			break;
		case INT_GLUT_BITMAP_HELVETICA_18:
			font = GLUT_BITMAP_HELVETICA_18;
			break;
	}
}*/

void processFontMenu(int option) {

	switch (option) {
		case 1: font = GLUT_STROKE_ROMAN;
			break;
		case 2: font = GLUT_STROKE_MONO_ROMAN;
			break;
	}
}

void createPopupMenus() {

    fontMenu = glutCreateMenu(processFontMenu);

	//glutAddMenuEntry("BITMAP_8_BY_13 ",INT_GLUT_BITMAP_8_BY_13 );
	//glutAddMenuEntry("BITMAP_9_BY_15",INT_GLUT_BITMAP_9_BY_15 );
	//glutAddMenuEntry("BITMAP_TIMES_ROMAN_10 ",INT_GLUT_BITMAP_TIMES_ROMAN_10  );
	//glutAddMenuEntry("BITMAP_TIMES_ROMAN_24",INT_GLUT_BITMAP_TIMES_ROMAN_24  );
	//glutAddMenuEntry("BITMAP_HELVETICA_10 ",INT_GLUT_BITMAP_HELVETICA_10  );
	//glutAddMenuEntry("BITMAP_HELVETICA_12",INT_GLUT_BITMAP_HELVETICA_12  );
	//glutAddMenuEntry("BITMAP_HELVETICA_18",INT_GLUT_BITMAP_HELVETICA_18 );

	glutAddMenuEntry("STROKE_ROMAN",1 );
    glutAddMenuEntry("STROKE_MONO_ROMAN",2 );

	shrinkMenu = glutCreateMenu(processShrinkMenu);

	glutAddMenuEntry("Shrink",SHRINK);
	glutAddMenuEntry("Normal",NORMAL);

	fillMenu = glutCreateMenu(processFillMenu);

	glutAddMenuEntry("Fill",FILL);
	glutAddMenuEntry("Line",LINE);

	colorMenu = glutCreateMenu(processColorMenu);
	glutAddMenuEntry("Red",RED);
	glutAddMenuEntry("Blue",BLUE);
	glutAddMenuEntry("Green",GREEN);
	glutAddMenuEntry("Orange",ORANGE);

	mainMenu = glutCreateMenu(processMainMenu);

	glutAddSubMenu("Polygon Mode", fillMenu);
	glutAddSubMenu("Color", colorMenu);
	glutAddSubMenu("Scale", shrinkMenu);
	glutAddSubMenu("Font", fontMenu);
	// attach the menu to the right button
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	// this will allow us to know if the menu is active
	glutMenuStatusFunc(processMenuStatus);
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

    glutIgnoreKeyRepeat(0);
    glutSpecialUpFunc(releaseKey);

    glutMouseFunc(mouseClick);
    glutMotionFunc(mouseActive);
    //glutPassiveMotionFunc(mousePassive);

    // init Menus
	createPopupMenus();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    PlaySound("starwars.wav", NULL, SND_ASYNC|SND_FILENAME|SND_LOOP);

    //GLUT event processing loop
    glutMainLoop();
    return 1;
}
