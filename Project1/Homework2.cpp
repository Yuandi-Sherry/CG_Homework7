#include "Homework2.h"
Homework2::Homework2(const string & vertexShaderFile, const string & fragmentShaderFile):HomeworkBase(vertexShaderFile, fragmentShaderFile)
{
	shaderProgram = HomeworkBase::shaderProgram;
	initBool();
}

Homework2::~Homework2()
{
}

void Homework2::displayPoint() {
	float pointVertex[] = {
		0, 0, 0, 1, 1, 1
	};
	unsigned int VBO;
	unsigned int VAO; // 顶点数组对象 
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindVertexArray(VAO);
	// 位置、颜色属性
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBufferData(GL_ARRAY_BUFFER, sizeof(pointVertex), pointVertex, GL_STATIC_DRAW);
	glViewport(400, 0, 400, 400);
	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);
	glPointSize(5.0f);
	glDrawArrays(GL_POINTS, 0, 1);

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void Homework2::displayRec() {
	float recVertices[] = {
		0.5f, 0.5f, 0.0f, 1, 1, 1,   // 右上角
		0.5f, -0.5f, 0.0f, 0, 1, 1,  // 右下角
		-0.5f, -0.5f, 0.0f, 1, 0, 1, // 左下角
		-0.5f, 0.5f, 0.0f, 1, 1, 0   // 左上角
	};
	unsigned int indices[] = { // 注意索引从0开始! 
		0, 1, 3, // 第一个三角形
		1, 2, 3  // 第二个三角形
	};
	unsigned int VBO;
	unsigned int VAO; // 顶点数组对象 
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindVertexArray(VAO);
	// 索引缓冲对象
	unsigned int EBO;
	glGenBuffers(1, &EBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(recVertices), recVertices, GL_STATIC_DRAW);
	// 这里的 缓冲类型为GL_ELEMENT_ARRAY_BUFFER
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glViewport(0, 200, 400, 400); // 注意视口要加载use之前
	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void Homework2::displayLine() {
	float lineVertices[] = {
		-0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f,
		0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f
	};
	unsigned int VBO;
	unsigned int VAO; // 顶点数组对象 
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindVertexArray(VAO);
	// 位置、颜色属性
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBufferData(GL_ARRAY_BUFFER, sizeof(lineVertices), lineVertices, GL_STATIC_DRAW);
	glViewport(400, 400, 400, 400);
	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);
	glDrawArrays(GL_LINE_STRIP, 0, 2); // 注意这里不是GL_LINE

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void Homework2::displayTriangle() {
	// 三角形初始颜色
	GLfloat triangleVertices[] = {
		 0,  0.5f, 0, 1, 0, 0,
		-0.5f, -0.5f, 0, 0, 1, 0,
		 0.5f, -0.5f, 0, 0, 0, 1 };

	GLfloat vertices[] = {
		0,  0.5f, 0, triangleColor.x, triangleColor.y, triangleColor.z,
		-0.5f, -0.5f, 0, triangleColor.x, triangleColor.y, triangleColor.z,
		0.5f, -0.5f, 0, triangleColor.x, triangleColor.y, triangleColor.z };
	unsigned int VBO;
	unsigned int VAO; // 顶点数组对象 
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindVertexArray(VAO);

	if (dirty) {
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	}
	else {
		glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices), triangleVertices, GL_STATIC_DRAW);
		// judge dirty
		if (triangleColor.x > 0) {
			dirty = true;
		}
	}
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// 绘制
	glViewport(0, 0, 400, 400);
	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void Homework2::displaySeveralTriangle() {
	float recVertices[] = {
		// 三角形2
		0.1f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.3f, 0.0f, 0.0f, 0.0f, 1.0f,
		// 三角形3
		-0.0f, 0.4f, 0.0f, 1.0f, 0.0f, 0.0f,
		-0.4f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, 0.1f, 0.0f, 0.0f, 0.0f, 1.0f,
		// 三角形1
		0.0f, -0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.5f, -0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		// 三角形4
		-0.3f, -0.2f, 0.0f, 1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, -0.1f, 0.0f, 0.0f, 0.0f, 1.0f
	};
	unsigned int indices[] = {
		0, 1, 2, // 第一个三角形
		3, 4, 5, // 第二个三角形
		6, 7, 8, // 第三个三角形
		9, 10, 11 // 第四个三角形
	};
	// 索引缓冲对象
	unsigned int EBO;
	glGenBuffers(1, &EBO);
	unsigned int VBO;
	unsigned int VAO; // 顶点数组对象 
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(recVertices), recVertices, GL_STATIC_DRAW);
	// 这里的 缓冲类型为GL_ELEMENT_ARRAY_BUFFER
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glViewport(400, 200, 400, 400); // 注意视口要加载use之前
	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void Homework2::initBool() {
	basic = false;
	triangle = false;
	bonus = false;
	point = false;
	line = false;
	rectangle = false;
	severalTri = false;
	dirty = false;
}

void Homework2::displayController() {
	if (rectangle) {
		displayRec();
	}
	if (severalTri)
		displaySeveralTriangle();

	// 指定三角形顶点和颜色
	if (triangle) {
		displayTriangle();
	}
	if (point) {
		displayPoint();
	}
	if (line) {
		displayLine();
	}
}

void Homework2::imGuiMenuSetting() {
	if (ImGui::BeginMenu("Homework2"))
	{
		if (ImGui::BeginMenu("Basic"))
		{
			ImGui::MenuItem("Triangle", NULL, &triangle);
			ImGui::MenuItem("Point", NULL, &point);
			ImGui::MenuItem("Line", NULL, &line);
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Bonus"))
		{
			ImGui::MenuItem("Rectangle", NULL, &rectangle);
			ImGui::MenuItem("Several Triangles", NULL, &severalTri);
			ImGui::EndMenu();
		}
		ImGui::EndMenu();
	}
}

void Homework2::imGuiSetting() {
	if (triangle) {
		ImGui::ColorEdit3("Triangle color", (float*)&triangleColor);
	}
}

void Homework2::processInput() {

}