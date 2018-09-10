#include "GL/glew.h" 
#include "GL/glut.h"
#include "GLM/glm.hpp"
#include "locationData.h"
#include "bufferMgr.h"

#include <iostream>

using namespace std;

bufferShaderManager::bufferShaderManager():bufferShaderMgr(NULL),renderDataMgr(NULL)
{

}

bufferShaderManager::~bufferShaderManager()
{
	bufferShaderMgr = NULL;
	renderDataMgr   = NULL;
}

void bufferShaderManager::createVaoBuffer(enum typeId type)
{
	GLuint* thisVaoId  = renderDataMgr->getVertexArrayId(type);

	glGenVertexArrays(1, thisVaoId);
	glBindVertexArray(*thisVaoId);

}

void bufferShaderManager::createVboBuffer(enum typeId type)
{
	GLuint* thisVboId;
	
	switch (type)
	{
	case VBO_GFX:
		thisVboId = renderDataMgr->getGfxCardBufferId(0);
		glGenBuffers(1, thisVboId);
		glBindBuffer(GL_ARRAY_BUFFER, *thisVboId);
		glBufferData(GL_ARRAY_BUFFER, renderDataMgr->getSizeVerticeDataGfx(), renderDataMgr->getVerticesDataGfx(), GL_STATIC_DRAW);

		glGenBuffers(1, renderDataMgr->getGfxCardColorBufferId(0));
		glBindBuffer(GL_ARRAY_BUFFER, *renderDataMgr->getGfxCardColorBufferId(0));
		glBufferData(GL_ARRAY_BUFFER, renderDataMgr->getSizeColorDataGfx(), renderDataMgr->getColorDataGfx(), GL_STATIC_DRAW);
		cout << "GFX card color buffer id: " << *renderDataMgr->getGfxCardColorBufferId(0) << endl;
		cout << "Color data size: " << renderDataMgr->getSizeColorDataGfx() << endl;
		break;
	case VBO_MICRO_ENGINE:
		thisVboId = renderDataMgr->getMircoEngineBufferId(1);
		glGenBuffers(1, thisVboId);
		glBindBuffer(GL_ARRAY_BUFFER, *thisVboId);
		glBufferData(GL_ARRAY_BUFFER, sizeof(thisVboId), thisVboId, GL_STATIC_DRAW);
		break;
	}
}

void bufferShaderManager::destroyVaoBuffer(enum typeId type)
{
	;
}

void bufferShaderManager::destroyVboBuffer(enum typeId type)
{
	;
}

void bufferShaderManager::enableVaoBuffer(enum typeId type)
{
	//glBindVertexArray(vertexArray);
}

void bufferShaderManager::enableVboBuffer(enum typeId type)
{
	//cout << "Enable vbo called" << endl;

	glEnableVertexAttribArray(0);
	//
	glBindBuffer(GL_ARRAY_BUFFER, *renderDataMgr->getGfxCardBufferId(0));
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, *renderDataMgr->getGfxCardColorBufferId(0));
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
}