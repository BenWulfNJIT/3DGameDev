#ifndef __COLLISION_H__
#define __COLLISION_H__

#include "entity.h"
#include "gfc_types.h"
#include "gfc_list.h"
#include "gfc_matrix.h"
#include "gf3d_vgraphics.h"
#include "gf3d_model.h"
#include "gfc_vector.h"


/**
 * @brief unused right now
 */
typedef struct Hitbox_Cluster_S
{
    int     hitboxClusterCount;
    Vector4D* hitboxCluster;

}Hitbox_Cluster;

/**
 * @brief unused right now
 */
Hitbox_Cluster *CreateHitboxCluster();

/**
 * @brief used as a bad collision system
 * @returns 0 if not colliding, 1 if colliding
 */
//Uint8 BadCollisionCheck(Entity* ent1, Entity* ent2);


#endif
