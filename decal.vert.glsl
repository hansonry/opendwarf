#version 330
// Decal Vertex Shader

layout (location = 0) in vec3 Position;
layout (location = 1) in vec2 InTexCoord;
uniform mat4 PMatrix;
out vec2 TexCoord0;

void main()
{
   gl_Position = vec4(Position, 1.0) * PMatrix;
   TexCoord0 = InTexCoord;
}

