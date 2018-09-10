#include "GL/glew.h" 
#include "GL/glut.h"
#include "GLM/glm.hpp"
#include "locationData.h"
#include "bufferMgr.h"
#include "shaderMgr.h"

const char* FRAGMENT_SHADER =
"#version 330 core\n"
"in vec3 fragmentColor;\n"
"out vec3 color;\n"
"uniform sampler2D myTextureSampler;\n"
"void main()\n"
"{\n"
"color = fragmentColor;\n"
"}\n";


const char* VERTEX_SHADER =
"#version 330 core\n"
"layout(location = 0) in vec3 vertexPosition_modelspace;\n"
"layout(location = 1) in vec3 vertexColor;\n"
"uniform mat4 MVP;\n"
"out vec3 fragmentColor;\n"
"void main(){\n"
"gl_Position =  MVP * vec4(vertexPosition_modelspace,1);\n"
"fragmentColor = vertexColor;\n"
"}\n";

shaderManager::shaderManager():fileMgr(NULL), shaderIdArray(NULL)
{

}

shaderManager::~shaderManager()
{

}

void shaderManager::shaderInit()
{
	shaderIdArray = (GLuint*) new GLuint[SHADER_NUM_MAX];
	pProgramId     = (GLuint*) new GLuint;
}

void shaderManager::buildVertexShader(enum shaderId vertexShaderId)
{
	shaderIdArray[vertexShaderId] = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(shaderIdArray[vertexShaderId], 1, &VERTEX_SHADER, NULL);
	glCompileShader(shaderIdArray[vertexShaderId]);
}

void shaderManager::buildFragmentShader(enum shaderId fragmentShaderId)
{
	shaderIdArray[fragmentShaderId] = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(shaderIdArray[fragmentShaderId], 1, &FRAGMENT_SHADER, NULL);
	glCompileShader(shaderIdArray[fragmentShaderId]);
}

void shaderManager::buildProgramTwo(enum shaderId vertexShaderId, enum shaderId fragmentShaderId)
{
	*pProgramId = glCreateProgram();

	glAttachShader(*pProgramId, shaderIdArray[vertexShaderId]);
	glAttachShader(*pProgramId, shaderIdArray[fragmentShaderId]);
	glLinkProgram(*pProgramId);
}

void shaderManager::buildProgramMultiple(void* vertexShaderIds, void* fragmentShaderIds)
{
	
}

void shaderManager::enableProgram()
{
	glUseProgram(*pProgramId);
}

void shaderManager::linkProgram(enum shaderId shaderId)
{

}