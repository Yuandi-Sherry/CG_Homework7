#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 LightingColor; // resulting color from lighting calculations

uniform vec3 lightPosition;
uniform vec3 viewPos;
uniform vec3 lightColor;

uniform float ambientFactor;
uniform float diffuseFactor;
uniform float specularFactor;
uniform uint reflectionPara;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	// ��ö�������λ��
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    
	// ���㶥�����������
	vec3 Position = vec3(model * vec4(aPos, 1.0));
	// ��������ת��
    vec3 Normal = mat3(transpose(inverse(model))) * aNormal;
    
    // ������
    vec3 ambient = ambientFactor * lightColor;
  	
    // ������
    vec3 norm = normalize(Normal); // ��׼��������
    vec3 lightDir = normalize(lightPosition - Position); // ��׼�����շ��������lightPosition������������ϵ
    float diff = max(dot(norm, lightDir), 0.0); // ����������ϵ��
    vec3 diffuse = diffuseFactor * diff * lightColor; // ����������
    
    // ���淴��
    vec3 viewDir = normalize(viewPos - Position); // �ӹ۲�㵽����λ�õķ���
    vec3 reflectDir = reflect(-lightDir, norm);  // ���䷽��
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), reflectionPara); 
    vec3 specular = specularFactor * spec * lightColor;      

    LightingColor = ambient + diffuse + specular;
}
