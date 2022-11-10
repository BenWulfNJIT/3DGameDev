#include "projectile.h"
#include "physics.h"
#include "simple_logger.h"
#include "collision.h"

void projectile_think(Entity *self)
{
    if (!self)return;
    Entity* nearest;
    Entity* player = GetPlayer();
    //slog("my pos = %f", self->position.z);
    if(self->position.z <= self->height/2)//GROUNDED
    {
     //entity_free(self);
        vector3d_copy(self->velocity, vector3d(0,0,0));
            self->rotation.z += 1;

        self->ttl--;
        if(self->ttl <= 0) entity_free(self);

        return;
    }
    else//NOT GROUNDED
    {
        self->airttl--;
        if(self->airttl <= 0) entity_free(self);


        nearest = GetNearestEnemy(self);

        //slog("what %f", nearest->position.z);
        if(nearest == NULL) return;
        if(self && nearest && BadCollisionCheck(self, nearest) == 1)
        {
         DoDamage(player, nearest, 100);
         Vector3D knockback = vector3d(nearest->position.x - player->position.x,nearest->position.y - player->position.y,5);
         vector3d_normalize(&knockback);
         knockback.x = knockback.x * 1.5;
        knockback.y = knockback.y * 1.5;
         knockback.z = 2;
        if(player->hasKnockbackBoost == 1)
        {
         knockback.x = knockback.x * 1.5;
         knockback.y = knockback.y * 1.5;
        }
         ApplyVelocity(nearest, knockback);
        }
       //if(BadCollisionCheck(self, GetNearestEnemy(self)))
       //{
        //slog("wompin");
       //}
    }

    self->rotation.z += 1;
    //think

}
void projectile_think(Entity *self);

Entity *projectile_new(Vector3D position, Vector3D velocity, int airttl, int gravity)
{
    Entity *ent = NULL;

    ent = entity_new();
    if (!ent)
    {
        slog("UGH OHHHH, no projectile for you!");
        return NULL;
    }

    ent->model = gf3d_model_load("dino");
    //ent->model->filename = "dino";

    //gfc_matrix_identity(ent->modelMat);
    //gfc_matrix_scale(ent->modelMat, vector3d(100,100,100));
    //gfc_matrix_translate(ent->modelMat, vector3d(1000,-1200,20));
    //ent->scale = vector3d(100,100,100);
    ent->height = 0.5;
    ent->width = 0.5;
    ent->depth = 0.5;
    ent->think = projectile_think;
    ent->type = 4;
    ent->team = 1;
    ent->ttl = 180;
    ent->airttl = airttl;
    ent->hasGravity = gravity;
    vector3d_copy(ent->position,position);
    vector3d_copy(ent->velocity, velocity);
    return ent;
}
