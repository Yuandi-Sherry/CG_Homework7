#pragma once
#include "ShaderProgram.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <cmath>
class HomeworkBase
{
public:
	HomeworkBase(const string & vsFile, const string & fsFile);
	HomeworkBase();
	void init(const string & vsFile, const string & fsFile);
	~HomeworkBase();
protected:
	int shaderProgram;
	ShaderProgram shaderProgramIns;
};

