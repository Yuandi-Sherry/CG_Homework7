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
	// 获得顶点坐标位置
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    
	// 计算顶点的世界坐标
	vec3 Position = vec3(model * vec4(aPos, 1.0));
	// 将法向量转化
    vec3 Normal = mat3(transpose(inverse(model))) * aNormal;
    
    // 环境光
    vec3 ambient = ambientFactor * lightColor;
  	
    // 漫反射
    vec3 norm = normalize(Normal); // 标准化法向量
    vec3 lightDir = normalize(lightPosition - Position); // 标准化光照方向，这里的lightPosition是在世界坐标系
    float diff = max(dot(norm, lightDir), 0.0); // 计算漫反射系数
    vec3 diffuse = diffuseFactor * diff * lightColor; // 计算漫反射
    
    // 镜面反射
    vec3 viewDir = normalize(viewPos - Position); // 从观察点到物体位置的方向
    vec3 reflectDir = reflect(-lightDir, norm);  // 反射方向
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), reflectionPara); 
    vec3 specular = specularFactor * spec * lightColor;      

    LightingColor = ambient + diffuse + specular;
}
