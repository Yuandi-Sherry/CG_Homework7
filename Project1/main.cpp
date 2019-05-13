#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <string>
#include <iostream>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "Homework2.h"
#include "Homework3.h"
#include "Homework4.h"
#include "Homework5.h"
#include "Homework6.h"
#include "Homework7.h"
#include "ShaderProgram.h"
#include "MySphere.h"
#define N 888
using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow * window, Homework5 & homework5);

void initGUI(GLFWwindow* window);
void displayGUI(GLFWwindow* window, Homework2 & homework2, Homework3 & homework3, Homework4 & homework4);
GLFWwindow* initialize();
int windowWidth = 800;
int windowHeight = 600;
// homework5 bonus mouse movement
float yaw = -90.0f;
float pitch = 0.0f;
float lastX = 800.0f / 2.0;
float lastY = 600.0f / 2.0;
float fov = 45.0f;
float sensitivity = 0.1f;

static void glfw_error_callback(int error, const char* description)
{
	fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}
// 颜色着色器文件
const string vertexShaderFile = "shader.vs";
const string fragmentShaderFile = "shader.fs";
// 纹理着色器文件
const string vertexShaderFile_texture = "texture_shader.vs";
const string fragmentShaderFile_texture = "texture_shader.fs";
const char* glsl_version = "#version 130";
// 清屏颜色
ImVec4 clear_color = ImVec4(0, 0, 0, 1.00f);
Homework5 homework5;
Homework6 homework6;
Homework7 homework7;
int main() {
	try {
		GLFWwindow* window = initialize();

		// 新建作业对象
		Homework2 homework2(vertexShaderFile, fragmentShaderFile);
		Homework3 homework3(vertexShaderFile, fragmentShaderFile);
		Homework4 homework4("coor_shader.vs", "coor_shader.fs");
		homework5.init("coor_shader.vs", "coor_shader.fs");
		homework6.init("coor_shader.vs", "coor_shader.fs");
		homework7.init("depth_shader.vs", "depth_shader.fs");

		// 鼠标输入相关设置
		glfwSetCursorPosCallback(window, mouse_callback);
		glfwSetScrollCallback(window, scroll_callback);
		// glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		// homework4.prepareCosmos();
		// 渲染循环
		// 每次循环开始前检查GLFW是否被退出
		while (!glfwWindowShouldClose(window)) {
			// 检查触发事件、更新窗口，回调
			glfwPollEvents();
			/*processInput(window, homework5);
			glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			// 作业对象的显示控制
			/*homework2.displayController();
			homework3.displayController();
			homework4.displayController();
			homework5.displayController();
			homework6.displayController();*/
			homework7.displayController();
			//displayGUI(window, homework2, homework3, homework4);
			//homework4.displayCosmos();
			// 交换缓冲、绘制、显示
			glfwSwapBuffers(window);
			
		}

		// 释放/删除资源
		glfwTerminate();
	}
	catch (const char* msg) {
		cerr << msg << endl;
	}	
	return 0;
}

GLFWwindow* initialize() {
	// Setup window
	glfwSetErrorCallback(glfw_error_callback);
	if (!glfwInit())
		throw "fail to init glfw";
	// 初始化GLFW
	glfwInit();
	// 设置GLFW - OpenGL 3.3 core mode
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	// 创建窗口
	GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "CG_HOMEWORK", NULL, NULL);
	if (window == NULL) {
		glfwTerminate();
		throw "fail to init window";
	}
	// 将创建的窗口的上下文设为当前线程的主上下文
	glfwMakeContextCurrent(window);

	glfwSwapInterval(1); // Enable vsync
	// 初始化GLAD，加载系统相关OpenGL函数指针
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		throw "fail to load glad";
	}
	glViewport(0, 0, windowWidth, windowHeight);
	glEnable(GL_DEPTH_TEST);
	// init GUI
	initGUI(window);
	return window;
}
/*
 * 鼠标调整后的新的大小为后两个参数
 */
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}
/*
 * 处理输入
 */
void processInput(GLFWwindow * window, Homework5 & homework5) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
	homework5.processInput(window);
	homework6.processInput(window);
}



/*
 * 编译着色器
 @shader 着色器
 @filename 着色器文件名
 @type 着色器类别 1->vertex, 2->fragment
 */


void initGUI(GLFWwindow* window) {
	// set up GUI context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	// Setup Platform/Renderer bindings
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);
}

void displayGUI(GLFWwindow* window, Homework2 & homework2, Homework3 & homework3, Homework4 & homework4) {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	ImGui::Begin("Options", NULL, ImGuiWindowFlags_MenuBar);
	if (ImGui::BeginMenuBar())
	{
		// 作业GUI显示
		homework2.imGuiMenuSetting();
		homework3.imGuiMenuSetting();
		homework4.imGuiMenuSetting();
		homework5.imGuiMenuSetting();
		homework6.imGuiMenuSetting();
		homework7.imGuiMenuSetting();
		ImGui::EndMenuBar();
	}
	homework2.imGuiSetting();
	homework3.imGuiSetting();
	homework4.imGuiSetting();
	homework5.imGuiSetting();
	homework6.imGuiSetting();
	homework7.imGuiSetting();
	ImGui::End();
	// Rendering
	ImGui::Render();
	int display_w, display_h;
	glfwMakeContextCurrent(window);
	glfwGetFramebufferSize(window, &display_w, &display_h);
	glViewport(-1, 1, display_w, display_h);
	
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	homework5.mouseCallback(window, xpos, ypos);
	homework6.mouseCallback(window, xpos, ypos);
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	homework5.scrollCallback(window, xoffset, yoffset);
	homework7.scrollCallback(window, xoffset, yoffset);
}

