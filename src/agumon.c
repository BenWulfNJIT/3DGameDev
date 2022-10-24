
#include "simple_logger.h"
#include "agumon.h"
#include "gfc_matrix.h"



void agumon_think(Entity *self);

Entity *agumon_new(Vector3D position)
{
    Entity *ent = NULL;
    
    ent = entity_new();
    if (!ent)
    {
        slog("UGH OHHHH, no agumon for you!");
        return NULL;
    }
    
    ent->model = gf3d_model_load("dino");
    //ent->model->filename = "dino";

    //gfc_matrix_identity(ent->modelMat);
    //gfc_matrix_scale(ent->modelMat, vector3d(100,100,100));
    //gfc_matrix_translate(ent->modelMat, vector3d(1000,-1200,20));
    //ent->scale = vector3d(100,100,100);
    ent->think = agumon_think;
    ent->type = 1;
    vector3d_copy(ent->position,position);
    return ent;
}


void agumon_think(Entity *self)
{
    if (!self)return;

    //gfc_matrix_identity(self->modelMat);
    //gfc_matrix_scale(self->modelMat, vector3d(100,100,100));
    //self->rotation.x += -0.2;
    //self->rotation.y += 0.05;
    //self->scale.x += 0.01;
    //self->rotation.z += 0.01;
    //self->rotation.x += 0.01;
    //self->rotation.y += 0.01;

}

/*eol@eof*/
