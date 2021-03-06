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
#include "matrixTransform.h"


//testing code
GLuint numOfVao = 1;
GLuint numOfGfxCard = 1;
GLuint numOfMicroEngine = 3;

GLuint bountry  = 0.01f;
GLuint intervel = 0.01f;

using namespace std;

GLuint matrixId;
GLuint colorId;
GLuint lightId;

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
	glEnable(GL_CULL_FACE);

	glewInit();

	//Create data structure
	renderData                renderDataMgr;
	bufferShaderManager       shaderMemMgr;
	shaderManager             shaderCodeMgr;
	matrixTransformManagement matrixTransformMgr;

	renderDataMgr.setRenderDataMgr(&renderDataMgr);
	renderDataMgr.setShaderMemMgr(&shaderMemMgr);

	shaderMemMgr.setRenderDataMgr(&renderDataMgr);
	shaderMemMgr.setShaderMemMgr(&shaderMemMgr);

	renderDataMgr.renderDataInit();

	size_t numOfEntriesVerticesData = renderDataMgr.getNumOfEntriesVerticeData();
    glm::vec3* normalVerticesData   = (glm::vec3*) new glm::vec3[numOfEntriesVerticesData/3];

	renderDataMgr.buildNormalBuffers(normalVerticesData, numOfEntriesVerticesData);

	shaderMemMgr.createVaoBuffer(VAO);
	shaderMemMgr.createVboBuffer(VBO_GFX);

	shaderCodeMgr.shaderInit();
	shaderCodeMgr.buildVertexShader(SHADER_GFX_VERTEXT);
	shaderCodeMgr.buildFragmentShader(SHADER_GFX_FRAGMENT);
	shaderCodeMgr.buildProgramTwo(SHADER_GFX_VERTEXT, SHADER_GFX_FRAGMENT);
	shaderCodeMgr.enableProgram();

	GLuint normalBufferId;
	glGenBuffers(1, &normalBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, normalBufferId);
	glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(glm::vec3), normalVerticesData, GL_STATIC_DRAW);

	//create scalar matrix, rotate matrix, and translate matrix
	glm::vec3* pScaleMatrix_0_15f      = matrixTransformMgr.createScaleVector(0.15f, SCALE_DOWN);
	glm::vec3* pTranslateMatrix_0_75_y = matrixTransformMgr.createTranslateVector(1.35f, TRANSLATE_Y);
	glm::vec3* pTranslateMatrix_1_0_x  = matrixTransformMgr.createTranslateVector(0.15f, TRANSLATE_X);

	projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.01f, 100.0f);

	view = glm::lookAt(
		glm::vec3(3, 3, 3), // Camera is at (4,3,3), in World Space
		glm::vec3(0, 0, 0), // and looks at the origin
		glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
	);

	float       scale = 0.0;
	//Scale, translate, and rotate
	model = glm::mat4(1.0f);

	MVP = projection * view * model;

	matrixId = glGetUniformLocation(shaderCodeMgr.getProgramId(), "MVP");
	colorId  = glGetUniformLocation(shaderCodeMgr.getProgramId(), "thisColor");
	//lightId = glGetUniformLocation(shaderCodeMgr.getProgramId(), "LightPosition_worldspace");

	glm::vec3 colorRed(1.0f, 0.0f, 0.0f);
	glm::vec3 colorBlue(0.0f, 1.0f, 0.0f);
	glm::vec3 colorEdge(0.0f, 0.0f, 1.0f);

	glUniformMatrix4fv(matrixId, 1, GL_FALSE, &MVP[0][0]);

	//glm::vec3 lightPos = glm::vec3(4, 4, 4);
	//glUniform3f(lightId, lightPos.x, lightPos.y, lightPos.z);

	//glEnableVertexAttribArray(2);
	//glBindBuffer(GL_ARRAY_BUFFER, normalBufferId);
	//glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

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

		MVP = projection * view * model * glm::scale(glm::mat4(1.0), glm::vec3(0.015f + scale, 1.5f + scale, 1.0f + scale));

		glUniformMatrix4fv(matrixId, 1, GL_FALSE, &MVP[0][0]);

		glUniform3fv(colorId, 1, &colorRed[0]);

		glDrawArrays(GL_LINES, 0, 16 * 2);

		//MicroEngine

		//MVP = projection * view * model
		//	* glm::translate(glm::mat4(1.0), *pTranslateMatrix_0_75_y)
		//	* glm::translate(glm::mat4(1.0), *pTranslateMatrix_1_0_x)
		//	* glm::scale(glm::mat4(1.0f), *pScaleMatrix_0_15f);

		//glUniformMatrix4fv(matrixId, 1, GL_FALSE, &MVP[0][0]);

		//glUniform3fv(colorId, 1, &colorEdge[0]);

		//glDrawArrays(GL_TRIANGLES, 0, 12 * 3);

		SDL_GL_SwapWindow(mainWindow);
	}

	return 0;
}

