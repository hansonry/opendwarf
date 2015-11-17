#version 330

out vec4 FragColor;
in  vec4 Color;
in  vec3 Normal;

uniform vec3 LightDirection;

void main()
{
   float DiffuseFactor;
   vec4 DiffuseColor;
   vec3 NNormal;

   NNormal = normalize(Normal);
   DiffuseFactor = dot(NNormal, LightDirection);
   if(DiffuseFactor > 0)
   {
      DiffuseColor = vec4(Color.xyz * DiffuseFactor, 1.0f);
   }
   else
   {
      DiffuseColor = vec4(0, 0, 0, 0);
   }


   FragColor = DiffuseColor;
}

