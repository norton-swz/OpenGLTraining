#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gAlbedoSpec;
//uniform sampler2D gDepth;

uniform vec3 lightColor;
uniform vec3 lightdirection;

void main()
{             
    // retrieve data from gbuffer
    vec3 FragPos = texture(gPosition, TexCoords).rgb;
    vec3 Normal = texture(gNormal, TexCoords).rgb;
    vec3 Diffuse = texture(gAlbedoSpec, TexCoords).rgb;
    float Specular = texture(gAlbedoSpec, TexCoords).a;
    
    // then calculate lighting as usual
    vec3 lighting  = Diffuse * 0.1; // hard-coded ambient component
    // diffuse
    float diff = max(dot(Normal, lightdirection), 0.0);
    vec3 diffuse = diff * lightColor;
    // specular
    vec3 viewDir = normalize(-FragPos);
    vec3 reflectDir = reflect(-lightdirection, Normal);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 128);
    vec3 specular = Specular * spec * lightColor;  

    lighting += diffuse + specular;          
    FragColor = vec4(lighting, 1.0);
}
