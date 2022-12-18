#include "npc.h"

void npc_think(Entity* self);

Entity* npc_new(Vector3D position)
{
    Entity *ent = NULL;

    ent = entity_new();
    if (!ent)
    {
        slog("Failed to make NPC!");
        return NULL;
    }

    ent->model = gf3d_model_load("npc"); //change to mushroom //mushroom_bfm


    ent->height = 60;
    ent->width = 40;
    ent->depth = 40;
    ent->initSize = GetOrigModelSize("models/npc.obj");
    //ent->size.x = 8; //height
    //ent->size.y = 16; //width
    //ent->size.z = 16; //depth

    //scale.x = width.x/orig model

    vector3d_copy(ent->scale, vector3d(ent->width/ent->initSize.x, ent->depth/ent->initSize.y, ent->height/ent->initSize.z));



    ent->type = 10; //monster
    ent->think = npc_think;

    /*
     * add any other monster specific stats
*/


    vector3d_copy(ent->position,position);
    return ent;

}


void npc_think(Entity* self)
{
    Entity* player = GetPlayer();

    float distanceSquared = ((player->position.x - self->position.x)*(player->position.x - self->position.x)) + ((player->position.y - self->position.y)*(player->position.y - self->position.y));

    if(distanceSquared < 10000)
    {
            player->displayQuest = 1;
    }
    else
    {
        player->displayQuest = 0;
    }

}
