/*
 * SimpleDraw.c
 *
 * Example program illustrating a simple use
 * of OpenGL to draw straight lines in 2D, and
 * to draw overlapping triangles in 3D.
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include "Glut.h"	// OpenGL Graphics Utility Library
#include "SimpleDraw.h"

 // These variables control the current mode
float angle = 45.0f;
int CurrentMode = 0;
const int NumModes = 3; //6 jer imas 6 case 5 i nulti tkd 6 mogla sam da stavim i 10 ali onda bi 4puta vrtelo prazno jer nema tih case-ova!!!

// These variables set the dimensions of the rectanglar region we wish to view.
const double Xmin = 0.0, Xmax = 3.0;
const double Ymin = 0.0, Ymax = 3.0;

// glutKeyboardFunc is called below to set this function to handle
//		all "normal" ascii key presses.
// Only space bar and escape key have an effect.
void myKeyboardFunc(unsigned char key, int x, int y)
{
	switch (key) {

	case ' ':									// Space bar
		// Increment the current mode, and tell operating system screen needs redrawing
		CurrentMode = (CurrentMode + 1) % NumModes;
		glutPostRedisplay();
		break;

	case 27:									// "27" is theEscape key
		exit(1);

	}
}


/*
 * drawScene() handles the animation and the redrawing of the
 *		graphics window contents.
 */
void drawScene(void) {
	// Clear the rendering window
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Set drawing color to white
	glColor3f(1.0, 1.0, 1.0);

	switch (CurrentMode)
	{
	case 0:
		glBegin(GL_POINTS);
		glColor3f(1.0,1.0,0.0);
		glVertex3f(0.3, 0.0, 0.0);
		glEnd();
	case 1:
		glBegin(GL_LINES);
		glColor3f(1.0, 0.0, 0.0);
		glVertex3f(0.3, 0.0, 0.0);
		glVertex3f(0.3, 1.0, 0.0);
		glEnd();
	case 2:
		glBegin(GL_POLYGON);
		glColor3f(1.0, 0.0, 0.0);
		glVertex3f(0.3, 0.0, 0.0);
		glColor3f(0.0, 1.0, 0.0);
		glVertex3f(0.9, 1.0, 0.0);
		glColor3f(0.0, 0.0, 1.0);
		glVertex3f(2.0, 1.0, 0.0);
		glColor3f(1.0, 1.0, 1.0);
		glVertex3f(2.6, 0.0, 0.0);
		glEnd();
		glBegin(GL_QUADS);
		glColor3f(0.0, 1.0, 0.0);
		glVertex2f(1.1, 1.0);
		glVertex2f(1.6, 1.0);
		glVertex2f(1.6, 1.5);
		glVertex2f(1.1, 1.5);
		glEnd();
		if (CurrentMode == 1) {
			glColor3f(0.0, 1.0, 0.0);
			glBegin(GL_LINE);
			glVertex2f(1.6, 1.5);
			glVertex2f(1.1, 1.5);
		}
		else if(CurrentMode == 2) {
			glTranslatef( 0.0, 1.0, 0.0);
			glRotatef(angle, 1.0, 0.0, 0.0);
			glTranslatef( -0.0,-1.0,0.0);
		}
		else {
			//glPopMatrix();
			glTranslatef(0.10f, 0.00f, 0.0f); //po x ide jer je samo ona zadata a ovo je brzina kojom ce da se krece
		}

		// Flush the pipeline.  (Not usually necessary.)
		glFlush();

	}
}
// Initialize OpenGL's rendering modes
void initRendering()
{

	glEnable(GL_DEPTH_TEST);

	// Uncomment out the first block of code below, and then the second block,
	//		to see how they affect line and point drawing.
/*
	// The following commands should cause points and line to be drawn larger
	//	than a single pixel width.
	glPointSize(8);
	glLineWidth(5);



	// The following commands should induce OpenGL to create round points and
	//	antialias points and lines.  (This is implementation dependent unfortunately).
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);	// Make round points, not square points
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);		// Antialias the lines
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
*/

}

// Called when the window is resized
//		w, h - width and height of the window in pixels.
void resizeWindow(int w, int h)
{
	double scale, center;
	double windowXmin, windowXmax, windowYmin, windowYmax;

	// Define the portion of the window used for OpenGL rendering.
	glViewport(0, 0, w, h);	// View port uses whole window

	// Set up the projection view matrix: orthographic projection
	// Determine the min and max values for x and y that should appear in the window.
	// The complication is that the aspect ratio of the window may not match the
	//		aspect ratio of the scene we want to view.
	w = (w == 0) ? 1 : w;
	h = (h == 0) ? 1 : h;
	if ((Xmax - Xmin) / w < (Ymax - Ymin) / h) {
		scale = ((Ymax - Ymin) / h) / ((Xmax - Xmin) / w);
		center = (Xmax + Xmin) / 2;
		windowXmin = center - (center - Xmin) * scale;
		windowXmax = center + (Xmax - center) * scale;
		windowYmin = Ymin;
		windowYmax = Ymax;
	}
	else {
		scale = ((Xmax - Xmin) / w) / ((Ymax - Ymin) / h);
		center = (Ymax + Ymin) / 2;
		windowYmin = center - (center - Ymin) * scale;
		windowYmax = center + (Ymax - center) * scale;
		windowXmin = Xmin;
		windowXmax = Xmax;
	}

	// Now that we know the max & min values for x & y that should be visible in the window,
	//		we set up the orthographic projection.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(windowXmin, windowXmax, windowYmin, windowYmax, -1, 1);

}


// Main routine
// Set up OpenGL, define the callbacks and start the main loop
int main(int argc, char** argv)
{
	glutInit(&argc, argv);

	// The image is not animated so single buffering is OK. 
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);

	// Window position (from top corner), and size (width and hieght)
	glutInitWindowPosition(20, 60);
	glutInitWindowSize(360, 360);
	glutCreateWindow("SimpleDraw - Press space bar to toggle images");

	// Initialize OpenGL as we like it..
	initRendering();

	// Set up callback functions for key presses
	glutKeyboardFunc(myKeyboardFunc);			// Handles "normal" ascii symbols
	// glutSpecialFunc( mySpecialKeyFunc );		// Handles "special" keyboard keys

	// Set up the callback function for resizing windows
	glutReshapeFunc(resizeWindow);

	// Call this for background processing
	// glutIdleFunc( myIdleFunction );

	// call this whenever window needs redrawing
	glutDisplayFunc(drawScene);

	fprintf(stdout, "Press space bar to toggle images; escape button to quit.\n");

	// Start the main loop.  glutMainLoop never returns.
	glutMainLoop();

	return(0);	// This line is never reached.
}