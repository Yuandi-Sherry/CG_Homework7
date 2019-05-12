#include "ShaderProgram.h"
ShaderProgram::ShaderProgram(const int & vertexShader, const int & fragmentShader)
{
	setShaders(vertexShader, fragmentShader);
}

ShaderProgram::~ShaderProgram()
{
}

void ShaderProgram::useProgram() {
	glUseProgram(shaderProgram);
}

void ShaderProgram::checkCompile(const int & shader) {
	int success;
	char info[512];
	glGetProgramiv(shader, GL_LINK_STATUS, &success);
	if (!success) {
		cout << "COMPILE ERROR: " << endl;
		glGetProgramInfoLog(shader, 512, NULL, info);
		cout << info << endl;
	}
}

void ShaderProgram::setShaders(const int & vertexShader, const int & fragmentShader) {
	shaderProgram = glCreateProgram();
	// Á´½Ó
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	checkCompile(shaderProgram);

}