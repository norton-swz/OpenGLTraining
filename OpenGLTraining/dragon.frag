#version 330 core
out vec4 FragColor;

in vec3 Normal;  
in vec3 FragPos;    

uniform vec3 lightColor;
uniform vec3 lightdirection;

void main()
{
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
        
    vec3 result = (ambient + diffuse + specular);
    FragColor = vec4(result, 1.0);
} 