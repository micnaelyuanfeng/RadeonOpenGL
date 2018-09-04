#include <iostream>
#include <string>
#include <assert.h>
#include "GL/glew.h" //should above glut
#include "GL/glut.h"
#include "SDL/SDL.h"


const char* VERTEXT_SHADER =
"#version 330 core\n"
"layout(location = 0) in vec3 vertexPosition_modelspace;\n"
"void main()\n"
"{\n"
"	gl_Position.xyz = vertexPosition_modelspace;\n"
"	gl_position     = 1.0;\n"
"}\n";

const char* FRAGMENT_SHADER = 
"#version 330 core\n"
"out vec3 color;\n"
"void main()\n"
"{\n"
"color = vec3(0,0,0);\n"
"}\n";

//linear interpolation is done by gfx card

using namespace std;

//3D data
//OpenGL internel data type
//In defeult OpenGL space, there is no matrixes defined
// -1.0 to 1.0 for x, y, z
//Normal way
GLfloat vertices[] = { -0.5, -0.5, 0.0, //v1
						//0.0,  1.0, 1.0, //v1c
						0.5, -0.5, 0.0, //v2
						//0.0,  0.0, 1.0, //v2c
						0.0,  0.5, 0.0,
	//0.0,  1.0, 1.0 ,
	-0.7, 0.0, 0.0, //v1
	//0.0,  0.0, 1.0, //v1c
	0.5, 0.0, 0.0, //v2
	//0.0,  0.0, 1.0, //v2c
	0.0,  0.5, 0.0,
	//0.0,  1.0, 1.0 };//v3
};
//Color = RGB channels R      G    B

GLuint VBOID;

void display()
{
	//For each frame = reset background color defined by glClearColor | depth value
	//reset for redraw                need to add this if using depth information
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//load shader
	

	//Start Drawing
	//Tell openGl read vertices data from an array
	glEnableVertexAttribArray(0);
	//glEnableClientState(GL_COLOR_ARRAY);

	//new solution to draw using data in gfx buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBOID); //activate buffer

	//Tell openGL structure of array = how to parse the data
	// 3 = 3D; 2 = 2D 
	// e.g each 3 value in this array represents a vertices
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);// 0 is starting address of the buffer
	//glColorPointer(3, GL_FLOAT,  6 * sizeof(GLfloat), (GLvoid*)(sizeof(GLfloat) * 3));
	//Draw shape type
	//Linear interpolation and restariztion

	glDrawArrays(GL_TRIANGLES, 0, 6); //send commands to gfx card
	//glDrawArrays(GL_TRIANGLES, 1, 3);
	//glDrawArrays(GL_TRIANGLES, 2, 3);

	glDisableVertexAttribArray(0);
	//glDisableClientState(GL_VERTEX_ARRAY);
	//glDisableClientState(GL_COLOR_ARRAY);

}

void reshape(int w, int h)
{
	
}

void initOpenGL()
{
	//set background color only
	glClearColor(0.0, 1.0, 0.0, 0.0);

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
	GLuint VertextArrayId;
	glGenVertexArrays(1, &VertextArrayId);
	glBindVertexArray(VertextArrayId);
	//In case of many triangles to draw, copying data hurt performance,
	//then use buffer and just copy once
	// num of buffer and handle
	glGenBuffers(1, &VBOID);
	glBindBuffer(GL_ARRAY_BUFFER, VBOID);                     //not change very often
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//unbined buffer
	//glBindBuffer(GL_ARRAY_BUFFER, 0);

	//load shader
	GLint  result = GL_FALSE;
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

	int InfoLogLength = 0;

	glShaderSource(VertexShaderID, 1, &VERTEXT_SHADER, NULL);
	assert(result != GL_TRUE);
	glCompileShader(VertexShaderID);

	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);

	result = GL_FALSE;
	glShaderSource(FragmentShaderId, 1, &FRAGMENT_SHADER, NULL);
	assert(result != GL_TRUE);
	glCompileShader(FragmentShaderId);

	glGetShaderiv(FragmentShaderId, GL_COMPILE_STATUS, &result);
	glGetShaderiv(FragmentShaderId, GL_INFO_LOG_LENGTH, &InfoLogLength);

	//Link
	GLuint programID = glCreateProgram();

	glAttachShader(programID, VertexShaderID);
	glAttachShader(programID, FragmentShaderId);
	glLinkProgram(programID);

	glUseProgram(programID);

}

void idle()
{
	glutPostRedisplay();
}

int main(int argc, char **argv)
{
	SDL_Window*   mainWindow;
	SDL_GLContext mainContext;
	SDL_Event     windowEvents = { 0 };

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);


	bool running = true;

	mainWindow = SDL_CreateWindow("Gfx Render", SDL_WINDOWPOS_CENTERED, 
		                           SDL_WINDOWPOS_CENTERED, 640, 480, 
		                           SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

	if (mainWindow == NULL)
	{
		SDL_Quit();

		return 1;
	}

	/* Create our opengl context and attach it to our window */
	mainContext = SDL_GL_CreateContext(mainWindow);

	initOpenGL();

	while (running)
	{
		while (SDL_PollEvent(&windowEvents))
		{
			if (windowEvents.type == SDL_QUIT)
			{
				running = false;
			}
			else if (windowEvents.type == SDL_KEYDOWN)
			{

			}
			else if (windowEvents.type == SDL_MOUSEBUTTONDOWN)
			{

			}
		}
		
		display();

		SDL_GL_SwapWindow(mainWindow);
	}

	return 0;
}


//perspective view in ogl
/*
	1. position of camera
	2. the way to laook at the world
	3. Near clip plane = closest thing can see
	4. Far clip plane  = farest thing can see
*/
