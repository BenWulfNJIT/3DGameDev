#include "wire_frame.h"
#include "simple_logger.h"

Entity *wire_frame_line_new()
{

    Entity *ent = NULL;

    ent = entity_new();
    if (!ent)
    {
        slog("Failed to create wire_frame_line");
        return NULL;
    }

    ent->model = gf3d_model_load("cube");
    ent->type = 4;

    vector3d_copy(ent->position,vector3d(-100000,-100000,-100000));

    return ent;

}

void wire_frame_line_move(Entity* wireFrame, Vector3D startPos, Vector3D rotation, float length)
{

    wireFrame->scale.y = 1;
    wireFrame->scale.z = 1;
    if(length == -1){length = 9999999;}
    wireFrame->scale.x = length;
    vector3d_copy(wireFrame->position, startPos);
    vector3d_copy(wireFrame->rotation, rotation);
    wireFrame->position.x += 100;
    wireFrame->position.y += 100;

    wireFrame->rotation.x += 1;
        wireFrame->rotation.y += 1;
    wireFrame->rotation.z += 1;



}

