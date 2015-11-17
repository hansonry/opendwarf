#ifndef __UNITCUBE_H__
#define __UNITCUBE_H__

typedef struct UnitCube_S UnitCube_T;
struct UnitCube_S
{
   // Each side needs to be a diffrent mesh due
   // to the normals
   GLMesh_T m_front;
   GLMesh_T m_right;
   GLMesh_T m_back;
   GLMesh_T m_left;
   GLMesh_T m_top;
   GLMesh_T m_bottom;
};

void UnitCube_Init(UnitCube_T * cube);

void UnitCube_Cleanup(UnitCube_T * cube);

void UnitCube_Render(UnitCube_T * cube);

#endif // __UNITCUBE_H__



