#pragma once

#include "GL/glew.h" 
#include "GL/glut.h"
#include "GLM/glm.hpp"
#include "locationData.h"

extern GLuint numOfGfxCard;
extern GLuint numOfMicroEngine;

#include <iostream>

using namespace std;

static GLfloat verticeData[] = {
-1.0f, -1.0f, -1.0f,
1.0f, -1.0f, -1.0f,
1.0f, 1.0f, -1.0f,
1.0f, 1.0f, -1.0f,
-1.0f, 1.0f, -1.0f,
-1.0f, -1.0f, -1.0f,

-1.0f, -1.0f, 1.0f,
1.0f, -1.0f, 1.0f,
1.0f, 1.0f, 1.0f,
1.0f, 1.0f, 1.0f,
-1.0f, 1.0f, 1.0f,
-1.0f, -1.0f, 1.0f,

-1.0f, 1.0f, 1.0f,
-1.0f, 1.0f, -1.0f,
-1.0f, -1.0f, -1.0f,
-1.0f, -1.0f, -1.0f,
-1.0f, -1.0f, 1.0f,
-1.0f, 1.0f, 1.0f,

1.0f, 1.0f, 1.0f,
1.0f, 1.0f, -1.0f,
1.0f, -1.0f, -1.0f,
1.0f, -1.0f, -1.0f,
1.0f, -1.0f, 1.0f,
1.0f, 1.0f, 1.0f,

-1.0f, -1.0f, -1.0f,
1.0f, -1.0f, -1.0f,
1.0f, -1.0f, 1.0f,
1.0f, -1.0f, 1.0f,
-1.0f, -1.0f, 1.0f,
-1.0f, -1.0f, -1.0f,

-1.0f, 1.0f, -1.0f,
1.0f, 1.0f, -1.0f,
1.0f, 1.0f, 1.0f,
1.0f, 1.0f, 1.0f,
-1.0f, 1.0f, 1.0f,
-1.0f, 1.0f, -1.0f
};

static GLfloat colorBufferData[] = {
			0.5f,  0.0f,  0.0f,
			0.5f,  0.0f,  0.0f,
			0.5f,  0.0f,  0.0f,
			0.5f,  0.0f,  0.0f,
			0.5f,  0.0f,  0.0f,
			0.5f,  0.0f,  0.0f,

			0.8f,  0.0f,  0.0f,
			0.8f,  0.0f,  0.0f,
			0.8f,  0.0f,  0.0f,
			0.8f,  0.0f,  0.0f,
			0.8f,  0.0f,  0.0f,
			0.8f,  0.0f,  0.0f,

			1.5f,  0.0f,  0.0f,
			1.5f,  0.0f,  0.0f,
			1.5f,  0.0f,  0.0f,
			1.5f,  0.0f,  0.0f,
			1.5f,  0.0f,  0.0f,
			1.5f,  0.0f,  0.0f,

			1.5f,  0.0f,  0.0f,
			1.5f,  0.0f,  0.0f,
			1.5f,  0.0f,  0.0f,
			1.5f,  0.0f,  0.0f,
			1.5f,  0.0f,  0.0f,
			1.5f,  0.0f,  0.0f,

			0.8f,  0.0f,  0.0f,
			0.8f,  0.0f,  0.0f,
			0.8f,  0.0f,  0.0f,
			0.8f,  0.0f,  0.0f,
			0.8f,  0.0f,  0.0f,
			0.8f,  0.0f,  0.0f,

			0.5f,  0.0f,  0.0f,
			0.5f,  0.0f,  0.0f,
			0.5f,  0.0f,  0.0f,
			0.5f,  0.0f,  0.0f,
			0.5f,  0.0f,  0.0f,
			0.5f,  0.0f,  0.0f,


};

static GLfloat colorBufferDataMicroEngine[] = {
			0.5f,  0.0f,  1.0f,
			0.5f,  0.0f,  1.0f,
			0.5f,  0.0f,  1.0f,
			0.5f,  0.0f,  1.0f,
			0.5f,  0.0f,  1.0f,
			0.5f,  0.0f,  1.0f,

			0.8f,  0.0f,  1.0f,
			0.8f,  0.0f,  1.0f,
			0.8f,  0.0f,  1.0f,
			0.8f,  0.0f,  1.0f,
			0.8f,  0.0f,  1.0f,
			0.8f,  0.0f,  1.0f,

			1.5f,  0.0f,  1.0f,
			1.5f,  0.0f,  1.0f,
			1.5f,  0.0f,  1.0f,
			1.5f,  0.0f,  1.0f,
			1.5f,  0.0f,  1.0f,
			1.5f,  0.0f,  1.0f,

			1.5f,  0.0f,  1.0f,
			1.5f,  0.0f,  1.0f,
			1.5f,  0.0f,  1.0f,
			1.5f,  0.0f,  1.0f,
			1.5f,  0.0f,  1.0f,
			1.5f,  0.0f,  1.0f,

			0.8f,  0.0f,  1.0f,
			0.8f,  0.0f,  1.0f,
			0.8f,  0.0f,  1.0f,
			0.8f,  0.0f,  1.0f,
			0.8f,  0.0f,  1.0f,
			0.8f,  0.0f,  1.0f,

			0.5f,  0.0f,  1.0f,
			0.5f,  0.0f,  1.0f,
			0.5f,  0.0f,  1.0f,
			0.5f,  0.0f,  1.0f,
			0.5f,  0.0f,  1.0f,
			0.5f,  0.0f,  1.0f,


};

renderData::renderData():vertexArrayId(NULL), gfxCardBufferId(NULL), microEngineBufferId(NULL),
				         programId(NULL), gfxCardVerticeData(NULL), microEngineVerticeData(NULL), gfxColorData(NULL), 
						 microEngineColorData(NULL), uvData(NULL)
{

}

renderData::~renderData()
{
	;
}

void renderData::renderDataInit()
{
	cout << "Render Init Called" << endl;

	programId            = (GLuint*) new GLuint;
	vertexArrayId        = (GLuint*) new GLuint;

	gfxCardBufferId      = (GLuint*) new GLuint[numOfGfxCard];
	microEngineBufferId  = (GLuint*) new GLuint[numOfMicroEngine];

	gfxCardColorBufferId = (GLuint*) new GLuint[numOfGfxCard];
	microEngineBufferId  = (GLuint*) new GLuint[numOfMicroEngine];

	gfxCardVerticeData   = verticeData;
	
	gfxColorData         = colorBufferData;
	microEngineColorData = colorBufferDataMicroEngine;

	mvpGfx               = new struct mvpMatrix[numOfGfxCard];
	mvpMicroEngine       = new struct mvpMatrix[numOfMicroEngine];
}

size_t renderData::getSizeVerticeDataGfx(void)
{
	return sizeof(verticeData);
}

size_t renderData::getSizeColorDataGfx(void)
{
	return sizeof(colorBufferData);
}