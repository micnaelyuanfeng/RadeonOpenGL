#pragma once
#ifndef _LOCATION_DATA_H_
#define _LOCATION_DATA_H_

enum typeId
{
	VAO              = 0x0,
	VBO_GFX          = 0x1,
	VBO_MICRO_ENGINE = 0x2,
};

enum shaderId
{
	SHADER_GFX_VERTEXT           = 0x0,
	SHADER_GFX_FRAGMENT          = 0x1,
	SHADER_MICRO_ENGINE_VERTEXT  = 0x2,
	SHADER_MICRO_ENGINE_FRAGMENT = 0x3,
	SHADER_NUM_MAX
};

struct mvpMatrix
{
	glm::mat4 projection;
	glm::mat4 view;
	glm::mat4 model;
	glm::mat4 MVP;
};

class bufferShaderManager;

class renderData
{
public:
	renderData();
	~renderData();

	GLfloat* getVerticeDataMicroEngine(void) { return microEngineVerticeData;}
	GLfloat* getVerticesDataGfx(void)		 { return gfxCardVerticeData; }
	GLfloat* getColorDataGfx(void)			 { return gfxColorData; }
	GLfloat* getColorDataMicroEngine(void)   { return microEngineColorData; }
	GLfloat* getUvData(void)                 { return uvData; }

	struct mvpMatrix* getMvpGfx(GLuint index) { return &mvpGfx[index]; }
	struct mvpMatrix* getMvpMicroEngine(GLuint index) { return &mvpMicroEngine[index]; }

	GLuint*   getVertexArrayId(GLuint index) { return &vertexArrayId[index]; }
	GLuint*   getGfxCardColorBufferId(GLuint index) { return &gfxCardColorBufferId[index]; }
	GLuint*   getMicroEngineColorBufferId(GLuint index) { return &microEngineColorBufferId[index]; }
	GLuint*   getGfxCardBufferId(GLuint index) { return &gfxCardBufferId[index]; }
	GLuint*   getMircoEngineBufferId(GLuint index) { return &microEngineBufferId[index]; }
	GLuint*   getProgramId(GLuint index) { return &programId[index]; }

	void setShaderMemMgr(void* pMgr) { bufferShaderMgr = (bufferShaderManager*)pMgr; }
	void setRenderDataMgr(void* pMgr) { renderDataMgr = (renderData*)pMgr; }

	size_t    getSizeVerticeDataGfx(void);
	size_t    getSizeColorDataGfx(void);

	void      renderDataInit(void);

private:
	//GLfloat* verticeData;
	GLuint*  vertexArrayId;

	GLuint*  gfxCardBufferId;
	GLuint*  microEngineBufferId;

	GLuint*  gfxCardColorBufferId;
	GLuint*  microEngineColorBufferId;

	GLuint*  programId;

	GLfloat* gfxCardVerticeData;
	GLfloat* microEngineVerticeData;
	GLfloat* gfxColorData;
	GLfloat* microEngineColorData;
	GLfloat* uvData;

	struct mvpMatrix* mvpGfx;
	struct mvpMatrix* mvpMicroEngine;

	bufferShaderManager* bufferShaderMgr;
	renderData*          renderDataMgr;

};


#endif