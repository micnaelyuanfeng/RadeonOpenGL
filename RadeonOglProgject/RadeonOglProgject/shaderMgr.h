#pragma once

#ifndef _SHADER_MGR_H_
#define _SHADER_MGR_H_

class fileManager;

class shaderManager
{
public:
	shaderManager();
	~shaderManager();

	void shaderInit();
	void buildFragmentShader(enum shaderId fragmentShaderId);
	void buildVertexShader(enum shaderId vertexShaderId);
	void enableProgram(void);
    
	void buildProgramTwo(enum shaderId vertexShaderId, enum shaderId fragmentShaderId);
	void buildProgramMultiple(void* vertexShaderIds, void* fragmentShaderIds);

	GLuint getProgramId(void) { return *pProgramId; }
private:
	void linkProgram(enum shaderId shaderId);
	
	fileManager* fileMgr;
	GLuint* shaderIdArray;
	GLuint* pProgramId;
};

#endif