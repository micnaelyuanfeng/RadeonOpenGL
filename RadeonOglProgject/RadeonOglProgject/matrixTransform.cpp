#include "GLM/glm.hpp"
#include "matrixTransform.h"

matrixTransformManagement::matrixTransformManagement()
{

}

matrixTransformManagement::~matrixTransformManagement()
{

}

glm::vec3* matrixTransformManagement::createTranslateVector(float offset, enum trasnlateDirection axisType)
{
	glm::vec3* pThisTranslateVector = NULL;

	switch (axisType)
	{
	case TRANSLATE_X:
		pThisTranslateVector = new glm::vec3(offset, 0.0f, 0.0f);
		break;
	case TRANSLATE_Y:
		pThisTranslateVector = new glm::vec3(0.0f, offset, 0.0f);
		break;
	case TRANSLATE_Z:
		pThisTranslateVector = new glm::vec3(0.0f, 0.0f, offset);
		break;
	default:
		pThisTranslateVector = new glm::vec3(0.0f, 0.0f, 0.0f); //no Translation
	}

	return pThisTranslateVector;
}


glm::vec3* matrixTransformManagement::createScaleVector(float scaleFator, enum scaleDirection scaleDirection)
{
	glm::vec3* pThisScaleVector = NULL;

	switch (scaleDirection)
	{
	case SCALE_UP:
		pThisScaleVector = new glm::vec3(scaleFator, scaleFator, scaleFator);
		break;
	
	case SCALE_DOWN:
		pThisScaleVector = new glm::vec3(scaleFator, scaleFator, scaleFator);
		break;
	}

	return pThisScaleVector;
}

glm::vec3* matrixTransformManagement::createRotateVector(float degree, enum rotateDirection rotateDirection)
{
	glm::vec3* pThisScaleVector = NULL;

	switch (rotateDirection)
	{
	case ROTATE_CW:
		pThisScaleVector = new glm::vec3(degree, degree, degree);
		break;

	case ROTATE_CCW:
		pThisScaleVector = new glm::vec3(degree, degree, degree);
		break;
	}

	return pThisScaleVector;
}


void matrixTransformManagement::destroyTranslateVetor(glm::vec3* pThisVector)
{
	delete pThisVector;
}


void matrixTransformManagement::destroyRotateVetor(glm::vec3* pThisVector)
{
	delete pThisVector;
}

void matrixTransformManagement::destroyScaleVetor(glm::vec3* pThisVector)
{
	delete pThisVector;
}