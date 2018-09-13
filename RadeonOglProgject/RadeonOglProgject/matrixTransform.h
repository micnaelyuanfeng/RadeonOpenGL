#ifndef _TRANSLATE_H_
#define _TRANSLATE_H_

enum trasnlateDirection
{
	TRANSLATE_X = 0x0,
	TRANSLATE_Y = 0x1,
	TRANSLATE_Z = 0x2
};

enum scaleDirection
{
	SCALE_UP = 0x0,
	SCALE_DOWN = 0x1
};

enum rotateDirection
{
	ROTATE_CW = 0x5,
	ROTATE_CCW = 0x6
};

class matrixTransformManagement
{
public:
	matrixTransformManagement();
	~matrixTransformManagement();

	glm::vec3* createTranslateVector(float offset, enum trasnlateDirection axisType);
	glm::vec3* createScaleVector(float scaleFator, enum scaleDirection scaleDirection);
	glm::vec3* createRotateVector(float degree, enum rotateDirection rotateDirection);
	
	void       destroyTranslateVetor(glm::vec3* pThisVector);
	void       destroyRotateVetor(glm::vec3* pThisVector);
	void       destroyScaleVetor(glm::vec3* pThisVector);


private:
};

#endif