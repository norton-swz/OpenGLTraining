#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 result;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 lightColor;
uniform vec3 lightdirection;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    vec3 FragPos = vec3(view * model * vec4(aPos, 1.0));
    vec3 Normal = mat3(transpose(inverse(model))) * aNormal; 

    // ambient
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    float diff = max(dot(norm, lightdirection), 0.0);
    vec3 diffuse = diff * lightColor;
    
    // specular
    float specularStrength = 8;
    vec3 viewDir = normalize(-FragPos);
    vec3 reflectDir = reflect(-lightdirection, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 128);
    vec3 specular = specularStrength * spec * lightColor;  
        
    result = ambient + diffuse + specular;
}