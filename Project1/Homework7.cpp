#include "Homework7.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stb_image.h>
using namespace std;
extern int windowWidth;
extern int windowHeight;
void Homework7::init(const string & vertexShaderFile, const string & fragmentShaderFile) {
	Shader simpleDepthShadertmp("depth_shader.vs", "depth_shader.fs");
	simpleDepthShader.setShaders(simpleDepthShadertmp.getVertexShader(), simpleDepthShadertmp.getFragmentShader());
	Shader debugDepthQuadtmp("depth_quad.vs", "depth_quad.fs");
	debugDepthQuad.setShaders(debugDepthQuadtmp.getVertexShader(), debugDepthQuadtmp.getFragmentShader());
	Shader shadowShadertmp("shadow_shader.vs", "shadow_shader.fs");
	shadowShader.setShaders(shadowShadertmp.getVertexShader(), shadowShadertmp.getFragmentShader());
	camera.setCamera(glm::vec3(0.0f, 0.0f, 3.0f));

	// 设置纹理
	shadowShader.useProgram();
	glUniform1i(glGetUniformLocation(shadowShader.getShaderProgram(), "diffuseTexture"), 0);
	glUniform1i(glGetUniformLocation(shadowShader.getShaderProgram(), "shadowMap"), 1);
	setPlane();
	initVars();
	configureDepth();
}

void Homework7::initVars() {
	lightPos = glm::vec3(-2.0f, 4.0f, -1.0f);
	woodTexture = loadTexture((GLchar*)"./wood.png");
}
void Homework7::configureDepth() {
	glGenFramebuffers(1, &depthMapFBO);
	glGenTextures(1, &depthMap);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
		SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT,
		GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// 把生成的深度纹理作为帧缓冲的深度缓冲
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
	// 不适用任何颜色数据进行渲染
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
}

void Homework7::setPlane() {
	glGenVertexArrays(1, &planeVAO);
	glGenBuffers(1, &planeVBO);
	glBindVertexArray(planeVAO);
	glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), &planeVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glBindVertexArray(0);

}
void Homework7::displayController() {
	// 1. 首选渲染深度贴图
	/*glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glClear(GL_DEPTH_BUFFER_BIT);
	configureShaderAndMatrices();
	RenderScene();
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	// 2. 像往常一样渲染场景，但这次使用深度贴图
	glViewport(0, 0, windowWidth, windowHeight);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	configureShaderAndMatrices();
	glBindTexture(GL_TEXTURE_2D, depthMap);
	RenderScene();
	glBindFramebuffer(GL_FRAMEBUFFER, 0);*/
	configureShaderAndMatrices();
	// RenderScene();
}


void Homework7::imGuiMenuSetting() {

}
void Homework7::imGuiSetting() {

}
/*
	确保每个物体设置了合适的投影和视图矩阵
 */
void Homework7::configureShaderAndMatrices() {
	GLfloat near_plane = 1.0f, far_plane = 7.5f;
	// 使用正交投影制造光线都平行的定向光
	glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
	// 将每个物体变换到从光源视角中可见的空间中
	glm::mat4 lightView = glm::lookAt(lightPos, glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	// 光空间变换矩阵
	glm::mat4 lightSpaceMatrix = lightProjection * lightView;
	simpleDepthShader.useProgram();
	glUniformMatrix4fv(glGetUniformLocation(simpleDepthShader.getShaderProgram(), "lightSpaceMatrix"), 1, GL_FALSE, glm::value_ptr(lightSpaceMatrix));
	glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glClear(GL_DEPTH_BUFFER_BIT);
	RenderScene(simpleDepthShader);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// render scene with shadow
	glViewport(0, 0, windowWidth, windowHeight);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	shadowShader.useProgram();
	glm::mat4 projection = glm::perspective(camera.Zoom, (float)windowWidth / (float)windowHeight, 0.1f, 100.0f);
	glm::mat4 view = camera.getViewMatrix();
	glUniformMatrix4fv(glGetUniformLocation(shadowShader.getShaderProgram(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(glGetUniformLocation(shadowShader.getShaderProgram(), "view"), 1, GL_FALSE, glm::value_ptr(view));
	// Set light uniforms
	glUniform3fv(glGetUniformLocation(shadowShader.getShaderProgram(), "lightPos"), 1, &lightPos[0]);
	glUniform3fv(glGetUniformLocation(shadowShader.getShaderProgram(), "viewPos"), 1, &camera.getPositon()[0]);
	glUniformMatrix4fv(glGetUniformLocation(shadowShader.getShaderProgram(), "lightSpaceMatrix"), 1, GL_FALSE, glm::value_ptr(lightSpaceMatrix));
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, woodTexture);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	RenderScene(shadowShader);


	// Render Depth map to quad
	debugDepthQuad.useProgram();
	glUniform1f(glGetUniformLocation(debugDepthQuad.getShaderProgram(), "near_plane"), near_plane);
	glUniform1f(glGetUniformLocation(debugDepthQuad.getShaderProgram(), "far_plane"), far_plane);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	// RenderQuad();
}

void Homework7::RenderScene(ShaderProgram & shader) {
	// Floor
	glm::mat4 model = glm::mat4(1.0f);;
	glUniformMatrix4fv(glGetUniformLocation(shader.getShaderProgram(), "model"), 1, GL_FALSE, glm::value_ptr(model));
	glBindVertexArray(planeVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
	// Cubes
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, 1.5f, 0.0));
	glUniformMatrix4fv(glGetUniformLocation(shader.getShaderProgram(), "model"), 1, GL_FALSE, glm::value_ptr(model));
	RenderCube();
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(2.0f, 0.0f, 1.0));
	glUniformMatrix4fv(glGetUniformLocation(shader.getShaderProgram(), "model"), 1, GL_FALSE, glm::value_ptr(model));
	RenderCube();
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 2.0));
	model = glm::rotate(model, 60.0f, glm::normalize(glm::vec3(1.0, 0.0, 1.0)));
	model = glm::scale(model, glm::vec3(0.5));
	glUniformMatrix4fv(glGetUniformLocation(shader.getShaderProgram(), "model"), 1, GL_FALSE, glm::value_ptr(model));
	RenderCube();
}

void Homework7::RenderQuad() {
	if (quadVAO == 0)
	{
		GLfloat quadVertices[] = {
			// Positions        // Texture Coords
			-1.0f,  1.0f, 0.0f,  0.0f, 1.0f,
			-1.0f, -1.0f, 0.0f,  0.0f, 0.0f,
			 1.0f,  1.0f, 0.0f,  1.0f, 1.0f,
			 1.0f, -1.0f, 0.0f,  1.0f, 0.0f,
		};
		// Setup plane VAO
		glGenVertexArrays(1, &quadVAO);
		glGenBuffers(1, &quadVBO);
		glBindVertexArray(quadVAO);
		glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	}
	glBindVertexArray(quadVAO);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindVertexArray(0);
}

void Homework7::RenderCube() {
	if (cubeVAO == 0)
	{
		cout << "cubeVAO = 0" << endl;
		glGenVertexArrays(1, &cubeVAO);
		glGenBuffers(1, &cubeVBO);
		// Fill buffer
		glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		// Link vertex attributes
		glBindVertexArray(cubeVAO);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
	// Render Cube
	glBindVertexArray(cubeVAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
}

void Homework7::scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.processMouseScroll(yoffset);
}

GLuint Homework7::loadTexture(GLchar* path)
{
	// Generate texture ID and load texture data 
	GLuint textureID;
	glGenTextures(1, &textureID);
	int width, height, n = 0;
	unsigned char *image = stbi_load(path, &width, &height, 0, 0);// Assign texture to ID
	cout << "width " << width << endl;
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	printf("%d, %d, %d\n", width, height, n);
	glGenerateMipmap(GL_TEXTURE_2D);

	// Parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
	// SOIL_free_image_data(image);
	return textureID;

}
