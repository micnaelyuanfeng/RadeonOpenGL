#pragma once

#ifndef _BUFFER_MGR_
#define _BUFFER_MGR_

class renderData;

class bufferShaderManager
{
public:
	bufferShaderManager();
	~bufferShaderManager();

	void createVaoBuffer(enum typeId type);
	void createVboBuffer(enum typeId type);
	void destroyVaoBuffer(enum typeId type);
	void destroyVboBuffer(enum typeId type);

	void enableVaoBuffer(enum typeId type);
	void enableVboBuffer(enum typeId type);

	void setShaderMemMgr(void* pMgr) { bufferShaderMgr = (bufferShaderManager*)pMgr; }
	void setRenderDataMgr(void* pMgr) { renderDataMgr = (renderData*)pMgr; }
private:
	bufferShaderManager* bufferShaderMgr;
 	renderData*          renderDataMgr;
};

#endif