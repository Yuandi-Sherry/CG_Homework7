#pragma once
#ifndef _shader_program_h_
#define _shader_program_h_
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <string>
#include "Shader.h"
using namespace std;
class ShaderProgram
{
public:
	ShaderProgram(const int & vShader, const int & fShader);
	ShaderProgram() {

	}
	~ShaderProgram();
	void checkCompile(const int & shaderProgram);
	unsigned int getShaderProgram() {
		return shaderProgram;
	}
	void useProgram();
	void setShaders(const int & vShader, const int & fShader);

private:
	unsigned int shaderProgram;

};
#endif // !ShaderProgram