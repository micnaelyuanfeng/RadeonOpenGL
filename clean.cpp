#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <assert.h>
#include "GL/glew.h" //should above glut
#include "GL/glut.h"
#include "SDL/SDL.h"
#include "GLM/glm.hpp"
#include "GLM/gtc/type_ptr.hpp"
#include "GLM/gtc/matrix_transform.hpp"
#include "locationData.h"
#include "bufferMgr.h"
#include "shaderMgr.h"


//testing code
GLuint numOfVao = 1;
GLuint numOfGfxCard = 1;
GLuint numOfMicroEngine = 2;

using namespace std;

GLuint vertexArray;
GLuint verticeBuffer;
GLuint colorBuffer;
GLuint matrixId;

GLuint vertexShaderId;
GLuint fragmentShaderId;
GLuint programId;

glm::mat4 projection;
glm::mat4 view;
glm::mat4 model;
glm::mat4 MVP;

void initOpenGL(void)
{
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	glEnable(GL_DEPTH_TEST);//enable to use depth information, if two objs overlap
	glDepthFunc(GL_LEQUAL); //tell opengl how to do test

	glewInit();
}
/*
void buildShaders(void)
{
	vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderId, 1, &VERTEXT_SHADER, NULL); //copy
	glCompileShader(vertexShaderId); //compile

	fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderId, 1, &FRAGMENT_SHADER, NULL); //copy
	glCompileShader(fragmentShaderId); //compile

}
*/
void buildMatrix()
{
	projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.01f, 100.0f);

	view = glm::lookAt(
		glm::vec3(3, 3, 3), // Camera is at (4,3,3), in World Space
		glm::vec3(0, 0, 0), // and looks at the origin
		glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
	);

	//Scale, translate, and rotate
	model = glm::mat4(1.0f);

	MVP = projection * view * model;

	matrixId = glGetUniformLocation(programId, "MVP");

	glUniformMatrix4fv(matrixId, 1, GL_FALSE, &MVP[0][0]);
}

void buildProgram(void)
{
	programId = glCreateProgram();

	//Attach Shader
	glAttachShader(programId, vertexShaderId);
	glAttachShader(programId, fragmentShaderId);
	glLinkProgram(programId);

	buildMatrix();
}

int main(int argc, char **argv)
{
	SDL_Window*   mainWindow;
	SDL_GLContext mainContext;
	SDL_Event     windowEvents = { 0 };

	bool running = true;

	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);


	mainWindow = SDL_CreateWindow("Gfx Render", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, 800, 600,
		SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

	if (mainWindow == NULL)
	{
		SDL_Quit();

		return 1;
	}

	mainContext = SDL_GL_CreateContext(mainWindow);

	initOpenGL();

	//Create data structure
	renderData            renderDataMgr;
	bufferShaderManager   shaderMemMgr;
	shaderManager         shaderCodeMgr;

	renderDataMgr.setRenderDataMgr(&renderDataMgr);
	renderDataMgr.setShaderMemMgr(&shaderMemMgr);

	shaderMemMgr.setRenderDataMgr(&renderDataMgr);
	shaderMemMgr.setShaderMemMgr(&shaderMemMgr);
	//setupBuffers();

	renderDataMgr.renderDataInit();

	shaderMemMgr.createVaoBuffer(VAO);
	shaderMemMgr.createVboBuffer(VBO_GFX);

	shaderCodeMgr.shaderInit();
	shaderCodeMgr.buildVertexShader(SHADER_GFX_VERTEXT);
	shaderCodeMgr.buildFragmentShader(SHADER_GFX_FRAGMENT);
	shaderCodeMgr.buildProgramTwo(SHADER_GFX_VERTEXT, SHADER_GFX_FRAGMENT);
	shaderCodeMgr.enableProgram();
	//buildShaders();
	//buildProgram();

	//buildMatrix();

	projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.01f, 100.0f);

	view = glm::lookAt(
		glm::vec3(3, 3, 3), // Camera is at (4,3,3), in World Space
		glm::vec3(0, 0, 0), // and looks at the origin
		glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
	);

	//Scale, translate, and rotate
	model = glm::mat4(1.0f);

	MVP = projection * view * model;

	matrixId = glGetUniformLocation(shaderCodeMgr.getProgramId(), "MVP");

	glUniformMatrix4fv(matrixId, 1, GL_FALSE, &MVP[0][0]);

	while (running)
	{
		while (SDL_PollEvent(&windowEvents))
		{
			if (windowEvents.type == SDL_QUIT)
			{
				running = false;
			}
			else
			{
				//draw();
			}
		}

		//draw();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderMemMgr.enableVboBuffer(VBO_GFX);

		glDrawArrays(GL_TRIANGLES, 0, 12 * 3);

		SDL_GL_SwapWindow(mainWindow);
	}

	return 0;
}
