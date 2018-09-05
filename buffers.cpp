#include <iostream>
#include <string>
#include <assert.h>
#include "GL/glew.h" //should above glut
#include "GL/glut.h"
#include "SDL/SDL.h"
#include "GLM/glm.hpp"
#include "GLM/gtc/matrix_transform.hpp"

const char* VERTEXT11_SHADER =
"#version 330 core\n"
"layout(location = 0) in vec3 vertexPosition_modelspace;\n"
"void main()\n"
"{\n"
"	gl_Position.xyz = vertexPosition_modelspace;\n"
"	gl_Position.w   = 1.0;\n"
"}\n";

const char* FRAGMENT_SHADER =
"#version 330 core\n"
"in vec3 fragmentColor;\n"
"out vec3 color;\n"
"void main()\n"
"{\n"
"color = fragmentColor;\n"
"}\n";


const char* VERTEXT_SHADER =
"#version 330 core\n"
"layout(location = 0) in vec3 vertexPosition_modelspace;\n"
"layout(location = 1) in vec3 vertexColor;\n"
"uniform mat4 MVP;\n"
"out vec3 fragmentColor;\n"
"void main(){\n"
"gl_Position =  MVP * vec4(vertexPosition_modelspace,1);\n"
"fragmentColor = vertexColor;\n"
"}\n";
//linear interpolation is done by gfx card

using namespace std;

//3D data
//OpenGL internel data type
//In defeult OpenGL space, there is no matrixes defined
// -1.0 to 1.0 for x, y, z
//Normal way
GLfloat vertices[] = {  -1.0f,-1.0f,-1.0f, // triangle 1 : begin
						-1.0f,-1.0f, 1.0f,
						-1.0f, 1.0f, 1.0f, // triangle 1 : end
						 1.0f, 1.0f,-1.0f, // triangle 2 : begin
						-1.0f,-1.0f,-1.0f,
						-1.0f, 1.0f,-1.0f, // triangle 2 : end
						 1.0f,-1.0f, 1.0f,
						-1.0f,-1.0f,-1.0f,
						 1.0f,-1.0f,-1.0f,
						 1.0f, 1.0f,-1.0f,
						 1.0f,-1.0f,-1.0f,
						-1.0f,-1.0f,-1.0f,
						-1.0f,-1.0f,-1.0f,
						-1.0f, 1.0f, 1.0f,
						-1.0f, 1.0f,-1.0f,
						 1.0f,-1.0f, 1.0f,
						-1.0f,-1.0f, 1.0f,
						-1.0f,-1.0f,-1.0f,
						-1.0f, 1.0f, 1.0f,
						-1.0f,-1.0f, 1.0f,
						 1.0f,-1.0f, 1.0f,
						 1.0f, 1.0f, 1.0f,
						 1.0f,-1.0f,-1.0f,
						 1.0f, 1.0f,-1.0f,
						 1.0f,-1.0f,-1.0f,
						 1.0f, 1.0f, 1.0f,
						 1.0f,-1.0f, 1.0f,
						 1.0f, 1.0f, 1.0f,
						 1.0f, 1.0f,-1.0f,
						-1.0f, 1.0f,-1.0f,
						 1.0f, 1.0f, 1.0f,
						-1.0f, 1.0f,-1.0f,
						-1.0f, 1.0f, 1.0f,
						 1.0f, 1.0f, 1.0f,
						-1.0f, 1.0f, 1.0f,
						 1.0f,-1.0f, 1.0f
};
//Color = RGB channels     R      G    B
static const GLfloat colorBufferData[] = {
						1.0f,  0.0f,  0.0f,
						1.0f,  0.0f,  0.0f,
						1.0f,  0.0f,  0.0f,
						0.822f,  0.569f,  0.201f,
						0.435f,  0.602f,  0.223f,
						0.310f,  0.747f,  0.185f,
						0.597f,  0.770f,  0.761f,
						0.559f,  0.436f,  0.730f,
						0.359f,  0.583f,  0.152f,
						0.483f,  0.596f,  0.789f,
						0.559f,  0.861f,  0.639f,
						0.195f,  0.548f,  0.859f,
						0.014f,  0.184f,  0.576f,
						0.771f,  0.328f,  0.970f,
						0.406f,  0.615f,  0.116f,
						0.676f,  0.977f,  0.133f,
						0.971f,  0.572f,  0.833f,
						0.140f,  0.616f,  0.489f,
						0.997f,  0.513f,  0.064f,
						0.945f,  0.719f,  0.592f,
						0.543f,  0.021f,  0.978f,
						0.279f,  0.317f,  0.505f,
						0.167f,  0.620f,  0.077f,
						0.347f,  0.857f,  0.137f,
						0.055f,  0.953f,  0.042f,
						0.714f,  0.505f,  0.345f,
						0.783f,  0.290f,  0.734f,
						0.722f,  0.645f,  0.174f,
						0.302f,  0.455f,  0.848f,
						0.225f,  0.587f,  0.040f,
						0.517f,  0.713f,  0.338f,
						0.053f,  0.959f,  0.120f,
						0.393f,  0.621f,  0.362f,
						0.673f,  0.211f,  0.457f,
						0.820f,  0.883f,  0.371f,
						0.982f,  0.099f,  0.879f
};

GLuint VBOID;       //VBO1
GLuint colorBuffer; //VBO2

void display()
{
	//For each frame = reset background color defined by glClearColor | depth value
	//reset for redraw                need to add this if using depth information
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glDrawArrays(GL_TRIANGLES, 0, 12 * 3); //send commands to gfx card
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
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

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

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &colorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colorBufferData), colorBufferData, GL_STATIC_DRAW);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//unbined buffer
	//glBindBuffer(GL_ARRAY_BUFFER, 0);

	//load shader
	GLint  result = GL_FALSE;
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

	int InfoLogLength = 0;

	glShaderSource(VertexShaderID, 1, &VERTEXT_SHADER, NULL);
	glCompileShader(VertexShaderID);

	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &result);
	assert(result == GL_TRUE);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);

	result = GL_FALSE;
	glShaderSource(FragmentShaderId, 1, &FRAGMENT_SHADER, NULL);
	glCompileShader(FragmentShaderId);

	glGetShaderiv(FragmentShaderId, GL_COMPILE_STATUS, &result);
	assert(result == GL_TRUE);
	glGetShaderiv(FragmentShaderId, GL_INFO_LOG_LENGTH, &InfoLogLength);

	GLuint programID = glCreateProgram();

	glAttachShader(programID, VertexShaderID);
	glAttachShader(programID, FragmentShaderId);
	glLinkProgram(programID);

	GLuint matrixID = glGetUniformLocation(programID, "MVP");

	glm::mat4 projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.01f, 100.0f);

	glm::mat4 view = glm::lookAt(
		glm::vec3(4, 3, 3), // Camera is at (4,3,3), in World Space
		glm::vec3(0, 0, 0), // and looks at the origin
		glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
	);

	glm::mat4 model = glm::mat4(1.0f);

	glm::mat4 MVP = projection * view * model;

	glUseProgram(programID);
	glUniformMatrix4fv(matrixID, 1, GL_FALSE, &MVP[0][0]);
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
