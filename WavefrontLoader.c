#include <stdio.h>
#include <stdlib.h>
#include "WavefrontLoader.h"



static void WavefrontLoader_LoadFile(WavefrontLoaderData_T * data, FILE * obj_file, const char * material_path)
{
}


void WavefrontLoader_Load(WavefrontLoaderData_T * data, const char * filename, const char * material_path)
{
   FILE * obj_file;

   obj_file = fopen(filename, "r");

   if(obj_file != NULL)
   {
      WavefrontLoader_LoadFile(data, obj_file, material_path);
      fclose(obj_file);
   }
   else
   {
      printf("Error: WavefrontLoader_Load can't open file: %s\n", filename);
   }
}



void WavefrontLoader_Delete(WavefrontLoaderData_T * data)
{
}


