#version 330 core

out vec4 oFragColor;

in vec2 vTexCoords;

uniform sampler2D uMainTex;

void main()
{
    vec3 Color = texture(uMainTex, vTexCoords).xyz;
    Color = 1.0f - Color;
    oFragColor = vec4(Color.xyz, 1.0f);
}