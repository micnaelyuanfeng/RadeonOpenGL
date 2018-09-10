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

GLuint matrixId;


glm::mat4 projection;
glm::mat4 view;
glm::mat4 model;
glm::mat4 MVP;


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

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glEnable(GL_DEPTH_TEST);//enable to use depth information, if two objs overlap
	glDepthFunc(GL_LEQUAL); //tell opengl how to do test

	glewInit();

	//Create data structure
	renderData            renderDataMgr;
	bufferShaderManager   shaderMemMgr;
	shaderManager         shaderCodeMgr;

	renderDataMgr.setRenderDataMgr(&renderDataMgr);
	renderDataMgr.setShaderMemMgr(&shaderMemMgr);

	shaderMemMgr.setRenderDataMgr(&renderDataMgr);
	shaderMemMgr.setShaderMemMgr(&shaderMemMgr);

	renderDataMgr.renderDataInit();

	shaderMemMgr.createVaoBuffer(VAO);
	shaderMemMgr.createVboBuffer(VBO_GFX);

	shaderCodeMgr.shaderInit();
	shaderCodeMgr.buildVertexShader(SHADER_GFX_VERTEXT);
	shaderCodeMgr.buildFragmentShader(SHADER_GFX_FRAGMENT);
	shaderCodeMgr.buildProgramTwo(SHADER_GFX_VERTEXT, SHADER_GFX_FRAGMENT);
	shaderCodeMgr.enableProgram();


	projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.01f, 100.0f);

	view = glm::lookAt(
		glm::vec3(3, 3, 3), // Camera is at (4,3,3), in World Space
		glm::vec3(0, 0, 0), // and looks at the origin
		glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
	);

	float       scale = 1.0;
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
			else if(windowEvents.type == SDL_MOUSEBUTTONDOWN)
			{
				switch (windowEvents.button.button)
				{
				case SDL_BUTTON_LEFT:
					SDL_ShowSimpleMessageBox(0, "Mouse Button", "Left", mainWindow);
					break;
				case SDL_BUTTON_RIGHT:
					SDL_ShowSimpleMessageBox(0, "Mouse Button", "Right", mainWindow);
					break;
				case SDL_BUTTON_MIDDLE:
					SDL_ShowSimpleMessageBox(0, "Mouse Button", "Middle", mainWindow);
					break;
				}
				break;
			}
			else if (windowEvents.type == SDL_MOUSEWHEEL)
			{
				if (windowEvents.wheel.x > 0)
				{
					SDL_ShowSimpleMessageBox(0, "Mouse Wheel", "Scroll Right", mainWindow);
				}
				else if (windowEvents.wheel.x < 0)
				{
					SDL_ShowSimpleMessageBox(0, "Mouse Wheel", "Scroll Left", mainWindow);
				}
				else if (windowEvents.wheel.y > 0)
				{
					scale += 0.015;
					//SDL_ShowSimpleMessageBox(0, "Mouse Wheel", "Scroll Up", mainWindow);
				}
				else if (windowEvents.wheel.y < 0)
				{
					scale -= 0.015;
					//SDL_ShowSimpleMessageBox(0, "Mouse Wheel", "Scroll Down", mainWindow);
				}
			}
		}

		//draw();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderMemMgr.enableVboBuffer(VBO_GFX);

		//glm::mat4 translateMatrix = glm::translate(glm::mat4(), glm::vec3(0.0f, 1.0f, 0.0f));

		glm::vec3 scaleMatrix(0.15f, 15.0f, 10.0f);

		model = glm::scale(glm::mat4(1.0), scaleMatrix);

		MVP = projection * view * model;

		glUniformMatrix4fv(matrixId, 1, GL_FALSE, &MVP[0][0]);

		glDrawArrays(GL_TRIANGLES, 0, 12 * 3);

		glm::mat4 temp = model;

		temp = glm::translate(temp, glm::vec3(1.0f, 0.0f, 0.0f));

		temp = temp * glm::scale(glm::mat4(1.0), glm::vec3(1.5f, 0.15f, 0.15f));

		MVP = projection * view * temp;

		glUniformMatrix4fv(matrixId, 1, GL_FALSE, &MVP[0][0]);

		glDrawArrays(GL_TRIANGLES, 0, 12 * 3);


		glm::mat4 temp2 = model;

		temp2 = glm::translate(temp2, glm::vec3(0.0f, 0.0f, 6.0f));

		temp2 = temp2 * glm::scale(glm::mat4(1.0), glm::vec3(1.5f, 0.15f, 0.15f));

		MVP = projection * view * temp2;

		glUniformMatrix4fv(matrixId, 1, GL_FALSE, &MVP[0][0]);

		glDrawArrays(GL_TRIANGLES, 0, 12 * 3);

		SDL_GL_SwapWindow(mainWindow);
	}

	return 0;
}

