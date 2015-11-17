#version 330

out vec4 FragColor;
in  vec4 Color;
in  vec3 Normal;
in  vec2 TexCoord0;
uniform vec3 LightDirection;
uniform sampler2D CSampler;

void main()
{
   float DiffuseFactor;
   vec4 DiffuseColor;
   vec3 NNormal;
   vec4 t_frag_color;

   t_frag_color = Color;
   t_frag_color = texture2D(CSampler, TexCoord0);


   NNormal = normalize(Normal);
   DiffuseFactor = dot(NNormal, LightDirection);
   if(DiffuseFactor > 0)
   {
      DiffuseColor = vec4(t_frag_color.xyz * DiffuseFactor, 1.0f);
   }
   else
   {
      DiffuseColor = vec4(0, 0, 0, 0);
   }


   FragColor = DiffuseColor;
}

