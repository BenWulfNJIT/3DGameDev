#include <math.h>
#include "barrel_mimic.h"
#include "simple_logger.h"
#include "mushroom_green_small.h"


void barrel_mimic_think(Entity* self);

Entity* barrel_mimic_new(Vector3D position)
{

    Entity *ent = NULL;

    ent = entity_new();
    if (!ent)
    {
        slog("Failed to create barrel_mimic");
        return NULL;
    }

    ent->model = gf3d_model_load("barrel_mimic"); //change to mushroom //mushroom_black


    ent->height = 10;
    ent->width = 16;
    ent->depth = 16;
    ent->health = 1;
    ent->damageBuffer = 0;
    ent->damageBufferCount = 60;
    ent->initSize = GetOrigModelSize("models/barrel_mimic.obj");
    //ent->size.x = 8; //height
    //ent->size.y = 16; //width
    //ent->size.z = 16; //depth


    //scale.x = width.x/orig model

    vector3d_copy(ent->scale, vector3d(ent->width/ent->initSize.x, ent->depth/ent->initSize.y, ent->height/ent->initSize.z));



    ent->think = barrel_mimic_think;
    ent->type = 1; //monster


    vector3d_copy(ent->position,position);
    return ent;

}

void barrel_mimic_think(Entity* self)
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
            mushroom_green_small_new(self->position, vector3d(1,0,2));
            mushroom_green_small_new(self->position, vector3d(-1,0,2));
            mushroom_green_small_new(self->position, vector3d(0,1,2));
            mushroom_green_small_new(self->position, vector3d(0,-1,2));
            mushroom_green_small_new(self->position, vector3d(0.5,0.5,2));
            mushroom_green_small_new(self->position, vector3d(-0.5,0.5,2));
            mushroom_green_small_new(self->position, vector3d(0.5,-0.5,2));
            mushroom_green_small_new(self->position, vector3d(-0.5,-0.5,2));

            entity_free(self);
        }


    }




}








