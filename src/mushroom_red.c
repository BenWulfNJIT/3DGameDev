#include <math.h>
#include "mushroom_red.h"
#include "simple_logger.h"
#include "entity.h"
#include "player.h"
#include "collision.h"

void mushroom_red_think(Entity* self);

Entity* mushroom_red_new(Vector3D position)
{

    Entity *ent = NULL;

    ent = entity_new();
    if (!ent)
    {
        slog("Failed to create mushroom_red");
        return NULL;
    }

    ent->model = gf3d_model_load("mushroom_red"); //change to mushroom //mushroom_red


    ent->height = 20;
    ent->width = 14;
    ent->depth = 14;
    ent->initSize = GetOrigModelSize("models/mushroom_red.obj");
    //ent->size.x = 8; //height
    //ent->size.y = 16; //width
    //ent->size.z = 16; //depth


    //scale.x = width.x/orig model

    vector3d_copy(ent->scale, vector3d(ent->width/ent->initSize.x, ent->depth/ent->initSize.y, ent->height/ent->initSize.z));



    ent->think = mushroom_red_think;
    ent->type = 1; //monster


    /*
     * add any other monster specific stats
    */
    ent->health = 100;
    ent->damageBuffer = 0;
    ent->damageBufferCount = 60;
    ent->jumpTimer = 0;
    ent->jumpTimerMax = 100;
    ent->attacking = 0;
    ent->attackRange = 150;

    vector3d_copy(ent->position,position);
    return ent;

}

void mushroom_red_think(Entity* self)
{
    if (!self)return;

    Entity* player = GetPlayer();

    if(player)
    {
        //slog("success??");
        //slog("aaa %i", player->type);
    }
    //do think stuff
    //need to set a timer for this but

    //slog("height: %f", self->height);
    //slog("orig size: %f", self->initSize.z);
    //slog("scale %f", self->scale.z);
   // slog("pos.z %f", self->position.z);



   Uint8 colliding = BadCollisionCheck(self, player);
   if(colliding == 1 && self->attacking ==1)
   {
       //slog("COLLIDING");
       player->iFrame = 1;

       if(self->attacking == 1)
       {
            vector3d_copy(self->velocity, vector3d(0,0,0));
            Vector3D jumpDir = vector3d(self->position.x - player->position.x, self->position.y - player->position.y, 1);
            vector3d_normalize(&jumpDir);
            jumpDir.x = jumpDir.x * 1.5;
            jumpDir.y = jumpDir.y * 1.5;
            jumpDir.z = 2;


            ApplyVelocity(self, jumpDir);
       }

   }
   else
   {
       //slog("NOT COLLIDING");
   }

    if(self->position.z <= self->height/2)
    {
        //TODO: set radius check so it only does stuff in range, ya know.

        self->velocity.x = 0;
        self->velocity.y = 0;
        self->velocity.z = 0;

        self->attacking = 0;

        BillboardRotateToPlayer(self, 0.05);


        self->jumpTimer++;


        if(self->jumpTimer >= self->jumpTimerMax)
        {
        Vector3D jumpDir = vector3d(player->position.x - self->position.x , player->position.y - self->position.y, 1);
        vector3d_normalize(&jumpDir);

         float distS = ((player->position.x-self->position.x)*(player->position.x-self->position.x)) +  ((player->position.y-self->position.y)*(player->position.y-self->position.y));

        if(distS < 0) distS = distS * -1;

        distS = sqrt((int)distS);

                slog("distanceS: %f", distS);

        if(distS > self->attackRange)
        {
            jumpDir.x = jumpDir.x * 1.5;
            jumpDir.y = jumpDir.y * 1.5;
            jumpDir.z = 2;
        }
        else
        {
            jumpDir.x = jumpDir.x * 5;
            jumpDir.y = jumpDir.y * 5;
            jumpDir.z = 2;
        }


        ApplyVelocity(self, jumpDir);
        self->attacking = 1;
        self->jumpTimer = 0;
        }
    }



}








