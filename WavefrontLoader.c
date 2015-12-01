#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "WavefrontLoader.h"


#define FILEBUFFER_SIZE 8
typedef struct FileBuffer_S FileBuffer_T;
struct FileBuffer_S
{
   FILE * file;
   int buffer[FILEBUFFER_SIZE];
   int index;
};


static void FileBuffer_Init(FileBuffer_T * buff, FILE * file)
{
   buff->file = file;
   buff->index = 0;
}

static int FileBuffer_Read(FileBuffer_T * buff)
{
   if(buff->index > 0)
   {
      buff->index --;
      return buff->buffer[buff->index];
   }
   else
   {
      return fgetc(buff->file);
   }
}

static void FileBuffer_Push(FileBuffer_T * buff, int c)
{
   if(buff->index < FILEBUFFER_SIZE)
   {
      buff->buffer[buff->index] = c;
      buff->index ++;
   }
   else
   {
      printf("Error: FileBuffer_Push buffer is maxed out\n");
   }
}


typedef enum WavefrontLoaderState_E WavefrontLoaderState_T;
enum WavefrontLoaderState_E
{
   e_WLS_Init,
   e_WLS_Comment,
   e_WLS_Unknown,
   e_WLS_Vertex,
   e_WLS_Normal,
   e_WLS_UV,
   e_WLS_Face,
   e_WLS_FaceVertex,
   e_WLS_FaceEnd,
   e_WLS_MaterialLib,
   e_WLS_UseMaterial,
   e_WLS_NewMaterial,
   e_WLS_MapKD
};
typedef enum StringMatchState_E StringMatchState_T;
enum StringMatchState_E
{
   e_SMS_Valid,
   e_SMS_MatchFail,
   e_SMS_MatchPass

};

static int FILE_StringMatch(FileBuffer_T * file_buffer, const char * strs[], StringMatchState_T * match_data, int str_count)
{
   int c;
   int i;
   int output;
   int done;
   int index;
   int still_looking;

   for(i = 0; i < str_count; i++)
   {
      match_data[i] = e_SMS_Valid;
   }

   c = FileBuffer_Read(file_buffer);
   //printf("First char %c\n", c);
   while(c == ' ' || c == '\t' || c == '\n' || c == '\r')
   {
      c = FileBuffer_Read(file_buffer);
   }

   FileBuffer_Push(file_buffer, c);

   output = -1;
   done = 0;
   index = 0;
   while(done == 0)
   {
      c = FileBuffer_Read(file_buffer);
      if(c == EOF)
      {
         done = 1;
      }
      else
      {
         still_looking = 0;
         for(i = 0; i < str_count; i++)
         {
            if(match_data[i] == e_SMS_Valid)
            {
               still_looking = 1;
               if(strs[i][index] != c)
               {
                  match_data[i] = e_SMS_MatchFail;
               }
               else if(strs[i][index + 1] == '\0')
               {
                  match_data[i] = e_SMS_MatchPass;
                  if(output == -1)
                  {
                     output = i;
                  }
                  done = 1;
               }
            }
         }

         if(still_looking == 0)
         {
            done = 1;
         }

         index ++;
      }
   }

   return output;

}

#define IS_INDEX(c) ((c) >= '0' && (c) <= '9')
#define INDEX_BUFFER_SIZE 16

#define IS_FLOAT(c) ((c) == '-' || (c) == '.' || ((c) >= '0' && (c) <= '9'))
#define FLOAT_BUFFER_SIZE 32


static int WavefrontLoader_ReadString(FileBuffer_T * file_buffer, char * out_str, size_t size)
{
   int c;
   int last_non_white_space;
   size_t count;

   c = FileBuffer_Read(file_buffer);
   while(c == ' ' || c == '\t')
   {
      c = FileBuffer_Read(file_buffer);
   }
   FileBuffer_Push(file_buffer, c);

   if(c == EOF)
   {
      return 0;
   }
   
   last_non_white_space = -1;
   count = 0;
   c = FileBuffer_Read(file_buffer);
   while(c != '\n' && count < size)
   {
      if(c != ' ' && c != '\t')
      {
         last_non_white_space = count;
      }


      out_str[count] = (char)c;
      count ++;
      c = FileBuffer_Read(file_buffer);
   }

   if(count >= size)
   {
      FileBuffer_Push(file_buffer, c);
      out_str[last_non_white_space + 1] = '\0';
   }
   else
   {
      out_str[last_non_white_space + 1] = '\0';
   }

   if(last_non_white_space < 0)
   {
      return 0;
   }
   else
   {
      return 1;
   }

}

static int WavefrontLoader_ReadFloat(FileBuffer_T * file_buffer, float * value)
{
   char buffer[FLOAT_BUFFER_SIZE];
   int index;
   int c;
   c = FileBuffer_Read(file_buffer);
   while(c == ' ' || c == '\t')
   {
      c = FileBuffer_Read(file_buffer);
   }

   FileBuffer_Push(file_buffer, c);
   if(c == EOF)
   {
      return 0;
   }

   

   c = FileBuffer_Read(file_buffer);
   index = 0;
   while(IS_FLOAT(c) && index < FLOAT_BUFFER_SIZE - 1)
   {
      buffer[index] = c;
      index ++;
      c = FileBuffer_Read(file_buffer);
   }

   if(!IS_FLOAT(c))
   {
      FileBuffer_Push(file_buffer, c);
   }

   if(index < FLOAT_BUFFER_SIZE - 1)
   {
      buffer[index] = '\0';
      if(sscanf(buffer, "%f", value) == 1)
      {
         return 1;
      }
      else
      {
         return 0;
      }
   }
   else
   {
      return 0;
   }
}

static int WavefrontLoader_ReadIndex(FileBuffer_T * file_buffer, size_t * value)
{
   char buffer[INDEX_BUFFER_SIZE];
   int index;
   int c;
   int v;
   c = FileBuffer_Read(file_buffer);
   while(c == ' ' || c == '\t')
   {
      c = FileBuffer_Read(file_buffer);
   }
   FileBuffer_Push(file_buffer, c);
   if(c == EOF)
   {
      return 0;
   }

   index = 0;
   c = FileBuffer_Read(file_buffer);
   while(IS_INDEX(c) && index < INDEX_BUFFER_SIZE - 1)
   {
      buffer[index] = c;
      index ++;
      c = FileBuffer_Read(file_buffer);
   }

   if(!IS_INDEX(c))
   {
      FileBuffer_Push(file_buffer, c);
   }

   if(index < INDEX_BUFFER_SIZE - 1)
   {
      buffer[index] = '\0';
      if(sscanf(buffer, "%i", &v) == 1)
      {
         (*value) = (size_t)v;
         return 1;
      }
      else
      {
         return 0;
      }
   }
   else
   {
      return 0;
   }
}


#define GROW_BY 16
static void Array_Add(void ** buffer, size_t element_size, size_t *count, size_t * size, void * data)
{
   size_t new_size;
   void * p;
   if((*count) >= (*size))
   {
      new_size = (*count) + GROW_BY;
      if((*buffer) == NULL)
      {
         (*buffer) = malloc(new_size * element_size);
      }
      else
      {
         (*buffer) = realloc(*buffer, new_size * element_size);
      }
      (*size) = new_size;
   }
   p = &((unsigned char *)(*buffer))[(*count) * element_size];
   memcpy(p, data, element_size);
   (*count) ++;

}

static size_t StringArray_Add(char *** str_buffer, size_t * count, size_t * size, char * str)
{
   size_t new_size;
   size_t str_len;
   size_t out_index;
   size_t i;
   char ** p;
   str_len = strlen(str);

   for(i = 0; i < (*count); i++)
   {
      if(strcmp((*str_buffer)[i], str) == 0)
      {
         return i;
      }

   }

   if((*count) >= (*size))
   {
      new_size = (*count) + GROW_BY;
      if((*str_buffer) == NULL)
      {
         (*str_buffer) = malloc(new_size * sizeof(char *));
      }
      else
      {
         (*str_buffer) = realloc(*str_buffer, new_size * sizeof(char *));
      }
      (*size) = new_size;
   }
   p = &(*str_buffer)[(*count)];

   (*p) = malloc(sizeof(char) * (str_len + 1));
   
   memcpy(*p, str, str_len + 1);
   out_index = (*count);
   (*count) ++; 
   return out_index;
}

static int WavefrontLoader_ParseVertex(WavefrontLoaderData_T * data, FileBuffer_T * obj_file_buffer)
{
   WavefrontLoaderVertex_T vert;
   int sucess;

   vert.w = 1.0f;

   if(WavefrontLoader_ReadFloat(obj_file_buffer, &vert.x) == 1 &&
      WavefrontLoader_ReadFloat(obj_file_buffer, &vert.y) == 1 &&
      WavefrontLoader_ReadFloat(obj_file_buffer, &vert.z) == 1)
   {
      sucess = 1;
      WavefrontLoader_ReadFloat(obj_file_buffer, &vert.w);
   }
   else
   {
      sucess = 0;
   }

   if(sucess == 1)
   {
      Array_Add((void**)&data->vertex_list, sizeof(WavefrontLoaderVertex_T), 
                &data->vertex_list_count, &data->vertex_list_size, &vert);
   }
   return sucess;
};

static int WavefrontLoader_ParseNormal(WavefrontLoaderData_T * data, FileBuffer_T * obj_file_buffer)
{
   WavefrontLoaderNormal_T norm;
   int sucess;
   int end_with_newline;


   if(WavefrontLoader_ReadFloat(obj_file_buffer, &norm.x) == 1 &&
      WavefrontLoader_ReadFloat(obj_file_buffer, &norm.y) == 1 &&
      WavefrontLoader_ReadFloat(obj_file_buffer, &norm.z) == 1)
   {
      sucess = 1;
   }
   else
   {
      sucess = 0;
   }

   if(sucess == 1)
   {
      Array_Add((void**)&data->normal_list, sizeof(WavefrontLoaderNormal_T), 
                &data->normal_list_count, &data->normal_list_size, &norm);
   }
   return sucess;
};

static int WavefrontLoader_ParseUV(WavefrontLoaderData_T * data, FileBuffer_T * obj_file_buffer)
{
   WavefrontLoaderUV_T uv;
   int sucess;

   uv.w = 0.0f;

   if(WavefrontLoader_ReadFloat(obj_file_buffer, &uv.u) == 1 &&
      WavefrontLoader_ReadFloat(obj_file_buffer, &uv.v) == 1)
   {
      sucess = 1;
      WavefrontLoader_ReadFloat(obj_file_buffer, &uv.w);
   }
   else
   {
      sucess = 0;
   }

   if(sucess == 1)
   {
      Array_Add((void**)&data->uv_list, sizeof(WavefrontLoaderUV_T), 
                &data->uv_list_count, &data->uv_list_size, &uv);
   }
   return sucess;
}

static int WavefrontLoader_NextSlash(FileBuffer_T * obj_file_buffer)
{
   int c;
   int output;

   c = FileBuffer_Read(obj_file_buffer);
   while(c != EOF && (c == ' ' || c == '\t'))
   {
      c = FileBuffer_Read(obj_file_buffer);
   }

   if(c == '/')
   {
      output = 1;
   }
   else
   {
      FileBuffer_Push(obj_file_buffer, c);
      output = 0;
   }
   return output;
}

static int WavefrontLoader_ParseFaceVertex(WavefrontLoaderData_T * data, FileBuffer_T * obj_file_buffer)
{
   WavefrontLoaderFaceVertex_T face_vertex;
   int sucess;

   

   if(WavefrontLoader_ReadIndex(obj_file_buffer, &face_vertex.vertex_index) == 1)
   {
      sucess = 1;
      face_vertex.vertex_index --; // 1 based to 0 based
      if(WavefrontLoader_NextSlash(obj_file_buffer) == 1)
      {
         WavefrontLoader_ReadIndex(obj_file_buffer, &face_vertex.uv_index);
         face_vertex.uv_index --;
         if(WavefrontLoader_NextSlash(obj_file_buffer) == 1)
         {
            WavefrontLoader_ReadIndex(obj_file_buffer, &face_vertex.normal_index);
            face_vertex.normal_index --;
         }
      }
   }
   else
   {
      sucess = 0;
   }

   if(sucess == 1)
   {
      Array_Add((void**)&data->face_vertex_list, sizeof(WavefrontLoaderFaceVertex_T), 
                &data->face_vertex_list_count, &data->face_vertex_list_size, 
                &face_vertex);
   }
   return sucess;
}

#define FILENAME_MAX_SIZE 128
static size_t WavefrontLoader_ParseMaterialLib(WavefrontLoaderData_T * data, FileBuffer_T * file_buffer)
{
   char filename[FILENAME_MAX_SIZE];
   WavefrontLoaderMaterialLib_T matlib;
   size_t string_index;
   string_index = 0;

   if(WavefrontLoader_ReadString(file_buffer, filename, FILENAME_MAX_SIZE) == 1)
   {
      //printf("ParseMaterial: %s\n", filename);

      string_index = StringArray_Add(&data->string_list, &data->string_list_count, &data->string_list_size, filename);
      matlib.filename_string_index = string_index;
      Array_Add((void**)&data->materiallib_list, sizeof(WavefrontLoaderMaterialLib_T),
                &data->materiallib_list_count, &data->materiallib_list_size,
                &matlib);
   }

   return string_index;
}

#define MATERIALNAME_MAX_SIZE  64
static size_t WavefrontLoader_ParseMaterialName(WavefrontLoaderData_T * data, FileBuffer_T * file_buffer)
{
   char material_name[MATERIALNAME_MAX_SIZE];
   size_t index;
   size_t string_index;

   if(WavefrontLoader_ReadString(file_buffer, material_name, MATERIALNAME_MAX_SIZE) == 1)
   {
      index = StringArray_Add(&data->string_list, &data->string_list_count, &data->string_list_size, material_name);
   }
   else
   {
      index = 0;
   }
   return index;
}



static void WavefrontLoader_Blank(WavefrontLoaderData_T * data)
{
   data->vertex_list            = NULL;
   data->vertex_list_count      = 0;
   data->vertex_list_size       = 0;
   data->normal_list            = NULL;
   data->normal_list_count      = 0;
   data->normal_list_size       = 0;
   data->uv_list                = NULL;
   data->uv_list_count          = 0;
   data->uv_list_size           = 0;
   data->face_vertex_list       = NULL;
   data->face_vertex_list_count = 0;
   data->face_vertex_list_size  = 0;
   data->face_list              = NULL;
   data->face_list_count        = 0;
   data->face_list_size         = 0;
   data->string_list            = NULL;
   data->string_list_count      = 0;
   data->string_list_size       = 0;
   data->materiallib_list       = NULL;
   data->materiallib_list_count = 0;
   data->materiallib_list_size  = 0;
   data->material_list          = NULL;
   data->material_list_count    = 0;
   data->material_list_size     = 0;
}

#define OBJ_CMDS_SIZE  7
static const char * obj_cmds[OBJ_CMDS_SIZE]                        = {"#",           "v ",         "vn ",       "vt ",     "f ",       "mtllib ",         "usemtl "};
static const WavefrontLoaderState_T obj_cmds_states[OBJ_CMDS_SIZE] = {e_WLS_Comment, e_WLS_Vertex, e_WLS_Normal, e_WLS_UV, e_WLS_Face, e_WLS_MaterialLib, e_WLS_UseMaterial};

static void WavefrontLoader_LoadFile(WavefrontLoaderData_T * data, FILE * obj_file)
{
   StringMatchState_T string_state[OBJ_CMDS_SIZE];
   WavefrontLoaderState_T state;
   WavefrontLoaderFace_T face;
   FileBuffer_T obj_file_buffer;
   int done;
   int found_index;
   int c;
   face.material_index          = 0;
   face.material_string_index   = 0;
   face.face_vertex_start_index = 0;
   face.face_vertex_count       = 0;

   // Init WavefrontLoaderState_T
   WavefrontLoader_Blank(data);

   state = e_WLS_Init;


   FileBuffer_Init(&obj_file_buffer, obj_file);

   done = 0;
   while(done == 0)
   {
      switch(state)
      {
         case e_WLS_Init:
            found_index = FILE_StringMatch(&obj_file_buffer, obj_cmds, string_state, OBJ_CMDS_SIZE);
            //printf("e_WLS_Init %i\n", found_index);
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
            //printf("e_WLS_Comment\n");
            c = FileBuffer_Read(&obj_file_buffer);            
            while(c != '\n' && c != EOF)
            {
               //printf("c: %c\n", c);
               c = FileBuffer_Read(&obj_file_buffer);
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
            //printf("e_WLS_Vertex\n");
            if(WavefrontLoader_ParseVertex(data, &obj_file_buffer))
            {
               state = e_WLS_Init;
            }
            else
            {
               done = 1;
            }

            break;
         case e_WLS_Normal:
            //printf("e_WLS_Normal\n");
            if(WavefrontLoader_ParseNormal(data, &obj_file_buffer))
            {
               state = e_WLS_Init;
            }
            else
            {
               done = 1;
            }
            break;
         case e_WLS_UV:
            //printf("e_WLS_UV\n");
            if(WavefrontLoader_ParseUV(data, &obj_file_buffer))
            {
               state = e_WLS_Init;
            }
            else
            {
               done = 1;
            }
            break;
         case e_WLS_Face:
            //printf("e_WLS_Face\n");
            face.face_vertex_start_index = data->face_vertex_list_count;
            face.face_vertex_count = 0;
            state = e_WLS_FaceVertex;
            break;
         case e_WLS_FaceVertex:
            //printf("e_WLS_FaceVertex\n");
            if(WavefrontLoader_ParseFaceVertex(data, &obj_file_buffer))
            {
               state = e_WLS_FaceVertex;
               face.face_vertex_count ++;
            }
            else
            {
               state = e_WLS_FaceEnd;
            }
            break;
         case e_WLS_FaceEnd:
            //printf("e_WLS_FaceEnd\n");
            Array_Add((void**)&data->face_list, sizeof(WavefrontLoaderFace_T), 
                      &data->face_list_count, &data->face_list_size, 
                      &face);
            state = e_WLS_Init;
            break;
         case e_WLS_MaterialLib:
            WavefrontLoader_ParseMaterialLib(data, &obj_file_buffer);
            state = e_WLS_Init;
            break;
         case e_WLS_UseMaterial:
            face.material_string_index = WavefrontLoader_ParseMaterialName(data, &obj_file_buffer);
            state = e_WLS_Init;
            break;
         default:
            //printf("default:\n");
            state = e_WLS_Unknown;
            break;
      }
   }
}


void WavefrontLoader_Load(WavefrontLoaderData_T * data, const char * filename)
{
   FILE * obj_file;

   obj_file = fopen(filename, "r");

   WavefrontLoader_Blank(data);
   if(obj_file != NULL)
   {
      WavefrontLoader_LoadFile(data, obj_file);
      fclose(obj_file);
   }
   else
   {
      printf("Error: WavefrontLoader_Load can't open file: %s\n", filename);
   }
}

static size_t WavefrontLoader_ParseFilename(WavefrontLoaderData_T * data, FileBuffer_T * file_buffer)
{
   char filename[FILENAME_MAX_SIZE];
   size_t string_index;
   string_index = 0;

   if(WavefrontLoader_ReadString(file_buffer, filename, FILENAME_MAX_SIZE) == 1)
   {

      string_index = StringArray_Add(&data->string_list, &data->string_list_count, &data->string_list_size, filename);
   }
   //printf("Parse Filename Index: %i\n", (int)string_index);

   return string_index;
}


#define MTL_CMDS_SIZE  3
static const char * mtl_cmds[MTL_CMDS_SIZE]                        = {"#",           "newmtl ",         "map_Kd "};
static const WavefrontLoaderState_T mtl_cmds_states[MTL_CMDS_SIZE] = {e_WLS_Comment, e_WLS_NewMaterial, e_WLS_MapKD};
static void WavefrontLoader_LoadMaterialFile(WavefrontLoaderData_T * data, FILE * mtl_file)
{
   StringMatchState_T string_state[MTL_CMDS_SIZE];
   WavefrontLoaderState_T state;
   FileBuffer_T mtl_file_buffer;
   int c;
   int done;
   int found_index;
   int material_started;
   WavefrontLoaderMaterial_T material;
   
   material.name_string_index  = 0;
   material.mapKd_string_index = 0;
   material_started = 0;

   FileBuffer_Init(&mtl_file_buffer, mtl_file);

   state = e_WLS_Init;
   done = 0;
   while(done == 0)
   {
      switch(state)
      {
         case e_WLS_Init:
            found_index = FILE_StringMatch(&mtl_file_buffer, mtl_cmds, string_state, MTL_CMDS_SIZE);
            //printf("e_WLS_Init: %i\n", found_index);
            if(found_index < 0)
            {
               state = e_WLS_Unknown;
            }
            else
            {
               state = mtl_cmds_states[found_index];
               
            }
            break;
         case e_WLS_Comment:
         case e_WLS_Unknown:
            c = FileBuffer_Read(&mtl_file_buffer);            
            while(c != '\n' && c != EOF)
            {
               //printf("c: %c\n", c);
               c = FileBuffer_Read(&mtl_file_buffer);
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
         case e_WLS_NewMaterial:
            if(material_started == 1)
            {
               Array_Add((void**)&data->material_list, sizeof(WavefrontLoaderMaterial_T), 
                         &data->material_list_count, &data->material_list_size, 
                         &material);
            }
            else
            {
               material_started = 1;
            }
            material.name_string_index = WavefrontLoader_ParseMaterialName(data, &mtl_file_buffer);

            state = e_WLS_Init;
            break;
         case e_WLS_MapKD:
            material.mapKd_string_index = WavefrontLoader_ParseFilename(data, &mtl_file_buffer);
            state = e_WLS_Init;
            break;
         default:
            state = e_WLS_Unknown;
            break;
      }
   }

   if(material_started == 1)
   {
      Array_Add((void**)&data->material_list, sizeof(WavefrontLoaderMaterial_T), 
            &data->material_list_count, &data->material_list_size, 
            &material);
   }
}

static void WavefrontLoader_LoadMaterialLibFile(WavefrontLoaderData_T * data, const char * filename)
{

   FILE * mtl_file;

   mtl_file = fopen(filename, "r");

   if(mtl_file != NULL)
   {
      WavefrontLoader_LoadMaterialFile(data, mtl_file);
      fclose(mtl_file);
   }
   else
   {
      printf("Error: WavefrontLoader_Load can't open file: %s\n", filename);
   }
}

void WavefrontLoader_LoadMaterialLibs(WavefrontLoaderData_T * data, const char * material_prefix_path)
{
   size_t i;
   size_t prefix_size, filename_size;
   const char * filename;
   char * full_filename;

   prefix_size = strlen(material_prefix_path);


   for(i = 0; i < data->materiallib_list_count; i++)
   {
      filename = data->string_list[data->materiallib_list[i].filename_string_index];
      filename_size = strlen(filename);
      
      full_filename = malloc(sizeof(char) * (filename_size + prefix_size + 1));
      memcpy(full_filename, material_prefix_path, prefix_size);
      memcpy(&full_filename[prefix_size], filename, filename_size);
      full_filename[prefix_size + filename_size] = '\0';


      WavefrontLoader_LoadMaterialLibFile(data, full_filename);

      
      free(full_filename); 

   }

}

void WavefrontLoader_LookupMaterial(WavefrontLoaderData_T * data)
{
   size_t i, k;
   for(i = 0; i < data->face_list_count; i++)
   {
      for(k = 0; k < data->material_list_count; k++)
      {
         if(data->face_list[i].material_string_index == data->material_list[k].name_string_index)
         {
            data->face_list[i].material_index = k;
            break;
         }
      }
   }
}

void WavefrontLoader_Delete(WavefrontLoaderData_T * data)
{
   size_t i;
   if(data->vertex_list != NULL)
   {
      free(data->vertex_list);
   }

   if(data->normal_list != NULL)
   {
      free(data->normal_list);
   }

   if(data->uv_list != NULL)
   {
      free(data->uv_list);
   }

   if(data->face_vertex_list != NULL)
   {
      free(data->face_vertex_list);
   }

   if(data->face_list != NULL)
   {
      free(data->face_list);
   }

   if(data->string_list != NULL)
   {
      for(i = 0; i < data->string_list_count; i++)
      {
         free(data->string_list[i]);
      }
      free(data->string_list);
   }

   if(data->materiallib_list != NULL)
   {
      free(data->materiallib_list);
   }

   if(data->material_list != NULL)
   {
      free(data->material_list);
   }

}


void WavefrontLoader_TEST(void)
{
   WavefrontLoaderData_T data;
   int i;
   printf("<WavefrontLoader_TEST>\n");
   WavefrontLoader_Load(&data, "assets/log.obj");
   WavefrontLoader_LoadMaterialLibs(&data, "assets/");
   WavefrontLoader_LookupMaterial(&data);

   for(i = 0; i < data.vertex_list_count; i++)
   {
      printf("v (%f, %f, %f)\n", data.vertex_list[i].x, data.vertex_list[i].y, data.vertex_list[i].z);
   }

   printf("\n");

   for(i = 0; i < data.normal_list_count; i++)
   {
      printf("n (%f, %f, %f)\n", data.normal_list[i].x, data.normal_list[i].y, data.normal_list[i].z);
   }
   printf("\n");

   for(i = 0; i < data.face_vertex_list_count; i++)
   {
      printf("f (%i, %i, %i)\n", (int)data.face_vertex_list[i].vertex_index, (int)data.face_vertex_list[i].normal_index, (int)data.face_vertex_list[i].uv_index); 
   }
   printf("\n");

   for(i = 0; i < data.face_list_count; i++)
   {
      printf("F (%i, %i) %s\n", (int)data.face_list[i].face_vertex_start_index, (int)data.face_list[i].face_vertex_count, data.string_list[data.face_list[i].material_string_index]);
   }

   printf("\n");
   for(i = 0; i < data.string_list_count; i++)
   {
      printf("String: %s\n", data.string_list[i]);
   }

   printf("\n");
   for(i = 0; i < data.materiallib_list_count; i++)
   {
      printf("MaterialLib String Index: %i\n", (int)data.materiallib_list[i].filename_string_index);
   }
   WavefrontLoader_Delete(&data);
   printf("</WavefrontLoader_TEST>\n");
}

