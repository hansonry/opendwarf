#version 330
// Decal Shader

out vec4 FragColor;
in  vec2 TexCoord0;
uniform sampler2D CSampler;

void main()
{
   vec4 t_frag_color;

   t_frag_color = texture2D(CSampler, TexCoord0);

   FragColor = t_frag_color;
}

