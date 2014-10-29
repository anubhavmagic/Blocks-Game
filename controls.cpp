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
#include "plane.h"
char gameModeString[40] = "1024x768";


// ************* Mouse Control **************

void mouseClick(int button, int state, int x, int y)
{
    //printf("Atleast\n");

    if(button == GLUT_LEFT_BUTTON)
    {
        //printf("Entered\n");
        if(state == GLUT_DOWN)
        {
            //printf("%d, %d\n", x, y);
            if(x>=250 && x <= 440 && y >= 190 && y <= 310 && start_flag)
            {
                //printf("%f, %f\n", x, y);
                glutDestroyWindow(mainWindow);
                start_flag = 0;
                mainWindow = glutCreateWindow("Ho Lee Fuk");
                // PlaySound("starwars.wav", NULL, SND_ASYNC|SND_FILENAME|SND_LOOP);
                //Register Display callbacks for Main Window
                glutDisplayFunc(renderDisplay);
                glutIdleFunc(renderDisplay);
                glutReshapeFunc(reshapeWindow);
                //To hide pointer.
                glutSetCursor(GLUT_CURSOR_NONE); 
                init();

            }
        }
    }
}


// ************* Keyboard control ***************

void normalKeyboard(unsigned char key, int x, int y)
{
    if(key == 27)
        exit(0);
//    if (key == 'B' && !bp)               // Is B Key Pressed And bp FALSE?
//    {
//        bp=TRUE;                // If So, bp Becomes TRUE
//        blend = !blend;             // Toggle blend TRUE / FALSE
//        if(blend)               // Is blend TRUE?
//        {
//            glEnable(GL_BLEND);     // Turn Blending On
//            glDisable(GL_DEPTH_TEST);   // Turn Depth Testing Off
//        }
//        else                    // Otherwise
//        {
//            glDisable(GL_BLEND);        // Turn Blending Off
//            glEnable(GL_DEPTH_TEST);    // Turn Depth Testing On
//        }
//    }
//    if (!key == 'B')                 // Has B Key Been Released?
//    {
//        bp=FALSE;               // If So, bp Becomes FALSE
//    }
}

void specialKeyboard(int key, int x, int y)
{
    switch(key)
    {
    case GLUT_KEY_F1:
        if (glutGameModeGet(GLUT_GAME_MODE_ACTIVE) != 0)
        {
            w = 700; h = 500;
            glutLeaveGameMode();
            glutSetWindow(mainWindow);
        }
        else
        {
            glutGameModeString("1024x768:32");
            printf("F1 pressed\n");
            if(GLUT_GAME_MODE_POSSIBLE)
            {
                glutEnterGameMode();
                sprintf(gameModeString,"1024x768:32");
                glutDisplayFunc(renderDisplay);
                glutIdleFunc(renderDisplay);
                glutReshapeFunc(reshapeWindow);
                init();
            }
            else
                glutGameModeString(gameModeString);
        }
        break;

    // case GLUT_KEY_RIGHT:
    //     if(plane_x <= 4.1f)
    //     {
    //         plane_x += 0.3f;
    //         // glutPostRedisplay();
    //     }
    //     break;
    // case GLUT_KEY_LEFT:
    //     if(plane_x >= -4.1f)
    //     {
    //         plane_x -= 0.3f;
    //     }
    //     break;
    // case GLUT_KEY_UP:
    //     if(plane_y <= 2.6f )
    //     {
    //         plane_y += 0.3f;
    //     }
    //     break;
    // case GLUT_KEY_DOWN:
    //     if(plane_y >= -2.6f)
    //     {
    //         plane_y -= 0.3f;
    //     }

    //     break;
    }
}
