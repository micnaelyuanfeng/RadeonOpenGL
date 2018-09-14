#pragma once

#include "GL/glew.h" 
#include "GL/glut.h"
#include "GLM/glm.hpp"
#include "locationData.h"

extern GLuint numOfGfxCard;
extern GLuint numOfMicroEngine;

#include <iostream>

using namespace std;
/*
static GLfloat verticeData[] = {
1	-1.0f,-1.0f,-1.0f, // triangle 1 : begin
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
1	-1.0f,-1.0f,-1.0f,
	
	-1.0f,-1.0f,-1.0f,
1	-1.0f, 1.0f, 1.0f,
1	-1.0f, 1.0f,-1.0f,
	
1	1.0f,-1.0f, 1.0f,
1	-1.0f,-1.0f, 1.0f,
1	-1.0f,-1.0f,-1.0f,
	
1	-1.0f, 1.0f, 1.0f,
1	-1.0f,-1.0f, 1.0f,
1	1.0f,-1.0f, 1.0f,
	
1	1.0f, 1.0f, 1.0f,
1	1.0f,-1.0f,-1.0f,
1	1.0f, 1.0f,-1.0f,
	
1	1.0f,-1.0f,-1.0f,
1	1.0f, 1.0f, 1.0f,
1	1.0f,-1.0f, 1.0f,
	
1	1.0f, 1.0f, 1.0f,
1	1.0f, 1.0f,-1.0f,
1	-1.0f, 1.0f,-1.0f,
	
1	1.0f, 1.0f, 1.0f,
1	-1.0f, 1.0f,-1.0f,
1	-1.0f, 1.0f, 1.0f,
	
1	1.0f, 1.0f, 1.0f,
1	-1.0f, 1.0f, 1.0f,
	1.0f,-1.0f, 1.0f
};
*/
static GLfloat verticeData[] = {
	-1.0f,-1.0f,-1.0f, // triangle 1 : begin
	-1.0f,-1.0f, 1.0f,
	
	//-1.0f, 1.0f, 1.0f, // triangle 1 : end
	//1.0f, 1.0f,-1.0f, // triangle 2 : begin
	-1.0f,-1.0f,-1.0f,
	-1.0f, 1.0f,-1.0f, // triangle 2 : end

	//-1.0f, 1.0f,-1.0f, // triangle 2 : end

	//1.0f,-1.0f, 1.0f,

	//1.0f,-1.0f, 1.0f,
	//-1.0f,-1.0f,-1.0f,

	-1.0f,-1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,

	1.0f,-1.0f,-1.0f,
	1.0f, 1.0f,-1.0f,
	
	-1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f,-1.0f,

	1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f, 1.0f,

	-1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f,-1.0f,

	-1.0f, 1.0f, 1.0f,
	-1.0f,-1.0f, 1.0f,

	1.0f,-1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,

	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f,-1.0f,

	1.0f, 1.0f,-1.0f,
	-1.0f, 1.0f,-1.0f,

	-1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,

	1.0f,-1.0f,-1.0f,
	1.0f,-1.0f, 1.0f
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

static glm::vec3 caculateNormal(const glm::vec3 &v1, const glm::vec3 &v2, const glm::vec3 &v3)
{
	glm::vec3 V1 = v2 - v1;
	glm::vec3 V2 = v3 - v1;

	glm::vec3 surfaceNormal;

	surfaceNormal.x = V1.y * V2.z - (V1.z - V1.y);
	surfaceNormal.y = -((V2.z * V1.x) - (V2.x * V1.z));
	surfaceNormal.z = (V1.x*V2.y) - (V1.y*V2.x);

	return surfaceNormal;
}

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

void renderData::buildNormalBuffers(glm::vec3* inputData, size_t numOfEntries)
{

	GLfloat*   pVerticeData = verticeData;
	
	glm::vec3* pTemp = inputData;
	glm::vec3  v1, v2, v3;
	glm::vec3  surfaceNormal;

	for (int i = 0; i < numOfEntries; i+=3)
	{
		v1.x = *pVerticeData;
		v1.y = *(++pVerticeData);
		v1.z = *(++pVerticeData);
		v2.x = *(++pVerticeData);
		v2.y = *(++pVerticeData);
		v2.z = *(++pVerticeData);
		v3.x = *(++pVerticeData);
		v3.y = *(++pVerticeData);
		v3.z = *(++pVerticeData);
		
		++pVerticeData;

		surfaceNormal = caculateNormal(v1, v2, v3);

		memcpy((void*)pTemp, (void*)&surfaceNormal, sizeof(float) * 3);

		//glnormal

		pTemp++;
	}

}

size_t renderData::getNumOfEntriesVerticeData(void)
{
	return getSizeVerticeDataGfx() / (sizeof(float) * 3);
}

size_t renderData::getNumOfEntriesColorData(void)
{
	return getSizeColorDataGfx() / (sizeof(float) * 3);
}