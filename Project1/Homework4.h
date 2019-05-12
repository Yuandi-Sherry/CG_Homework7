#pragma once
#ifndef _Homework_4_
#define _Homework_4_
#include "HomeworkBase.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "MySphere.h"
class Homework4 : public HomeworkBase
{
public:
	Homework4(const string & vertexShaderFile, const string & fragmentShaderFile);
	void drawCube(); // basic1:画一个立方体
	void generateSphere(const float & radius);
	void displaySphere();
	void displayController();;
	~Homework4();
	void imGuiSetting();
	void imGuiMenuSetting();
	void initVars();
	void parseSphereShaders();
	void setTexture(char const *filePath);
	GLuint createTexture(char const *filePath);
	void displayCosmos();
	void prepareCosmos();
	void processInput();
private:
	bool homework4;
	// basic part
	// the length of the cube
	float length = 1.0f;
	// initial position in world coordinate
	float transFactorX = 0.0f;
	float transFactorY = 0.0f;
	float transFactorZ = 0.0f;

	float cubeVertices [216] = {
		// red z = -2
		-1.0f, -1.0f, -1.0f,  1.0f, 0.0f, 0.0f,
		 1.0f, -1.0f, -1.0f,  1.0f, 0.0f, 0.0f,
		 1.0f,  1.0f, -1.0f,  1.0f, 0.0f, 0.0f,
		 1.0f,  1.0f, -1.0f,  1.0f, 0.0f, 0.0f,
		-1.0f,  1.0f, -1.0f,  1.0f, 0.0f, 0.0f,
		-1.0f, -1.0f, -1.0f,  1.0f, 0.0f, 0.0f,
		// purple z = 2
		-1.0f, -1.0f,  1.0f,  1.0f, 0.0f, 1.0f,
		 1.0f, -1.0f,  1.0f,  1.0f, 0.0f, 1.0f,
		 1.0f,  1.0f,  1.0f,  1.0f, 0.0f, 1.0f,
		 1.0f,  1.0f,  1.0f,  1.0f, 0.0f, 1.0f,
		-1.0f,  1.0f,  1.0f,  1.0f, 0.0f, 1.0f,
		-1.0f, -1.0f,  1.0f,  1.0f, 0.0f, 1.0f,
		// yellow z = 
		-1.0f,  1.0f,  1.0f,  1.0f, 1.0f, 0.0f,
		-1.0f,  1.0f, -1.0f,  1.0f, 1.0f, 0.0f,
		-1.0f, -1.0f, -1.0f,  1.0f, 1.0f, 0.0f,
		-1.0f, -1.0f, -1.0f,  1.0f, 1.0f, 0.0f,
		-1.0f, -1.0f,  1.0f,  1.0f, 1.0f, 0.0f,
		-1.0f,  1.0f,  1.0f,  1.0f, 1.0f, 0.0f,
		// blue z = 
		 1.0f,  1.0f,  1.0f,  0.0f, 0.0f, 1.0f,
		 1.0f,  1.0f, -1.0f,  0.0f, 0.0f, 1.0f,
		 1.0f, -1.0f, -1.0f,  0.0f, 0.0f, 1.0f,
		 1.0f, -1.0f, -1.0f,  0.0f, 0.0f, 1.0f,
		 1.0f, -1.0f,  1.0f,  0.0f, 0.0f, 1.0f,
		 1.0f,  1.0f,  1.0f,  0.0f, 0.0f, 1.0f,
		 // green
		-1.0f, -1.0f, -1.0f,  0.0f, 1.0f, 0.0f,
		 1.0f, -1.0f, -1.0f,  0.0f, 1.0f, 0.0f,
		 1.0f, -1.0f,  1.0f,  0.0f, 1.0f, 0.0f,
		 1.0f, -1.0f,  1.0f,  0.0f, 1.0f, 0.0f,
		-1.0f, -1.0f,  1.0f,  0.0f, 1.0f, 0.0f,
		-1.0f, -1.0f, -1.0f,  0.0f, 1.0f, 0.0f,
		// qing
		-1.0f,  1.0f, -1.0f,  0.0f, 1.0f, 1.0f,
		 1.0f,  1.0f, -1.0f,  0.0f, 1.0f, 1.0f,
		 1.0f,  1.0f,  1.0f,  0.0f, 1.0f, 1.0f,
		 1.0f,  1.0f,  1.0f,  0.0f, 1.0f, 1.0f,
		-1.0f,  1.0f,  1.0f,  0.0f, 1.0f, 1.0f,
		-1.0f,  1.0f, -1.0f,  0.0f, 1.0f, 1.0f
	};
	int shaderProgram;
	bool translation;
	float translateX;
	float translateY;
	float translateZ;
	bool rotation;
	bool scaling;
	float scalar;
	
	bool pro;
	// projec
	float pro_frov;
	float pro_near;
	float pro_far;

	// ortho
	float ort_left;
	float ort_right;
	float ort_bottom;
	float ort_top;
	float ort_near;
	float ort_far;
	
	// bonus part
	MySphere sun;
	MySphere earth;

	// camera
	// hm5 - 模拟摄像机
	glm::vec3 cameraPos;
	glm::vec3 cameraTarget;
	glm::vec3 cameraDirection;
	glm::vec3 up;
	glm::vec3 cameraRight;
	// 上轴
	glm::vec3 cameraUp;
	glm::vec3 cameraFront;
};



#endif // !_homework_4_
