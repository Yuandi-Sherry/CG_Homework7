#pragma once
#ifndef _shader_h_
#define _shader_h_
#include <string>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
using namespace std;
class Shader
{
public:
	Shader(const string & vertexShaderFile, const string & fragmentShaderFile);
	int getShader();
	~Shader();
	int getVertexShader() {
		return vertexShader;
	}
	int getFragmentShader() {
		return fragmentShader;
	}
private:
	void compileShader(unsigned int & shader, const string & filename, const int & shaderType);
	bool readFile(const string & fileName, string & content);
	void checkCompile(const int & shader);
	unsigned int vertexShader;
	unsigned int fragmentShader;
};
#endif
