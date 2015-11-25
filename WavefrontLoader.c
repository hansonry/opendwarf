#include <stdio.h>
#include <stdlib.h>
#include "WavefrontLoader.h"


typedef enum WavefrontLoaderState_E WavefrontLoaderState_T;
enum WavefrontLoaderState_E
{
   e_WLS_Init,
   e_WLS_Comment,
   e_WLS_Unknown,
   e_WLS_Vertex,
   e_WLS_Normal,
   e_WLS_UV,
   e_WLS_Face
};
typedef enum StringMatchState_E StringMatchState_T;
enum StringMatchState_E
{
   e_SMS_Valid,
   e_SMS_MatchFail,
   e_SMS_MatchPass

};

static int FILE_StringMatch(FILE * file, const char * strs[], StringMatchState_T * match_data, int str_count)
{
   int c;
   int i;
   int output;
   int done;
   int index;

   for(i = 0; i < str_count; i++)
   {
      match_data[i] = e_SMS_Valid;
   }

   c = fgetc(file);
   while(c == ' ' || c == '\t' || c == '\n' || c == '\r')
   {
      c = fgetc(file);
   }

   output = -1;
   done = 0;
   index = 0;
   while(done == 0)
   {
      if(c == EOF)
      {
         done = 1;
      }
      else
      {
         for(i = 0; i < str_count; i++)
         {
            if(match_data[i] == e_SMS_Valid)
            {
               if(strs[i][index] != c)
               {
                  match_data[i] = e_SMS_MatchFail;
               }
               else if(strs[i][index + 1] == '\0')
               {
                  match_data[i] == e_SMS_MatchPass;
                  if(output == -1)
                  {
                     output = i;
                  }
                  done = 1;
               }
            }
         }

         index ++;
         c = fgetc(file);
      }
   }

   return output;

}

static void WavefrontLoader_ParseVertex(WavefrontLoaderData_T * data, FILE * obj_file)
{
};


#define OBJ_CMDS_SIZE 5
static const char * obj_cmds[OBJ_CMDS_SIZE]                        = {"#",           "v ",         "vn ",       "vt ",     "f "};
static const WavefrontLoaderState_T obj_cmds_states[OBJ_CMDS_SIZE] = {e_WLS_Comment, e_WLS_Vertex, e_WLS_Normal, e_WLS_UV, e_WLS_Face};

static void WavefrontLoader_LoadFile(WavefrontLoaderData_T * data, FILE * obj_file, const char * material_path)
{
   StringMatchState_T string_state[OBJ_CMDS_SIZE];
   WavefrontLoaderState_T state;
   int done;
   int found_index;
   int c;

   state = e_WLS_Init;

   done = 0;
   while(done == 0)
   {
      switch(state)
      {
         case e_WLS_Init:
            found_index = FILE_StringMatch(obj_file, obj_cmds, string_state, OBJ_CMDS_SIZE);
            if(found_index < 0)
            {
               state = e_WLS_Unknown;
            }
            else
            {
               state = obj_cmds_states[found_index];
            }
            break;
         case e_WLS_Comment:
         case e_WLS_Unknown:
            c = fgetc(obj_file);
            while(c != '\n' && c != EOF)
            {
               c = fgetc(obj_file);
            }
            if(c == EOF)
            {
               done = 1;
            }
            else
            {
               state = e_WLS_Init;
            }
            
            break;
         case e_WLS_Vertex:
            WavefrontLoader_ParseVertex(data, obj_file);
            break;
           
      }
   }



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


