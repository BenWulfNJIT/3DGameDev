#include <math.h>
#include "sky.h"
#include "simple_logger.h"
#include "collision.h"
#include "physics.h"


void sky_think(Entity* self);

Entity* sky_new(Vector3D position, Vector3D rotation)
{

    Entity *ent = NULL;

    ent = entity_new();
    if (!ent)
    {
        slog("Failed to create sky");
        return NULL;
    }

    ent->model = gf3d_model_load("sky"); //change to mushroom //mushroom_black


    ent->height = 6000;
    ent->width = 6000;
    ent->depth = 100;
    ent->health = 1;
    ent->damageBuffer = 0;
    ent->damageBufferCount = 60;
    ent->initSize = GetOrigModelSize("models/sky.obj");
    //ent->size.x = 8; //height
    //ent->size.y = 16; //width
    //ent->size.z = 16; //depth


    //scale.x = width.x/orig model

    vector3d_copy(ent->scale, vector3d(ent->width/ent->initSize.x, ent->depth/ent->initSize.y, ent->height/ent->initSize.z));

    vector3d_copy(ent->rotation, rotation);

    ent->think = sky_think;
    ent->type = 7; //monster


    vector3d_copy(ent->position,position);
    return ent;

}

void sky_think(Entity* self)
{
    if (!self)return;




}








