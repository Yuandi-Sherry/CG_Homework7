#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <string>
#include <iostream>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <cmath>
#include <string>
#include "HomeworkBase.h"
using namespace std;
class Homework3 : public HomeworkBase
{
public:
	Homework3(const int vertices[6], const string & vertexShaderFile, const string & fragmentShaderFile);
	Homework3(const int & centerX, const int & centerY, const int & radius, const string & vertexShaderFile, const string & fragmentShaderFile);
	Homework3(const string & vertexShaderFile, const string & fragmentShaderFile);
	~Homework3() {

	}
	void drawTriangle();
	void drawCircle();
	void setTriangle(const int & p1x = -300, const int & p1y = -300, const int & p2x = 0, const int & p2y = 600, const int & p3x = 300, const int & p3y = -300);
	void setCircle(const int & centerX = 0, const int & centerY = 0, const int & radius = 500);
	void fillTriangle();
	void displayController();
	void imGuiSetting();
	void imGuiMenuSetting();
	void processInput();

	// options
	bool triangleFrame;
	bool circleFrame;
	bool filledTri;
	// input Vars
	int center[2];
	int radius;
	// tri
	int point1[2];
	int point2[2];
	int point3[2];
private:
	// const
	float color[3] = { 1.0f, 0, 0 };
	int top, bottom, left, right;
	// basic Methods
	void drawPoint(const float location[3], const float color[3], const int & VAO);
	void drawLine(const int startPoint[2], const int endPoint[2], const int & VAO);
	// draw circle
	void draw8points(const int & x, const int & y);
	// fill Tri
	bool isInTri(const int & x, const int & y);
	void initVars();
	void initBound();
	
};

