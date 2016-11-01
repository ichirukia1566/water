#ifdef _WIN32
#include <windows.h>
#endif

#define GLEW_STATIC 1
#include "gl_2_1.h"
#include <stdio.h>
#include <GL/freeglut.h>
//#include <GL/glui.h>
#include "GPGPU.h"

static int winWidth = 512;
static int winHeight = 512;
static int winId = -1;
//static GLUI *glui;

GPGPU  *gpgpu;
unsigned int t = 0;

/*****************************************************************************
*****************************************************************************/
static void
leftButtonDownCB(void)
{
   gpgpu->restart();
}

/*****************************************************************************
*****************************************************************************/
static void
leftButtonUpCB(void)
{
}

/*****************************************************************************
*****************************************************************************/
static void
middleButtonDownCB(void)
{
}


/*****************************************************************************
*****************************************************************************/
static void
middleButtonUpCB(void)
{
}

/*****************************************************************************
*****************************************************************************/
static void
rightButtonDownCB(void)
{
}


/*****************************************************************************
*****************************************************************************/
static void
rightButtonUpCB(void)
{
}

/*****************************************************************************
*****************************************************************************/
static void
mouseCB(int button, int state, int x, int y)
{
   if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
      leftButtonDownCB();
   else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
      leftButtonUpCB();
   else if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
      middleButtonDownCB();
   else if (button == GLUT_MIDDLE_BUTTON && state == GLUT_UP)
      middleButtonUpCB();
   else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
      rightButtonDownCB();
   else if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP)
      rightButtonUpCB();
}


/*****************************************************************************
*****************************************************************************/
static void
motionCB(int x, int y)
{
}


/*****************************************************************************
*****************************************************************************/
void
reshapeCB(int width, int height)
{
    if (height == 0) height = 1;
    
    glViewport(0, 0, width, height);
    
	// Use orthographic projection
    glMatrixMode(GL_PROJECTION);    
    glLoadIdentity();               
    gluOrtho2D(-1, 1, -1, 1);       
    glMatrixMode(GL_MODELVIEW);     
    glLoadIdentity();   
}

/*****************************************************************************
*****************************************************************************/
void
keyboardCB(unsigned char key, int x, int y)
{
}

/*****************************************************************************
*****************************************************************************/
void
idleFunc()
{		
	glutPostRedisplay();
}

/*****************************************************************************
*****************************************************************************/
void
refreshCB()
{
	gpgpu->update((float) t * 0.002);  
	t++;
	// Display the results
	gpgpu->display();
    glutSwapBuffers();
}

/*****************************************************************************
*****************************************************************************/
void initialize()
{
    // Create the gpgpu object
    gpgpu = new GPGPU(512, 512);
}

/*****************************************************************************
*****************************************************************************/
void MakeGUI()
{
	//glui = GLUI_Master.create_glui("GUI", 0, 0, 0);
	//glui->add_statictext("GPGPU example");

	//glui->set_main_gfx_window(winId);

	/* We register the idle callback with GLUI, *not* with GLUT */
	//GLUI_Master.set_glutIdleFunc(idleFunc);
}

/*****************************************************************************
*****************************************************************************/
void menu(int cmd)
{
	switch (cmd) {
	case 0:
		gpgpu->moveIslandX(0.1f);
		break;
	case 1:
		gpgpu->moveIslandX(-0.1f);
		break;
	case 2:
		gpgpu->moveIslandY(0.1f);
		break;
	case 3:
		gpgpu->moveIslandY(-0.1f);
		break;
	}
}

void menuIsland(int cmd)
{
	switch (cmd) {
	case 0:
		gpgpu->moveIslandX(0.1f);
		break;
	case 1:
		gpgpu->moveIslandX(-0.1f);
		break;
	case 2:
		gpgpu->moveIslandY(0.1f);
		break;
	case 3:
		gpgpu->moveIslandY(-0.1f);
		break;
	}
}

void menuCenter(int cmd)
{
	
	switch (cmd)
	{
	case 0:
		gpgpu->moveCtX(0, 0.1f);
		break;
	case 1:
		gpgpu->moveCtX(0, -0.1f);
		break;
	case 2:
		gpgpu->moveCtY(0, 0.1f);
		break;
	case 3:
		gpgpu->moveCtY(0, -0.1f);
		break;

	case 4:
		gpgpu->moveCtX(1, 0.1f);
		break;
	case 5:
		gpgpu->moveCtX(1, -0.1f);
		break;
	case 6:
		gpgpu->moveCtY(1, 0.1f);
		break;
	case 7:
		gpgpu->moveCtY(1, -0.1f);
		break;


	case 8:
		gpgpu->moveCtX(2, 0.1f);
		break;
	case 9:
		gpgpu->moveCtX(2, -0.1f);
		break;
	case 10:
		gpgpu->moveCtY(2, 0.1f);
		break;
	case 11:
		gpgpu->moveCtY(2, -0.1f);
		break;
		
	}

}

void menuFreq(int cmd)
{
	switch (cmd)
	{
	case 0:
		gpgpu->changeFreq(0, 5.0f);
		break;
	case 1:
		gpgpu->changeFreq(0, -5.0f);
		break;
	case 2:
		gpgpu->changeFreq(1, 5.0f);
		break;
	case 3:
		gpgpu->changeFreq(1, -5.0f);
		break;
	case 4:
		gpgpu->changeFreq(2, 5.0f);
		break;
	case 5:
		gpgpu->changeFreq(2, -5.0f);
		break;
	}
}

void menuSpeed(int cmd)
{
	switch (cmd)
	{
	case 0:
		gpgpu->changeSpeed(0, 0.005f);
		break;
	case 1:
		gpgpu->changeSpeed(0, -0.005f);
		break;
	case 2:
		gpgpu->changeSpeed(1, 0.005f);
		break;
	case 3:
		gpgpu->changeSpeed(1, -0.005f);
		break;
	case 4:
		gpgpu->changeSpeed(2, 0.005f);
		break;
	case 5:
		gpgpu->changeSpeed(2, -0.005f);
		break;
	}
}

void menuAmp(int cmd)
{
	switch (cmd)
	{
	case 0:
		gpgpu->changeAmp(0, 0.05f);
		break;
	case 1:
		gpgpu->changeAmp(0, -0.05f);
		break;
	case 2:
		gpgpu->changeAmp(1, 0.05f);
		break;
	case 3:
		gpgpu->changeAmp(1, -0.05f);
		break;
	case 4:
		gpgpu->changeAmp(2, 0.05f);
		break;
	case 5:
		gpgpu->changeAmp(2, -0.05f);
		break;
	}
}

int main(int argc, char *argv[])
{
	// init OpenGL/GLUT
	glutInit(&argc, argv);
	
	// create main window
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(winWidth, winHeight);
	glutInitContextVersion(2, 1);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	winId = glutCreateWindow("Right click for menu!");

	initialize();
	
	// Create a menu
	
	int islandMenu = glutCreateMenu(menuIsland);
	glutAddMenuEntry("right by 0.1", 0);
	glutAddMenuEntry("left by 0.1", 1);
	glutAddMenuEntry("up by 0.1", 2);
	glutAddMenuEntry("down by 0.1", 3);

	int centerMenu = glutCreateMenu(menuCenter);
	glutAddMenuEntry("wave 1 right by 0.1", 0);
	glutAddMenuEntry("wave 1 left by 0.1", 1);
	glutAddMenuEntry("wave 1 up by 0.1", 2);
	glutAddMenuEntry("wave 1 down by 0.1", 3);
	glutAddMenuEntry("wave 2 right by 0.1", 4);
	glutAddMenuEntry("wave 2 left by 0.1", 5);
	glutAddMenuEntry("wave 2 up by 0.1", 6);
	glutAddMenuEntry("wave 2 down by 0.1", 7);
	glutAddMenuEntry("wave 3 right by 0.1", 8);
	glutAddMenuEntry("wave 3 left by 0.1", 9);
	glutAddMenuEntry("wave 3 up by 0.1", 10);
	glutAddMenuEntry("wave 3 down by 0.1", 11);

	int freqMenu = glutCreateMenu(menuFreq);
	glutAddMenuEntry("wave 1 by 5.0", 0);
	glutAddMenuEntry("wave 1 by -5.0", 1);
	glutAddMenuEntry("wave 2 by 5.0", 2);
	glutAddMenuEntry("wave 2 by -5.0", 3);
	glutAddMenuEntry("wave 3 by 5.0", 4);
	glutAddMenuEntry("wave 3 by -5.0", 5);

	int speedMenu = glutCreateMenu(menuSpeed);
	glutAddMenuEntry("wave 1 by 0.005", 0);
	glutAddMenuEntry("wave 1 by -0.005", 1);
	glutAddMenuEntry("wave 2 by 0.005", 2);
	glutAddMenuEntry("wave 2 by -0.005", 3);
	glutAddMenuEntry("wave 3 by 0.005", 4);
	glutAddMenuEntry("wave 3 by -0.005", 5);

	int ampMenu = glutCreateMenu(menuAmp);
	glutAddMenuEntry("wave 1 by 0.05", 0);
	glutAddMenuEntry("wave 1 by -0.05", 1);
	glutAddMenuEntry("wave 2 by 0.05", 2);
	glutAddMenuEntry("wave 2 by -0.05", 3);
	glutAddMenuEntry("wave 3 by 0.05", 4);
	glutAddMenuEntry("wave 3 by -0.05", 5);

	int mainMenu = glutCreateMenu(menu);
	glutAddSubMenu("Move island", islandMenu);
	glutAddSubMenu("Move center of", centerMenu);
	glutAddSubMenu("Change frequency of", freqMenu);
	glutAddSubMenu("Change speed of", speedMenu);
	glutAddSubMenu("Change amplitude of", ampMenu);

	glutAttachMenu(GLUT_RIGHT_BUTTON);


	// setup callbacks
	glutDisplayFunc(refreshCB);
	glutReshapeFunc(reshapeCB);
	glutKeyboardFunc(keyboardCB);
	glutMouseFunc(mouseCB);
	glutMotionFunc(motionCB);
	glutIdleFunc(idleFunc);

	// force initial matrix setup
	reshapeCB(winWidth, winHeight);

	// set modelview matrix stack to identity
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// make GLUI GUI
	//MakeGUI();

	glutMainLoop();

	return (TRUE);
}
