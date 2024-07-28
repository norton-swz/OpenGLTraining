#version 330 core
layout (triangles) in;
layout (line_strip, max_vertices = 6) out;

in VS_OUT {
    vec3 vNormal;
} gs_in[];

uniform float uMagnitude;
uniform mat4 uProjection;

void GenerateLine(int index)
{
    gl_Position = uProjection * gl_in[index].gl_Position;
    EmitVertex();
    gl_Position = uProjection * (gl_in[index].gl_Position + vec4(gs_in[index].vNormal, 0.0) * uMagnitude);
    EmitVertex();
    EndPrimitive();
}

void main()
{
    GenerateLine(0); // first vertex normal
    GenerateLine(1); // second vertex normal
    GenerateLine(2); // third vertex normal
}