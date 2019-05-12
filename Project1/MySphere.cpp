#include "MySphere.h"
#include <vector>
#include "tgaLoader.h"
using namespace std;
GLint SLICEY = 60;
GLint SLICEX = 60;
double PI = 3.14159265;
extern int windowWidth;
extern int windowHeight;
MySphere::MySphere(const int & shadePro)
{
	setPro(shadePro);
}

MySphere::MySphere()
{
}

MySphere::~MySphere()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void MySphere::setPro(const int & shadePro)
{
	this->shaderProgram = shadePro;
	cout << "shaderProgram" << shaderProgram << endl;
}

void MySphere::parseShaders() {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]), vertices.data(), GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 2, (GLvoid *)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 2, (GLvoid *)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 2, (GLvoid *)(sizeof(vertices[0])));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(indices[0]), indices.data(), GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}


void MySphere::display() {
	glDrawElements(GL_TRIANGLES, (GLsizei)(indices.size() * 3), GL_UNSIGNED_INT, 0);
}

void MySphere::generateSphere(const float &  radius, const string & name) {
	this->name = name;
	this->radius = radius;
	float stripe = PI / SLICEX;
	double offset = 0;
	vertices.push_back(0.0f);
	vertices.push_back(radius);
	vertices.push_back(0.0f);
	vertices.push_back(0.5f);
	vertices.push_back(1.0f);
	vertices.push_back(0.0f);
	int indexCounter = 1;
	int outerCounter = 0;

	for (float phi = stripe; phi <= PI; phi += stripe) {
		int innerCounter = 0;
		for (float theta = 0; theta <= 2 * PI; theta += stripe) {
			innerCounter++;
			float x = radius * cos(theta + offset) * sin(phi);
			float y = radius * cos(phi);
			float z = radius * sin(theta + offset) * sin(phi);
			vertices.push_back(x);
			vertices.push_back(y);
			vertices.push_back(z);
			// ?? 2 
			float u = theta / 2 / PI;
			float v = (cos(phi) + 1) / 2;
			vertices.push_back(u);
			vertices.push_back(v);
			vertices.push_back(0);

			if (theta != 0) {
				if (abs(phi - stripe) < 0.00001) { // 第一次
					indices.push_back(indexCounter - 1);
					indices.push_back(indexCounter);
					indices.push_back(0);
				}
				else { // 之后每次添加两个顶点
					indices.push_back(indexCounter - 1);
					indices.push_back(indexCounter);
					indices.push_back(indexCounter - outerCounter - 1);
					indices.push_back(indexCounter);
					indices.push_back(indexCounter - outerCounter - 1);
					indices.push_back(indexCounter - outerCounter);
				}
			}

			indexCounter++;

		}
		if (abs(phi - stripe) < 0.0001) {
			//vector<int>({ indexCounter - innerCounter, indexCounter - 1, 0 })
			indices.push_back(indexCounter - innerCounter);
			indices.push_back(indexCounter - 1);
			indices.push_back(0);
		}
		else {
			indices.push_back(indexCounter - innerCounter);
			indices.push_back(indexCounter - 1);
			indices.push_back(indexCounter - outerCounter - 1);
			indices.push_back(indexCounter - innerCounter);
			indices.push_back(indexCounter - outerCounter - innerCounter);
			indices.push_back(indexCounter - outerCounter - 1);
		}
		outerCounter = innerCounter;
		offset += stripe / 2;
	}
	for (int i = indexCounter - 1; i > indexCounter - outerCounter; --i) {
		indices.push_back(i);
		indices.push_back(i - 1);
		indices.push_back(indexCounter);

	}
	indices.push_back(indexCounter - 1);
	indices.push_back(indexCounter - outerCounter);
	indices.push_back(indexCounter);
	vertices.push_back(0);
	vertices.push_back(-radius);
	vertices.push_back(0);
	vertices.push_back(0.5f);
	vertices.push_back(0.0f);
	vertices.push_back(0.0f);
	parseSphereShaders();
}

GLuint MySphere::createTexture(char const *filePath) {
	return loadtga(filePath);
}

void MySphere::setTexture(char const *filePath) {
	GLuint tex = createTexture(filePath);
	if (tex != -1) {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tex);
		glUniform1i(glGetUniformLocation(shaderProgram, "solarTexture"), 0);
	}
}
void MySphere::displaySphere() {
	string temp = "_resources_/" + name;
	temp += ".tga";
	setTexture(temp.c_str());
	glViewport(0, 0, windowWidth, windowHeight);
	glUseProgram(shaderProgram);
	// 计算矩阵
	glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(45.0f), (float)windowWidth / (float)windowHeight, 0.1f, 100.0f);
	glm::mat4 model(1.0f);
	model = glm::scale(model, glm::vec3(5, 5, 5));
	if (name == "Sun") {

	}
	else {
		model = glm::translate(model, glm::vec3(radius * cos(glfwGetTime() / 100),
			0,
			radius * sin(glfwGetTime() / 100)
		));
		model = glm::rotate(model, (GLfloat)glfwGetTime(), glm::vec3(1, 1, 0));
	}
	

	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, &projection[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, &view[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, &model[0][0]);

	glBindVertexArray(VAO);
	// Array Buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	glDrawElements(GL_TRIANGLES, (GLsizei)(indices.size()), GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void MySphere::parseSphereShaders() {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (GLvoid *)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (GLvoid *)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (GLvoid *)(sizeof(float) * 3));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(float), indices.data(), GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}
