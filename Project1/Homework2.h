#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <string>
#include <iostream>
#include "HomeworkBase.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
using namespace std;
class Homework2 : public HomeworkBase
{
public:
	Homework2(const string & vertexShaderFile, const string & fragmentShaderFile);
	~Homework2();
	void displayPoint();
	void displayLine();
	void displayRec();
	void displayTriangle();
	void displaySeveralTriangle();
	void processInput();

	bool homework2;
	bool basic;
	bool triangle;
	bool bonus;
	bool point;
	bool line;
	bool rectangle;
	bool severalTri;
	ImVec4 triangleColor = ImVec4(-1.0f, -1.0f, -1.0f, 1.00f);
	void displayController();
	void imGuiSetting();
	void imGuiMenuSetting();
private:
	void initBool();	
	bool dirty; // 修改三角形颜色
	int shaderProgram;
};

