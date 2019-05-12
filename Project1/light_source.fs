#version 330 core
// 灯的着色器，万年白光
out vec4 FragColor;
uniform vec3 lightColor;

void main() {
	FragColor = vec4(lightColor, 1.0);
}
