#include <iostream>
#include "GL/glew.h" //should above glut
#include "GL/glut.h"

//linear interpolation is done by gfx card

using namespace std;

//3D data
//OpenGL internel data type
//In defeult OpenGL space, there is no matrixes defined
// -1.0 to 1.0 for x, y, z
//Normal way
GLfloat vertices[] = { -0.5, -0.5, 0.0, //v1
						0.0,  0.0, 1.0, //v1c
						0.5, -0.5, 0.0, //v2
						0.0,  0.0, 1.0, //v2c
						0.0,  0.5, 0.0,
						0.0,  0.0, 1.0 ,
						-0.7, 0.0, 0.0, //v1
						0.0,  0.0, 1.0, //v1c
						0.5, 0.0, 0.0, //v2
						0.0,  0.0, 1.0, //v2c
						0.0,  0.5, 0.0,
						0.0,  0.0, 1.0 };//v3
//Color = RGB channels R      G    B

GLuint VBOID;

void display()
{
	//For each frame = reset background color defined by glClearColor | depth value
	//reset for redraw                need to add this if using depth information
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Start Drawing
	//Tell openGl read vertices data from an array
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	//new solution to draw using data in gfx buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBOID); //activate buffer


	//Tell openGL structure of array = how to parse the data
	// 3 = 3D; 2 = 2D 
	// e.g each 3 value in this array represents a vertices
	glVertexPointer(3, GL_FLOAT, 6 * sizeof(GLfloat), 0);// 0 is starting address of the buffer
	glColorPointer(3, GL_FLOAT, 24, (GLvoid*)(VBOID + 3));
	//Draw shape type
	//Linear interpolation and restariztion

	glDrawArrays(GL_TRIANGLES, 0, 6); //send commands to gfx card
	//glDrawArrays(GL_TRIANGLES, 1, 3);
	//glDrawArrays(GL_TRIANGLES, 2, 3);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);

	glutSwapBuffers();
}

void reshape(int w, int h)
{
	
}

void initOpenGL()
{
	//set background color only
	glClearColor(1.0, 0.0, 0.0, 1.0);

	//Tell ogl use depth information
	//ogl will do depth test
	glEnable(GL_DEPTH_TEST);//enable to use depth information, if two objs overlap
	glDepthFunc(GL_LEQUAL); //tell opengl how to do test

	//Initialize all extensions which allow to create buffers on gfx card
	glewInit();

	//copy data to gfx card
	/*
		1. ask gfx for a piece of memory to put data which required for later rendering
	*/

	//In case of many triangles to draw, copying data hurt performance,
	//then use buffer and just copy once
	// num of buffer and handle
	glGenBuffers(1, &VBOID);
	glBindBuffer(GL_ARRAY_BUFFER, VBOID);                     //not change very often
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//unbined buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void idle()
{
	glutPostRedisplay();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 200);
	glutCreateWindow("Gfx Render");

	initOpenGL();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);
	glutMainLoop();
}


//perspective view in ogl
/*
	1. position of camera
	2. the way to laook at the world
	3. Near clip plane = closest thing can see
	4. Far clip plane  = farest thing can see
*/
