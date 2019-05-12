#pragma once
#ifndef HOMEWORK_6_
#include "Camera.h"
#include "HomeworkBase.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stb_image.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
class Homework6 : public HomeworkBase
{
public:
	Homework6();
	Homework6(const string & vertexShaderFile, const string & fragmentShaderFile);
	~Homework6();
	void init(const string & vertexShaderFile, const string & fragmentShaderFile);
	void displayController();
	void imGuiSetting();
	void imGuiMenuSetting();
	// keyboards & mouse
	void processInput(GLFWwindow * window);
	void mouseCallback(GLFWwindow* window, double xpos, double ypos);
	
private:
	// control
	bool homework6;

	// cube
	float cubeVerticesColor[216] = {
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

	float cubeVertices[216] = {
		-10.0f, -10.0f, -10.0f,  0.0f,  0.0f, -1.0f,
		 10.0f, -10.0f, -10.0f,  0.0f,  0.0f, -1.0f,
		 10.0f,  10.0f, -10.0f,  0.0f,  0.0f, -1.0f,
		 10.0f,  10.0f, -10.0f,  0.0f,  0.0f, -1.0f,
		-10.0f,  10.0f, -10.0f,  0.0f,  0.0f, -1.0f,
		-10.0f, -10.0f, -10.0f,  0.0f,  0.0f, -1.0f,

		-10.0f, -10.0f,  10.0f,  0.0f,  0.0f, 1.0f,
		 10.0f, -10.0f,  10.0f,  0.0f,  0.0f, 1.0f,
		 10.0f,  10.0f,  10.0f,  0.0f,  0.0f, 1.0f,
		 10.0f,  10.0f,  10.0f,  0.0f,  0.0f, 1.0f,
		-10.0f,  10.0f,  10.0f,  0.0f,  0.0f, 1.0f,
		-10.0f, -10.0f,  10.0f,  0.0f,  0.0f, 1.0f,

		-10.0f,  10.0f,  10.0f, -1.0f,  0.0f,  0.0f,
		-10.0f,  10.0f, -10.0f, -1.0f,  0.0f,  0.0f,
		-10.0f, -10.0f, -10.0f, -1.0f,  0.0f,  0.0f,
		-10.0f, -10.0f, -10.0f, -1.0f,  0.0f,  0.0f,
		-10.0f, -10.0f,  10.0f, -1.0f,  0.0f,  0.0f,
		-10.0f,  10.0f,  10.0f, -1.0f,  0.0f,  0.0f,

		 10.0f,  10.0f,  10.0f,  1.0f,  0.0f,  0.0f,
		 10.0f,  10.0f, -10.0f,  1.0f,  0.0f,  0.0f,
		 10.0f, -10.0f, -10.0f,  1.0f,  0.0f,  0.0f,
		 10.0f, -10.0f, -10.0f,  1.0f,  0.0f,  0.0f,
		 10.0f, -10.0f,  10.0f,  1.0f,  0.0f,  0.0f,
		 10.0f,  10.0f,  10.0f,  1.0f,  0.0f,  0.0f,

		-10.0f, -10.0f, -10.0f,  0.0f, -1.0f,  0.0f,
		 10.0f, -10.0f, -10.0f,  0.0f, -1.0f,  0.0f,
		 10.0f, -10.0f,  10.0f,  0.0f, -1.0f,  0.0f,
		 10.0f, -10.0f,  10.0f,  0.0f, -1.0f,  0.0f,
		-10.0f, -10.0f,  10.0f,  0.0f, -1.0f,  0.0f,
		-10.0f, -10.0f, -10.0f,  0.0f, -1.0f,  0.0f,

		-10.0f,  10.0f, -10.0f,  0.0f,  1.0f,  0.0f,
		 10.0f,  10.0f, -10.0f,  0.0f,  1.0f,  0.0f,
		 10.0f,  10.0f,  10.0f,  0.0f,  1.0f,  0.0f,
		 10.0f,  10.0f,  10.0f,  0.0f,  1.0f,  0.0f,
		-10.0f,  10.0f,  10.0f,  0.0f,  1.0f,  0.0f,
		-10.0f,  10.0f, -10.0f,  0.0f,  1.0f,  0.0f
	};
	// init position
	float x, y, z;
	unsigned int VBO;
	unsigned int VAO; // 顶点数组对象 
	// light source
	unsigned int lightVAO;
	glm::vec3 lightPos; // 光源在场景的世界空间坐标中的位置

	// int
	void initVars();
	
	void setCubeVAOVBO();
	void setLightSourceVAO();
	
	// show
	ShaderProgram lightSource;
	unsigned int lightSourceID;
	ShaderProgram phongShading;
	ShaderProgram gouraudShading;
	void showLightSource();
	void showLightedCube();
	Camera camera;
	glm::vec3 viewPoint;
	/**
	 * 可调节参数
	 * Phong/Gourand
	 * 
	 */
	bool basic, bonus;
	int phong;
	// 光照颜色
	glm::vec3 lightColor;
	// ambient, diffuse, specular 因子
	float ambientFactor;
	float diffuseFactor;
	float specularFactor;
	int reflectionPara; // 反光参数
	glm::vec3 lastViewPoint;
	
};

#endif // !HOMEWORK_6_
