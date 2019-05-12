# version 330 core
// 设置当前使用GLSL版本名称

// 布局限定符，把缓冲区索引的数据绑定输入输出，并声明三个浮点数的输入变量
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
out vec3 ourColor;

void main() {
	gl_Position = vec4(aPos,1.0f);
	ourColor = color;
	gl_PointSize = 100;
}