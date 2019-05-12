#include "Shader.h"

Shader::Shader(const string & vertexShaderFile, const string & fragmentShaderFile)
{
	compileShader(vertexShader, vertexShaderFile, GL_VERTEX_SHADER);
	compileShader(fragmentShader, fragmentShaderFile, GL_FRAGMENT_SHADER);
}



Shader::~Shader()
{
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::compileShader(unsigned int & shader, const string & filename, const int & shaderType) {
	shader = glCreateShader(shaderType);
	string shaderSource;
	if (readFile(filename.c_str(), shaderSource)) {
		const GLchar* p[1];
		p[0] = shaderSource.c_str();
		GLint Lengths[1];
		Lengths[0] = strlen(shaderSource.c_str());
		glShaderSource(shader, 1, p, Lengths);
		glCompileShader(shader);
		checkCompile(shader);
	}
	else {
		cout << "Fail to read shader file" << endl;
	}
}

/*
 * ÎÄ¼þ¶ÁÈ¡
 */
bool Shader::readFile(const string & fileName, string & content) {
	ifstream inFile(fileName);
	if (!inFile) {
		cout << "Fail to read " << fileName.c_str() << endl;
		return false;
	}
	else {
		string line;
		while (getline(inFile, line)) {
			content.append(line);
			content.append("\n");
		}
	}
	return true;
}

void Shader::checkCompile(const int & shader) {
	int success;
	char info[512];	
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		cout << "COMPILE ERROR: " << endl;
		glGetShaderInfoLog(shader, 512, NULL, info);
		cout << info << endl;
	}
}