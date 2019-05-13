#include "Homework6.h"

extern int windowWidth;
extern int windowHeight;
extern float lastX;
extern float lastY;
Homework6::Homework6(const string & vertexShaderFile, const string & fragmentShaderFile) {
	init(vertexShaderFile, fragmentShaderFile);
	
}
Homework6::Homework6() {

}
void Homework6::init(const string & vertexShaderFile, const string & fragmentShaderFile) {
	HomeworkBase::init(vertexShaderFile, fragmentShaderFile);
	shaderProgram = HomeworkBase::shaderProgram;
	camera.setCamera(glm::vec3(0.0f, 0.0f, 20.0f));
	setCubeVAOVBO();
	setLightSourceVAO();
	Shader phongShader("phong_shading.vs", "phong_shading.fs");
	phongShading.setShaders(phongShader.getVertexShader(), phongShader.getFragmentShader());
	Shader gouraudShader("gouraud_shading.vs", "gouraud_shading.fs");
	gouraudShading.setShaders(gouraudShader.getVertexShader(), gouraudShader.getFragmentShader());
	Shader lightSourceShader("phong_shading.vs", "light_source.fs");
	lightSource.setShaders(lightSourceShader.getVertexShader(), lightSourceShader.getFragmentShader());
	initVars();
}
Homework6::~Homework6()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}
void Homework6::initVars() {
	homework6 = false;
	lightPos = glm::vec3(1.2f, 1.0f, 2.0f);
	viewPoint = camera.getPositon();
	lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
	phong = false;
	basic = true;
	bonus = false;
	ambientFactor = 0.1f;
	diffuseFactor = 0.5f;
	specularFactor = 0.1f;
	reflectionPara = 32;
}
void Homework6::displayController() {
	if (homework6) {
		showLightedCube();
		showLightSource();
	}
}

void Homework6::showLightSource() {
	lightSource.useProgram();
	// 设置颜色
	glUniform3f(glGetUniformLocation(lightSource.getShaderProgram(), "lightColor"), lightColor.x, lightColor.y, lightColor.z);
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)windowWidth / (float)windowHeight, 0.1f, 100.0f);
	glm::mat4 view = view = camera.getViewMatrix();
	// lightSource.setMat4("projection", projection);
	glUniformMatrix4fv(glGetUniformLocation(lightSource.getShaderProgram(), "projection"), 1, GL_FALSE, &projection[0][0]);
	// lightSource.setMat("view", view);
	glUniformMatrix4fv(glGetUniformLocation(lightSource.getShaderProgram(), "view"), 1, GL_FALSE, &view[0][0]);

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, lightPos);
	model = glm::scale(model, glm::vec3(0.2f));
	// lightSource.setMat4("Model", model);
	glUniformMatrix4fv(glGetUniformLocation(lightSource.getShaderProgram(), "model"), 1, GL_FALSE, &model[0][0]);
	glBindVertexArray(lightVAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Homework6::showLightedCube (){
	ShaderProgram * thisShader; 
	if (phong) {
		thisShader = &phongShading;
	}
	else {
		thisShader = &gouraudShading;
	}

	(*thisShader).useProgram();

	glUniform3f(glGetUniformLocation((*thisShader).getShaderProgram(), "objectColor"), 1.0f, 0.5f, 0.31f);
	glUniform3f(glGetUniformLocation((*thisShader).getShaderProgram(), "lightColor"), lightColor.x, lightColor.y, lightColor.z);
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)windowWidth / (float)windowHeight, 0.1f, 100.0f);
	glm::mat4 view = camera.getViewMatrix();
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -20.0f));
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, &projection[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, &view[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, &model[0][0]);
	// 环境光
	glUniform1f(glGetUniformLocation((*thisShader).getShaderProgram(), "ambientFactor"), ambientFactor);
	// 漫反射
	glUniform1f(glGetUniformLocation((*thisShader).getShaderProgram(), "diffuseFactor"), diffuseFactor);
	glUniform3f(glGetUniformLocation((*thisShader).getShaderProgram(), "lightPosition"), lightPos.x, lightPos.y, lightPos.z);
	// 镜面反射
	glUniform3f(glGetUniformLocation((*thisShader).getShaderProgram(), "viewPos"), camera.getPositon().x, camera.getPositon().y, camera.getPositon().z);
	glUniform1f(glGetUniformLocation((*thisShader).getShaderProgram(), "specularFactor"), specularFactor);
	glUniform1ui(glGetUniformLocation((*thisShader).getShaderProgram(), "reflectionPara"), reflectionPara);
	
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	
}

void Homework6::setLightSourceVAO() {
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,  6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

void Homework6::setCubeVAOVBO() {
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindVertexArray(VAO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
}
void Homework6::imGuiSetting() {
	if (homework6) {
		if (basic) {
			// 选择Phong和Gouraud Shading
			ImGui::RadioButton("Phong", &phong, 1);
			ImGui::RadioButton("Gouraud", &phong, 0);
			ImGui::DragFloat3("View point", (float*)glm::value_ptr(viewPoint), 1.0f);
			// 视点 camera.position
			if (lastViewPoint != viewPoint) {
				camera.setCamera(viewPoint);
				lastViewPoint = viewPoint;
			}
			else {
				lastViewPoint = camera.getPositon();
				viewPoint = camera.getPositon();
			}

			// 光照位置
			ImGui::DragFloat3("Light Position", (float*)glm::value_ptr(lightPos), 1.0f);
			// 光照颜色
			ImGui::DragFloat3("Light Color", (float*)glm::value_ptr(lightColor), 0.005f, 0.0f, 1.0f);
			// ambient, diffuse, specular, reflectionRate
			ImGui::DragFloat("ambient factor", &ambientFactor, 0.1f, 0.0f, 1.0f);
			ImGui::DragFloat("diffuse factor", &diffuseFactor, 0.1f, 0.0f, 10.0f);
			ImGui::DragFloat("specular factor", &specularFactor, 0.1f, 0.0f, 1.0f);
			ImGui::DragInt("reflection parameter", &reflectionPara, 10, 2, 256);
		}
		if (bonus) {

		}
	}
	
}
void Homework6::imGuiMenuSetting() {
	if (ImGui::BeginMenu("Homework6")) {
		ImGui::MenuItem("Basic", NULL, &basic);
		ImGui::MenuItem("Bonus", NULL, &bonus);
		ImGui::EndMenu();
	}
}

void Homework6::processInput(GLFWwindow * window) {
	// 键盘输入
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


void Homework6::mouseCallback(GLFWwindow* window, double xpos, double ypos) {
	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
	lastX = xpos;
	lastY = ypos;
	camera.processMouseMovement(xoffset, yoffset);

}