#include "mushroom_black.h"
#include "simple_logger.h"
#include "entity.h"
#include "player.h"

void mushroom_black_think(Entity* self);

Entity* mushroom_black_new(Vector3D position)
{

    Entity *ent = NULL;

    ent = entity_new();
    if (!ent)
    {
        slog("Failed to create mushroom_black");
        return NULL;
    }

    ent->model = gf3d_model_load("mushroom_black"); //change to mushroom

    ent->size.x = 8; //height
    ent->size.y = 16; //width
    ent->size.z = 16; //depth

    vector3d_copy(ent->scale, vector3d(ent->size.y, ent->size.z, ent->size.x));

    ent->think = mushroom_black_think;
    ent->type = 1; //monster


    /*
     * add any other monster specific stats
    */

    ent->jumpTimer = 0;
    ent->jumpTimerMax = 100;


    vector3d_copy(ent->position,position);
    return ent;

}

void mushroom_black_think(Entity* self)
{
    if (!self)return;

    Entity* player = GetPlayer();

    if(player)
    {
        slog("success??");
        slog("aaa %i", player->type);
    }
    //do think stuff
    //need to set a timer for this but
    if(self->position.z <= self->size.x)
    {
        //TODO: set radius check so it only does stuff in range, ya know.
        //float test = player->position.x;
        //slog("AAAA %f", player->position.x);
        self->velocity.x = 0;
        self->velocity.y = 0;
        self->velocity.z = 0;


        float angle = atan((player->position.y - self->position.y)/(player->position.x - self->position.x));

       self->rotation.z = angle;

       slog("uh %f", self->rotation.z);


        self->jumpTimer++;
        if(self->jumpTimer >= self->jumpTimerMax)
        {
        Vector3D jumpDir = vector3d(player->position.x - self->position.x , player->position.y - self->position.y, 1);
        vector3d_normalize(&jumpDir);
        jumpDir.x = jumpDir.x * 1.5;
        jumpDir.y = jumpDir.y * 1.5;
        jumpDir.z = 2;


        //ApplyVelocity(self,vector3d(self->position.x - player->position.x, self->position.y - player->position.y, 3));
        ApplyVelocity(self, jumpDir);

        self->jumpTimer = 0;
        }
    }

}








