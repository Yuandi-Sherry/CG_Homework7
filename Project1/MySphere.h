#pragma once
#include <vector>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "HomeworkBase.h"
using namespace std;
class MySphere
{
public:
	MySphere(const int & shadePro);
	MySphere();
	~MySphere();
	vector<float> getVBOarr();
	void display();
	void displayEarth();
	void generateSphere(const float & radius, const string & name);
	void setPro(const int & );
	void displaySphere();
private:
	GLuint VAO, VBO, EBO;
	vector<float> vertices;
	vector<int> indices;
	glm::vec3 cameraPos = glm::vec3(0.0f, 4.0f, -30.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, -0.2f, 1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	void parseShaders();
	int shaderProgram;
	GLuint createTexture(char const *filePath);
	void setTexture(char const *filePath);
	
	void parseSphereShaders();
	string name;
	float radius;
};
