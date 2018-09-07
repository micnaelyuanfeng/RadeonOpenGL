#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <assert.h>
#include "GL/glew.h" //should above glut
#include "GL/glut.h"
#include "SDL/SDL.h"
#include "GLM/glm.hpp"
#include "GLM/gtc/matrix_transform.hpp"

using namespace std;

const char* VERTEXT11_SHADER =
"#version 330 core\n"
"layout(location = 0) in vec3 vertexPosition_modelspace;\n"
"void main()\n"
"{\n"
"	gl_Position.xyz = vertexPosition_modelspace;\n"
"	gl_Position.w   = 1.0;\n"
"}\n";

const char* FRAGMENT_SHADER =
"#version 330 core\n"
"in vec2 UV;\n"
"//in vec3 fragmentColor;\n"
"out vec3 color;\n"
"uniform sampler2D myTextureSampler;\n"
"void main()\n"
"{\n"
"color = texture(myTextureSampler, UV).rgb;\n"
"//color = vec3(UV,0);\n"
"//color = fragmentColor;\n"
"}\n";


const char* VERTEXT_SHADER =
"#version 330 core\n"
"layout(location = 0) in vec3 vertexPosition_modelspace;\n"
"//layout(location = 1) in vec3 vertexColor;\n"
"layout(location = 1) in vec2 vertexUV;\n"
"uniform mat4 MVP;\n"
"out vec2 UV;\n"
"//out vec3 fragmentColor;\n"
"void main(){\n"
"gl_Position =  MVP * vec4(vertexPosition_modelspace,1);\n"
"UV = vertexUV;\n"
"//fragmentColor = vertexColor;\n"
"}\n";
//linear interpolation is done by gfx card

using namespace std;

//3D data
//OpenGL internel data type
//In defeult OpenGL space, there is no matrixes defined
// -1.0 to 1.0 for x, y, z
//Normal way
GLfloat vertices[] = {  -1.0f,-1.0f,-1.0f, // triangle 1 : begin
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
						-1.0f,-1.0f,-1.0f,
						-1.0f,-1.0f,-1.0f,
						-1.0f, 1.0f, 1.0f,
						-1.0f, 1.0f,-1.0f,
						 1.0f,-1.0f, 1.0f,
						-1.0f,-1.0f, 1.0f,
						-1.0f,-1.0f,-1.0f,
						-1.0f, 1.0f, 1.0f,
						-1.0f,-1.0f, 1.0f,
						 1.0f,-1.0f, 1.0f,
						 1.0f, 1.0f, 1.0f,
						 1.0f,-1.0f,-1.0f,
						 1.0f, 1.0f,-1.0f,
						 1.0f,-1.0f,-1.0f,
						 1.0f, 1.0f, 1.0f,
						 1.0f,-1.0f, 1.0f,
						 1.0f, 1.0f, 1.0f,
						 1.0f, 1.0f,-1.0f,
						-1.0f, 1.0f,-1.0f,
						 1.0f, 1.0f, 1.0f,
						-1.0f, 1.0f,-1.0f,
						-1.0f, 1.0f, 1.0f,
						 1.0f, 1.0f, 1.0f,
						-1.0f, 1.0f, 1.0f,
						 1.0f,-1.0f, 1.0f
};
//Color = RGB channels     R      G    B
static const GLfloat colorBufferData[] = {
						1.0f,  0.0f,  0.0f,
						1.0f,  0.0f,  0.0f,
						1.0f,  0.0f,  0.0f,
						0.822f,  0.569f,  0.201f,
						0.435f,  0.602f,  0.223f,
						0.310f,  0.747f,  0.185f,
						0.597f,  0.770f,  0.761f,
						0.559f,  0.436f,  0.730f,
						0.359f,  0.583f,  0.152f,
						0.483f,  0.596f,  0.789f,
						0.559f,  0.861f,  0.639f,
						0.195f,  0.548f,  0.859f,
						0.014f,  0.184f,  0.576f,
						0.771f,  0.328f,  0.970f,
						0.406f,  0.615f,  0.116f,
						0.676f,  0.977f,  0.133f,
						0.971f,  0.572f,  0.833f,
						0.140f,  0.616f,  0.489f,
						0.997f,  0.513f,  0.064f,
						0.945f,  0.719f,  0.592f,
						0.543f,  0.021f,  0.978f,
						0.279f,  0.317f,  0.505f,
						0.167f,  0.620f,  0.077f,
						0.347f,  0.857f,  0.137f,
						0.055f,  0.953f,  0.042f,
						0.714f,  0.505f,  0.345f,
						0.783f,  0.290f,  0.734f,
						0.722f,  0.645f,  0.174f,
						0.302f,  0.455f,  0.848f,
						0.225f,  0.587f,  0.040f,
						0.517f,  0.713f,  0.338f,
						0.053f,  0.959f,  0.120f,
						0.393f,  0.621f,  0.362f,
						0.673f,  0.211f,  0.457f,
						0.820f,  0.883f,  0.371f,
						0.982f,  0.099f,  0.879f
};

static const GLfloat uvBufferData[] = {
	0.000059f, 1.0f - 0.000004f,
	0.000103f, 1.0f - 0.336048f,
	0.335973f, 1.0f - 0.335903f,
	1.000023f, 1.0f - 0.000013f,
	0.667979f, 1.0f - 0.335851f,
	0.999958f, 1.0f - 0.336064f,
	0.667979f, 1.0f - 0.335851f,
	0.336024f, 1.0f - 0.671877f,
	0.667969f, 1.0f - 0.671889f,
	1.000023f, 1.0f - 0.000013f,
	0.668104f, 1.0f - 0.000013f,
	0.667979f, 1.0f - 0.335851f,
	0.000059f, 1.0f - 0.000004f,
	0.335973f, 1.0f - 0.335903f,
	0.336098f, 1.0f - 0.000071f,
	0.667979f, 1.0f - 0.335851f,
	0.335973f, 1.0f - 0.335903f,
	0.336024f, 1.0f - 0.671877f,
	1.000004f, 1.0f - 0.671847f,
	0.999958f, 1.0f - 0.336064f,
	0.667979f, 1.0f - 0.335851f,
	0.668104f, 1.0f - 0.000013f,
	0.335973f, 1.0f - 0.335903f,
	0.667979f, 1.0f - 0.335851f,
	0.335973f, 1.0f - 0.335903f,
	0.668104f, 1.0f - 0.000013f,
	0.336098f, 1.0f - 0.000071f,
	0.000103f, 1.0f - 0.336048f,
	0.000004f, 1.0f - 0.671870f,
	0.336024f, 1.0f - 0.671877f,
	0.000103f, 1.0f - 0.336048f,
	0.336024f, 1.0f - 0.671877f,
	0.335973f, 1.0f - 0.335903f,
	0.667969f, 1.0f - 0.671889f,
	1.000004f, 1.0f - 0.671847f,
	0.667979f, 1.0f - 0.335851f,
};

GLuint VBOID;       //VBO1
GLuint colorBuffer; //VBO2
GLuint uvBuffer;     //VBO3
GLuint matrixID;

float       degree          = 0;
float       scale           = 1.0;
bool        expandDirection = false;
const float scale_distance  = 0.05;

glm::mat4 projection;
glm::mat4 view;
glm::mat4 model;
glm::mat4 MVP;

struct verticeCCoordinates
{
	float x;
	float y;
	float z;
};

string vertextArray[100];
string indexArray[100];
string vertextData[200];

int vindex = 0;
int iindex = 0;

void readFile()
{
	string line;

	ifstream thisFile("F:\\Projects\\imgs\\amd1.obj");

	if (!thisFile.is_open())
	{
		cout << "Error" << endl;
	}

	while (getline(thisFile, line))
	{
		if (line.at(0) == 'f' || (line.at(0) == 'v' && line.at(1) != 'n'))
		{
			if (line.at(0) == 'f')
			{
				vertextArray[vindex] = line;
				vindex++;
			}
			if (line.at(0) == 'v')
			{
				indexArray[iindex] = line;
				iindex++;
			}
		}
	}

	for (int i = 0; i < vindex; i++)
	{
		cout << vertextArray[i] << endl;
		string parsedString;
		int j,k, w, z;
		sscanf((char*)vertextArray[i].c_str(), "f %d//%*d %d//%*d %d//%*d %d//%*d", &j, &k, &w, &z);
		cout << j << " "<< k <<" "<< w <<" "<< z << endl;
	}

	for (int i = 0; i < iindex; i++)
	{
		cout << indexArray[i] << endl;
	}



	thisFile.close();
}

GLuint loadBMP(const char* imagePath)
{
	unsigned char header[54];
	unsigned int dataPos;
	unsigned int imageSize;
	unsigned int width, height;
	// Actual RGB data
	unsigned char * data;

	// Open the file
	FILE* file = fopen(imagePath, "rb");

	if (file == NULL)
	{
		assert(0);
	}

	if (fread(header, 1, 54, file) != 54) {
		printf("Not a correct BMP file\n");
		fclose(file);
		return 0;
	}
	// A BMP files always begins with "BM"
	if (header[0] != 'B' || header[1] != 'M') {
		printf("Not a correct BMP file\n");
		fclose(file);
		return 0;
	}
	// Make sure this is a 24bpp file
	if (*(int*)&(header[0x1E]) != 0) { printf("Not a correct BMP file\n");    fclose(file); return 0; }
	if (*(int*)&(header[0x1C]) != 24) { printf("Not a correct BMP file\n");    fclose(file); return 0; }

	// Read the information about the image
	dataPos = *(int*)&(header[0x0A]);
	imageSize = *(int*)&(header[0x22]);
	width = *(int*)&(header[0x12]);
	height = *(int*)&(header[0x16]);

	// Some BMP files are misformatted, guess missing information
	if (imageSize == 0)    imageSize = width * height * 3; // 3 : one byte for each Red, Green and Blue component
	if (dataPos == 0)      dataPos = 54; // The BMP header is done that way

	// Create a buffer
	data = new unsigned char[imageSize];

	// Read the actual data from the file into the buffer
	fread(data, 1, imageSize, file);

	// Everything is in memory now, the file can be closed.
	fclose(file);

	GLuint textureId;

	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);

	// Give the image to OpenGL
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

	//delete[] data;

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	return textureId;
}

void display()
{
	

	glm::vec3 unitVectorX(1.0f, 0.0f, 0.0f);
	glm::vec3 unitVectorY(0.0f, 1.0f, 0.0f);
	glm::vec3 unitVectorZ(0.0f, 0.0f, 1.0f);
	glm::vec3 scaleMatrix(scale, scale, scale);
	//
	model = glm::rotate(glm::mat4(1.0),degree, unitVectorY) * glm::scale(glm::mat4(1.0), scaleMatrix);

	MVP = projection * view * model;

	glUniformMatrix4fv(matrixID, 1, GL_FALSE, &MVP[0][0]);

	degree += 0.00005;

	//if (expandDirection == false)
	//{
		//scale -= 0.00001;
	//}
	//else
	//{
		//scale += 0.00001;
	//}
	

	if (degree > 360)
	{
		degree = 0.0;
	}

	//if (scale >= 1.5)
	//{
		//expandDirection = false;
	//}
	//else if (scale <= 1.0)
	//{
		//expandDirection = true;
	//}
	//For each frame = reset background color defined by glClearColor | depth value
	//reset for redraw                need to add this if using depth information
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Start Drawing
	//Tell openGl read vertices data from an array
	glEnableVertexAttribArray(0);
	//glEnableClientState(GL_COLOR_ARRAY);

	//new solution to draw using data in gfx buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBOID); //activate buffer


	//Tell openGL structure of array = how to parse the data
	// 3 = 3D; 2 = 2D 
	// e.g each 3 value in this array represents a vertices
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);// 0 is starting address of the buffer
	//glColorPointer(3, GL_FLOAT,  6 * sizeof(GLfloat), (GLvoid*)(sizeof(GLfloat) * 3));
	//Draw shape type
	//Linear interpolation and restariztion
	
	//glEnableVertexAttribArray(1);
	//glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glDrawArrays(GL_TRIANGLES, 0, 12 * 3); //send commands to gfx card
	//glDrawArrays(GL_TRIANGLES, 1, 3);
	//glDrawArrays(GL_TRIANGLES, 2, 3);

	glDisableVertexAttribArray(0);

	int error = glGetError();

	if (error != 0)
	{
		cout<<"error";
	}
	//glDisableClientState(GL_VERTEX_ARRAY);
	//glDisableClientState(GL_COLOR_ARRAY);

}

void reshape(int w, int h)
{

}

void initOpenGL()
{
	//set background color only
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	readFile();
	//Tell ogl use depth information
	//ogl will do depth test
	glEnable(GL_DEPTH_TEST);//enable to use depth information, if two objs overlap
	glDepthFunc(GL_LEQUAL); //tell opengl how to do test

	//Initialize all extensions which allow to create buffers on gfx card
	glewInit();

	//copy data to gfx card
	/*
		1. ask gfx for a piece of memory to put data which required for later rendering
	*/
	GLuint VertextArrayId;
	glGenVertexArrays(1, &VertextArrayId);
	glBindVertexArray(VertextArrayId);
	//In case of many triangles to draw, copying data hurt performance,
	//then use buffer and just copy once
	// num of buffer and handle
	glGenBuffers(1, &VBOID);
	glBindBuffer(GL_ARRAY_BUFFER, VBOID);                     //not change very often
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//glGenBuffers(1, &colorBuffer);
	//glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(colorBufferData), colorBufferData, GL_STATIC_DRAW);

	//glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &uvBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(uvBufferData), uvBufferData, GL_STATIC_DRAW);

	cout << sizeof(uvBufferData) << endl;
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//unbined buffer
	//glBindBuffer(GL_ARRAY_BUFFER, 0);

	//load shader
	GLint  result = GL_FALSE;
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

	int InfoLogLength = 0;

	glShaderSource(VertexShaderID, 1, &VERTEXT_SHADER, NULL);
	glCompileShader(VertexShaderID);

	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &result);
	assert(result == GL_TRUE);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);

	result = GL_FALSE;
	glShaderSource(FragmentShaderId, 1, &FRAGMENT_SHADER, NULL);
	glCompileShader(FragmentShaderId);

	glGetShaderiv(FragmentShaderId, GL_COMPILE_STATUS, &result);
	assert(result == GL_TRUE);
	glGetShaderiv(FragmentShaderId, GL_INFO_LOG_LENGTH, &InfoLogLength);

	GLuint programID = glCreateProgram();

	glAttachShader(programID, VertexShaderID);
	glAttachShader(programID, FragmentShaderId);
	//glBindAttribLocation(programID, 0, "vertexPosition_modelspace");
	//glBindAttribLocation(programID, 1, "vertexUV");
	glLinkProgram(programID);

	matrixID = glGetUniformLocation(programID, "MVP");

	//keep constant
	projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.01f, 100.0f);


	view = glm::lookAt(
		glm::vec3(4, 3, 3), // Camera is at (4,3,3), in World Space
		glm::vec3(0, 0, 0), // and looks at the origin
		glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
	);

	//Scale, translate, and rotate
	model = glm::mat4(1.0f);

	MVP = projection * view * model;

	GLuint texture = loadBMP("F:\\Projects\\imgs\\amd.bmp");
	GLuint textureId = glGetUniformLocation(programID, "myTextureSampler");

	glUseProgram(programID);
	glUniformMatrix4fv(matrixID, 1, GL_FALSE, &MVP[0][0]);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(textureId, 0);
}

void idle()
{
	glutPostRedisplay();
}

int main(int argc, char **argv)
{
	SDL_Window*   mainWindow;
	SDL_GLContext mainContext;
	SDL_Event     windowEvents = { 0 };

	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);


	bool running = true;

	mainWindow = SDL_CreateWindow("Gfx Render", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, 640, 480,
		SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

	if (mainWindow == NULL)
	{
		SDL_Quit();

		return 1;
	}

	/* Create our opengl context and attach it to our window */
	mainContext = SDL_GL_CreateContext(mainWindow);

	initOpenGL();

	while (running)
	{
		while (SDL_PollEvent(&windowEvents))
		{
			if (windowEvents.type == SDL_QUIT)
			{
				running = false;
			}
			else if (windowEvents.type == SDL_KEYDOWN)
			{
			}
			else if (windowEvents.type == SDL_MOUSEBUTTONDOWN)
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

		display();

		SDL_GL_SwapWindow(mainWindow);
	}

	return 0;
}


//perspective view in ogl
/*
	1. position of camera
	2. the way to laook at the world
	3. Near clip plane = closest thing can see
	4. Far clip plane  = farest thing can see
*/
