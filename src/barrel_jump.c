#include <math.h>
#include "barrel_jump.h"
#include "simple_logger.h"
#include "collision.h"
#include "physics.h"


void barrel_jump_think(Entity* self);

Entity* barrel_jump_new(Vector3D position)
{

    Entity *ent = NULL;

    ent = entity_new();
    if (!ent)
    {
        slog("Failed to create barrel_jump");
        return NULL;
    }

    ent->model = gf3d_model_load("barrel_jump"); //change to mushroom //mushroom_black


    ent->height = 10;
    ent->width = 16;
    ent->depth = 16;
    ent->health = 1;
    ent->damageBuffer = 0;
    ent->damageBufferCount = 60;
    ent->initSize = GetOrigModelSize("models/barrel_jump.obj");
    //ent->size.x = 8; //height
    //ent->size.y = 16; //width
    //ent->size.z = 16; //depth


    //scale.x = width.x/orig model

    vector3d_copy(ent->scale, vector3d(ent->width/ent->initSize.x, ent->depth/ent->initSize.y, ent->height/ent->initSize.z));



    ent->think = barrel_jump_think;
    ent->type = 1; //monster


    vector3d_copy(ent->position,position);
    return ent;

}

void barrel_jump_think(Entity* self)
{
    if (!self)return;

    Entity* player = GetPlayer();

    self->velocity.x = 0;
        self->velocity.y = 0;
    self->velocity.z = 0;

    if(BadCollisionCheck(self, player) == 1)
    {
        ApplyVelocity(player, vector3d(0,0,20));
    }



}








