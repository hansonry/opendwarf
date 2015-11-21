#version 330
// Block Vertex Shader

layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 InNormal;
layout (location = 2) in vec2 InTexCoord;
uniform mat4 PMatrix;
uniform mat4 WMatrix;
out vec3 Normal;
out vec2 TexCoord0;

void main()
{
   gl_Position = vec4(Position, 1.0) * PMatrix;
   Normal = (vec4(InNormal, 0.0) * WMatrix).xyz;
   TexCoord0 = InTexCoord;
}

