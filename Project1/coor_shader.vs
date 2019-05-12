# version 330 core
// ���õ�ǰʹ��GLSL�汾����

// �����޶������ѻ��������������ݰ�����������������������������������
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
out vec3 ourColor;

void main() {
	// ���ñ��������涥��λ�õ��������
	gl_Position = projection * view * model * vec4(aPos, 1.0f);
	ourColor = color; // ��fs�д�����ɫ
	gl_PointSize = 100;
}