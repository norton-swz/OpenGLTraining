#version 330 core
layout (location = 0) out vec3 gPosition;
layout (location = 1) out vec3 gNormal;
layout (location = 2) out vec4 gAlbedoSpec;


in vec3 Normal;  
in vec3 FragPos;    


void main()
{
    gPosition = FragPos;
    gNormal = normalize(Normal);
    gAlbedoSpec.rgb = vec3(1.0, 1.0, 1.0);
    gAlbedoSpec.a = 8.0;
} 