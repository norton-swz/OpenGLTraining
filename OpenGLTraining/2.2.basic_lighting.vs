#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 aColor;

out vec3 FragPos;
out vec3 Normal;
//out vec3 LightPos;
out vec3 ourColor;

//uniform vec3 lightPos;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    FragPos = vec3(view * model * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(model))) * aNormal;  
    //LightPos = vec3(view * vec4(lightPos, 1.0));
    gl_Position = projection * vec4(FragPos, 1.0);
    ourColor = aColor;
}