#version 330 core
layout (location = 0) in vec3 iPos;
layout (location = 1) in vec3 iNormal;

out VS_OUT {
    vec3 vNormal;
} vs_out;

uniform mat4 uView;
uniform mat4 uModel;

void main()
{
    mat3 NormalMatrix = mat3(transpose(inverse(uView * uModel)));
    vs_out.vNormal = vec3(vec4(NormalMatrix * iNormal, 0.0));
    gl_Position = uView * uModel * vec4(iPos, 1.0); 
}