#ifndef __UNITCUBE_H__
#define __UNITCUBE_H__

typedef struct UnitCube_S UnitCube_T;
struct UnitCube_S
{
   GLMesh_T cube;
};

void UnitCube_Init(UnitCube_T * cube);

void UnitCube_Cleanup(UnitCube_T * cube);

void UnitCube_Render(UnitCube_T * cube);

#endif // __UNITCUBE_H__



