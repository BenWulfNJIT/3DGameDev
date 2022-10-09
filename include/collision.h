#ifndef __COLLISION_H__
#define __COLLISION_H__

#include "gfc_types.h"
#include "gfc_list.h"
#include "gfc_matrix.h"
#include "gf3d_vgraphics.h"
#include "gf3d_model.h"
#include "gfc_vector.h"
#include "entity.h"

typedef struct Hitbox_Cluster_S
{
    int     hitboxClusterCount;
    Vector4D* hitboxCluster;

}Hitbox_Cluster;

Hitbox_Cluster *CreateHitboxCluster();


#endif
