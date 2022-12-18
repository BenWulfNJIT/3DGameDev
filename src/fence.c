#include "fence.h"


Entity* fence_new(Vector3D position)
{
    Entity *ent = NULL;

    ent = entity_new();
    if (!ent)
    {
        slog("Failed to make FENCE!");
        return NULL;
    }

    ent->model = gf3d_model_load("fence"); //change to mushroom //mushroom_bfm


    ent->height = 80;
    ent->width = 20;
    ent->depth = 20;
    ent->initSize = GetOrigModelSize("models/fence.obj");
    //ent->size.x = 8; //height
    //ent->size.y = 16; //width
    //ent->size.z = 16; //depth

    //scale.x = width.x/orig model

    vector3d_copy(ent->scale, vector3d(ent->width/ent->initSize.x, ent->depth/ent->initSize.y, ent->height/ent->initSize.z));



    ent->type = 10; //monster


    /*
     * add any other monster specific stats
*/


    vector3d_copy(ent->position,position);
    return ent;

}
