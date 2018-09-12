#define GLEW_STATIC		//how to use glew 

#include <iostream>
#include "GL/glew.h" //should above glut
#include "GL/glut.h"

using namespace std;

float counter = -1500.0;

/*
	z = depth
*/

void display()
{
	//For each frame = reset background color | depth value
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//angle and vector rotate around
	//Reset Matrix = reset position in space
	glLoadIdentity();

	//Correct order = translate and rotate
	glTranslatef(counter/1500.0, 0.0, -4.0);
	glRotatef(counter , 0.0, 1.0, 0.0);
	
	counter += 0.05;

	if (counter > 2200.0)
	{
		counter = -2200.0;
	}

	glBegin(GL_TRIANGLES);
		glColor3f(0.0, 1.0, 0.0);
		//z = 1 to 9, default is -1 to 1
		glVertex3f(-0.5, -0.5, -0.0);

		glColor3f(1.0, 0.0, 0.0);
		glVertex3f(0.5, -0.5, -0.0);

		glColor3f(0.0, 0.0, 1.0);
		glVertex3f(0.0, 0.5, -0.0);
	glEnd();

	
	glLoadIdentity();
	// Rang = -1.0 to 1.0 
	glTranslatef(-0.5, -0.8, -4.0);
	glRotatef(75, 0.0, 1.0, 0.0);

	glBegin(GL_TRIANGLES);
		glColor3f(1.0, 0.0, 0.0);
		glVertex3f(-0.9, -0.1, -0.0);

		glColor3f(0.0, 0.0, 1.0);
		glVertex3f(0.1, -0.1, -0.0);

		glColor3f(0.0, 1.0, 0.0);
		glVertex3f(-0.1, 0.9, -0.0);
	glEnd();

	glutSwapBuffers();
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);

	//Create and Set perspective
	//Create = Prodece a matrix to hanle perspective
	//Enable and switch to project mode
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); //reset the Matrix
	//view angle
	//ogl unit = user defined
	//e.g 10.0 - 1.0 = 9.0 ogl unit in depth = visible space
	gluPerspective(60, (float)w/(float)h, 1.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
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

	glClearColor(0.8, 0.0, 0.0, 1.0);

	glEnable(GL_DEPTH_TEST);//enable to use depth information, if two objs overlap
	glDepthFunc(GL_LEQUAL); //tell opengl how to do test

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

void renderData::buildNormalBuffers()
{
	int numOfEntries = sizeof(verticeData) / (sizeof(float) * 3);
	
	GLfloat*   pVerticeData  = verticeData;

	glm::vec3* pNormalBuffer = (glm::vec3*) new glm::vec3[numOfEntries];

	glm::vec3 tempValue;
	

	for (int i = 0; i < numOfEntries; i++)
	{
		tempValue.x = *pVerticeData;
		tempValue.y = *(++pVerticeData);
		tempValue.z = *(++pVerticeData);

		pVerticeData++;
		memcpy((void*)pNormalBuffer, (void*)&tempValue, sizeof(float) * 3);

		cout << pNormalBuffer->x << " " << pNormalBuffer->y << " " << pNormalBuffer->z << endl;
		cout << endl;

		pNormalBuffer++;
	}

}
