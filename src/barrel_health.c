#include <math.h>
#include "barrel_health.h"
#include "simple_logger.h"


void barrel_health_think(Entity* self);

Entity* barrel_health_new(Vector3D position)
{

    Entity *ent = NULL;

    ent = entity_new();
    if (!ent)
    {
        slog("Failed to create barrel_health");
        return NULL;
    }

    ent->model = gf3d_model_load("barrel_health"); //change to mushroom //mushroom_black


    ent->height = 10;
    ent->width = 16;
    ent->depth = 16;
    ent->health = 1;
    ent->damageBuffer = 0;
    ent->damageBufferCount = 60;
    ent->initSize = GetOrigModelSize("models/barrel_health.obj");
    //ent->size.x = 8; //height
    //ent->size.y = 16; //width
    //ent->size.z = 16; //depth


    //scale.x = width.x/orig model

    vector3d_copy(ent->scale, vector3d(ent->width/ent->initSize.x, ent->depth/ent->initSize.y, ent->height/ent->initSize.z));



    ent->think = barrel_health_think;
    ent->type = 1; //monster


    vector3d_copy(ent->position,position);
    return ent;

}

void barrel_health_think(Entity* self)
{
    if (!self)return;

    Entity* player = GetPlayer();


    if(self->health == 0)
    {
        self->velocity.x = 0;
        self->velocity.y = 0;
        self->velocity.z = 0;

        self->scale.x += 0.1;
        self->scale.y += 0.1;
        self->scale.z += 0.1;

        if(self->scale.x >= 20)
        {
            player->health = player->maxHealth;
            entity_free(self);
        }


    }



}








