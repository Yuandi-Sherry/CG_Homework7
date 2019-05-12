#include "Homework5.h"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stb_image.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define TRANSFACTOR 0.1
using namespace std;
extern int windowWidth;
extern int windowHeight;
extern GLFWwindow* window;
extern float lastX;
extern float lastY;
Homework5::Homework5(const string & vertexShaderFile, const string & fragmentShaderFile) {
	init(vertexShaderFile, fragmentShaderFile);
}
Homework5::Homework5() {

}
void Homework5::init(const string & vertexShaderFile, const string & fragmentShaderFile) {
	HomeworkBase::init(vertexShaderFile, fragmentShaderFile);
	shaderProgram = HomeworkBase::shaderProgram;
	initVars();
	camera.setCamera();
}
Homework5::~Homework5()
{
}


void Homework5::drawCube() {
	unsigned int VBO;
	unsigned int VAO; // ����������� 
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
	// �������
	//glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	view = glm::translate(view, glm::vec3(x, y, z));
	// ͸��ͶӰ
	if (per) {
		projection = glm::perspective(glm::radians(pro_frov), (float)windowWidth / (float)windowHeight, pro_near, pro_far);
	}
	else
		projection = glm::ortho(ort_left, ort_right, ort_bottom, ort_top, ort_near, ort_far);

	if (viewChanging) {
		//cameraPos = glm::vec3(0.0f, 0.0f, 3.0f); // �����λ��
		//cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f); // ��Ӱ����
		//cameraDirection = glm::normalize(cameraPos - cameraTarget); // ���������
		up = glm::vec3(0.0f, 1.0f, 0.0f); // �����Ϸ�
		//cameraRight = glm::normalize(glm::cross(up, cameraDirection)); // �Ϸ�����������˵õ��ҷ�
		// ����
		//cameraUp = glm::cross(cameraDirection, cameraRight); // ���������ҷ���˵õ�����
		float radius = 10.0f;
		float camX = sin(glfwGetTime()) * radius;
		float camZ = cos(glfwGetTime()) * radius;

		view = glm::lookAt(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
	}
	
	if (FPS) {
		view = camera.getViewMatrix();
	}
	//view = glm::translate(view, glm::vec3(translateX, translateY, translateZ));

	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, &projection[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, &view[0][0]);

	glm::mat4 model = glm::mat4(1.0f);
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, &model[0][0]);
	// ����
	shaderProgramIns.useProgram();
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void Homework5::displayController() {
	if (homework5) {
		drawCube();
	}
		
}

void Homework5::imGuiSetting() {
	if (coordinate_transform) {
		// ѡ��ͶӰ��ʽ
		ImGui::Text("Coordinate Transform");
		ImGui::Checkbox("projection/orthology", &per);
		if (per) {
			ImGui::Text("perspective projection");
			ImGui::SliderFloat("Frov", &pro_frov, 0.0f, 90.0f);
			ImGui::SliderFloat("Near", &pro_near, 0.001f, 10.0f);
			ImGui::SliderFloat("Far", &pro_far, 1.0f, 100.0f);
			ImGui::SliderFloat("z", &z, -10.0f, 0.0f);
		}
		else {
			ImGui::Text("orthology projection");
			ImGui::SliderFloat("Left", &ort_left, -1000.0f, 1000.0f);
			ImGui::SliderFloat("Right", &ort_right, -1000.0f, 1000.0f);
			ImGui::SliderFloat("Bottom", &ort_bottom, -1000.0f, 1000.0f);
			ImGui::SliderFloat("Top", &ort_top, -1000.0f, 1000.0f);
			ImGui::SliderFloat("Near", &ort_near, -1000.0f, 1000.0f);
			ImGui::SliderFloat("Far", &ort_far, -1000.0f, 1000.0f);
		}
	}
	


}
void Homework5::imGuiMenuSetting() {
	if (ImGui::BeginMenu("Homework5")) {
		if (ImGui::BeginMenu("Basic")) {
			ImGui::MenuItem("Coordinate Transform", NULL, &coordinate_transform);
			ImGui::MenuItem("View Changeing", NULL, &viewChanging);
			ImGui::MenuItem("FPS", NULL, &FPS);
			ImGui::EndMenu();
		}
		ImGui::EndMenu();
	}
}

void Homework5::initVars() {
	homework5 = false;
	coordinate_transform = false;
	x = -1.5f;
	y = 0.5f;
	z = -1.5f;

	per = true;
	pro_frov = 45.0f;
	pro_near = 0.1f;
	pro_far = 100.0f;

	ort_left = 0.0f;
	ort_right = windowWidth;
	ort_bottom = 0.0f;
	ort_top = windowHeight;
	ort_near = 0.1f;
	ort_far = 100.0f;

	viewChanging = false;

	FPS = false;

}



// ������������������������
void Homework5::processInput(GLFWwindow * window) {
	if (FPS) {
		// ��������
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			camera.processKeyboard(FORWARD, 0.1);
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			camera.processKeyboard(BACKWARD, 0.1);
		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			camera.processKeyboard(LEFT, 0.1);
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			camera.processKeyboard(RIGHT, 0.1);
		}
	}

}


void Homework5::mouseCallback(GLFWwindow* window, double xpos, double ypos) {
	if (FPS) {
		float xoffset = xpos - lastX;
		float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
		lastX = xpos;
		lastY = ypos;
		camera.processMouseMovement(xoffset, yoffset);

	}

}
void Homework5::scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
	if (FPS) {
		camera.processMouseScroll(yoffset);
	}
}