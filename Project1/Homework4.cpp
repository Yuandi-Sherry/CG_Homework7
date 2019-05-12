#include <iostream>
#include "Homework4.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stb_image.h>

#define TRANSFACTOR 0.1
using namespace std;
extern int windowWidth;
extern int windowHeight;
extern GLFWwindow* window;

Homework4::Homework4(const string & vertexShaderFile, const string & fragmentShaderFile) : HomeworkBase(vertexShaderFile, fragmentShaderFile) {
	shaderProgram = HomeworkBase::shaderProgram;
	initVars();
}
Homework4::~Homework4()
{
}

void Homework4::drawCube() {
	
	// hm5
	unsigned int VBO;
	unsigned int VAO; // 顶点数组对象 
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindVertexArray(VAO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	shaderProgramIns.useProgram();
	// 计算矩阵
	//glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);
	glm::mat4 view;
	if (pro) {
		// 摄像机
		cameraPos = glm::vec3(0.0f, 0.0f, 3.0f); // 摄像机位置
		cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f); // 摄影中心
		cameraDirection = glm::normalize(cameraPos - cameraTarget); // 摄像机方向
		up = glm::vec3(0.0f, 1.0f, 0.0f); // 定义上方
		cameraRight = glm::normalize(glm::cross(up, cameraDirection)); // 上方和相机方向叉乘得到右方
		// 上轴
		cameraUp = glm::cross(cameraDirection, cameraRight); // 相机方向和右方叉乘得到上轴
		float radius = 10.0f;
		float camX = sin(glfwGetTime()) * radius;
		float camZ = cos(glfwGetTime()) * radius;
		
		view = glm::lookAt(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0)); // lookAt旋转
		projection = glm::perspective(glm::radians(pro_frov), (float)windowWidth / (float)windowHeight, pro_near, pro_far);
	}
		
	else
		projection = glm::ortho(ort_left, ort_right, ort_bottom, ort_top, ort_near, ort_far);
	//view = glm::translate(view, glm::vec3(translateX, translateY, translateZ));
	if (translation) {
		translateX += transFactorX * TRANSFACTOR;
		translateY += transFactorY * TRANSFACTOR;
		translateZ += transFactorZ * TRANSFACTOR;
		view = glm::translate(view, glm::vec3(translateX, translateY, translateZ));
	}
		
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, &projection[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, &view[0][0]);

	glm::mat4 model = glm::mat4(1.0f);
	
	if(rotation)
		model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(1.0f, 0.0f, 1.0f));
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, &model[0][0]);
	// 绘制
	shaderProgramIns.useProgram();
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void Homework4::displayController() {
	if (homework4) {
		drawCube();
	}
		
}

void Homework4::imGuiSetting() {
	if (homework4) {
		// 变换的是view
		if (translation) {
			ImGui::Text("Translation");
			ImGui::SliderFloat("X", &transFactorX, -1, 1);
			ImGui::SliderFloat("Y", &transFactorY, -1, 1);
			ImGui::SliderFloat("Z", &transFactorZ, -1, 1);
		}
		// 变换的是model
		if (scaling) {
			ImGui::Text("Scaling");
			ImGui::SliderFloat("Scalar", &scalar, 0.9, 1.1);
			for (int i = 0; i < 36; i++) {
				for (int j = 0; j < 3; j++) {
					cubeVertices[i * 6 + j] *= (double)scalar;
				}
			}
		}

		ImGui::Text("Coordinate Trnsform");
		ImGui::Checkbox("projection/orthology", &pro);
		if (pro) {
			ImGui::Text("perspective projection");
			ImGui::SliderFloat("Frov", &pro_frov, 0.0f, 90.0f);
			ImGui::SliderFloat("Near", &pro_near, 0.0f, 10.0f);
			ImGui::SliderFloat("Far", &pro_far, 10.0f, 100.0f);
		}
		else {
			ImGui::Text("orthology projection");
			ImGui::SliderFloat("Left", &ort_left, -1000.0f, 1000.0f);
			ImGui::SliderFloat("Right", &ort_right, -1000.0f, 1000.0f);
			ImGui::SliderFloat("Bottom", &ort_bottom, -1000.0f, 1000.0f);
			ImGui::SliderFloat("Top", &ort_top, -1000.0f, 1000.0f);
			ImGui::SliderFloat("Far", &ort_far, -1000.0f, 1000.0f);
			ImGui::SliderFloat("Near", &ort_near, -1000.0f, 1000.0f);
		}

	}
	

}
void Homework4::imGuiMenuSetting() {
	if (ImGui::BeginMenu("Homework4")) {
		if (ImGui::BeginMenu("Basic")){
			ImGui::MenuItem("Translation", NULL, &translation);
			ImGui::MenuItem("Rotation", NULL, &rotation);
			ImGui::MenuItem("Scaling", NULL, &scaling);
			ImGui::EndMenu();
		}
		ImGui::EndMenu();
	}
}

void Homework4::initVars() {
	homework4 = false;
	translation = false;
	translateX = 0.0f;
	translateY = 0.0f;
	translateZ = 0.0f;
	rotation = false;
	scaling = false;
	scalar = 1.0f;

	pro = true;
	pro_frov = 45.0f;
	pro_near = 0.1f;
	pro_far = 100.0f;

	ort_left = 0.0f;
	ort_right = 800.0f;
	ort_bottom = 0.0f;
	ort_top = 600.0f;
	ort_near = 0.1f;
	ort_far = 100.0f;
}


void Homework4::prepareCosmos() {
	sun.setPro(shaderProgram);
	earth.setPro(shaderProgram);
	sun.generateSphere(1.0f, "Sun");
	earth.generateSphere(0.3f, "Earth");
}

void Homework4::displayCosmos() {
	// sun.displaySphere();
	earth.displaySphere();
}

// 接受摄像机的鼠标键盘输入控制
void Homework4::processInput() {
/*	float cameraSpeed = 0.05f; // adjust accordingly
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;*/
}