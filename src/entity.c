#include <stdlib.h>
#include <string.h>
#include "gfc_text.h"

#include "simple_logger.h"
#include "gf3d_obj_load.h"
#include "gf3d_model.h"
#include "entity.h"
#include "physics.h"

typedef struct
{
    Entity *entity_list;
    Uint32  entity_count;
    
}EntityManager;

static EntityManager entity_manager = {0};

void entity_system_close()
{
    int i;
    for (i = 0; i < entity_manager.entity_count; i++)
    {
        entity_free(&entity_manager.entity_list[i]);        
    }
    free(entity_manager.entity_list);
    memset(&entity_manager,0,sizeof(EntityManager));
    slog("entity_system closed");
}

void entity_system_init(Uint32 maxEntities)
{
    entity_manager.entity_list = gfc_allocate_array(sizeof(Entity),maxEntities);
    if (entity_manager.entity_list == NULL)
    {
        slog("failed to allocate entity list, cannot allocate ZERO entities");
        return;
    }
    entity_manager.entity_count = maxEntities;
    atexit(entity_system_close);
    slog("entity_system initialized");
}

Entity *entity_new()
{
    int i;
    for (i = 0; i < entity_manager.entity_count; i++)
    {
        if (!entity_manager.entity_list[i]._inuse)// not used yet, so we can!
        {
            entity_manager.entity_list[i]._inuse = 1;
            gfc_matrix_identity(entity_manager.entity_list[i].modelMat);
            entity_manager.entity_list[i].scale.x = 1;
            entity_manager.entity_list[i].scale.y = 1;
            entity_manager.entity_list[i].scale.z = 1;
            return &entity_manager.entity_list[i];
        }
    }
    slog("entity_new: no free space in the entity list");
    return NULL;
}

void entity_free(Entity *self)
{
    if (!self)return;
    //MUST DESTROY
    gf3d_model_free(self->model);
    memset(self,0,sizeof(Entity));
}


void entity_draw(Entity *self)
{
    if (!self)return;
    gf3d_model_draw(self->model,self->modelMat);
}

void entity_draw_all()
{
    int i;
    for (i = 0; i < entity_manager.entity_count; i++)
    {
        if (!entity_manager.entity_list[i]._inuse)// not used yet
        {
            continue;// skip this iteration of the loop
        }
        entity_draw(&entity_manager.entity_list[i]);
    }
}

void entity_think(Entity *self)
{
    if (!self)return;
    if (self->think)self->think(self);
}

void entity_think_all()
{
    int i;
    for (i = 0; i < entity_manager.entity_count; i++)
    {
        if (!entity_manager.entity_list[i]._inuse)// not used yet
        {
            continue;// skip this iteration of the loop
        }
        entity_think(&entity_manager.entity_list[i]);
    }
}


void entity_update(Entity *self)
{
    if (!self)return;
    // HANDLE ALL COMMON UPDATE STUFF
    
    vector3d_add(self->position,self->position,self->velocity);
    vector3d_add(self->velocity,self->acceleration,self->velocity);
    
    gfc_matrix_identity(self->modelMat);



        gfc_matrix_scale(self->modelMat,self->scale);
        gfc_matrix_rotate_by_vector(self->modelMat, self->modelMat, self->rotation);
    if(self->rotation.z >= 6.283) self->rotation.z = 0;
    else if(self->rotation.z <=0) self->rotation.z =6.283;

        gfc_matrix_translate(self->modelMat,self->position);

    /* old matrix rotate
    gfc_matrix_rotate(self->modelMat,self->modelMat,self->rotation.z,vector3d(0,0,1));
    gfc_matrix_rotate(self->modelMat,self->modelMat,self->rotation.y,vector3d(0,1,0));
    gfc_matrix_rotate(self->modelMat,self->modelMat,self->rotation.x,vector3d(1,0,0));
    */


    
    if (self->update)self->update(self);
}

Entity* GetPlayer()
{

    int i;
    for (i = 0; i < entity_manager.entity_count; i++)
    {
        if (!entity_manager.entity_list[i]._inuse)// not used yet
        {
            continue;// skip this iteration of the loop
        }
        //entity_update(&entity_manager.entity_list[i]);
        if(entity_manager.entity_list[i].type == 0)
        {
            return &entity_manager.entity_list[i];
        }
    }
}

void entity_update_all()
{
    int i;
    for (i = 0; i < entity_manager.entity_count; i++)
    {
        if (!entity_manager.entity_list[i]._inuse)// not used yet
        {
            continue;// skip this iteration of the loop
        }
        entity_update(&entity_manager.entity_list[i]);
    }
}

void ApplyGravity()
{
    for(int i=0; i<entity_manager.entity_count; i++)
    {
        if (!entity_manager.entity_list[i]._inuse)// not used yet
        {
            continue;// skip this iteration of the loop
        }
        else if(entity_manager.entity_list[i].type == 0 || entity_manager.entity_list[i].type == 1)
        {
            //slog("Apply gravity to player hopefully");
            ApplyVelocity(&entity_manager.entity_list[i], vector3d(0,0,-0.15));
        }
        else if(entity_manager.entity_list[i].type == 4)
        {

            ApplyVelocity(&entity_manager.entity_list[i], vector3d(0,0,-0.05));

        }

    }
}


Vector3D GetOrigModelSize(char* filePath)
{
    float minX, minY, minZ, maxX, maxY, maxZ;    //if(!object)
    //{
        //slog("Could not get object data for size");
     //   return vector3d(0,0,0);
    //}

    minX = 999999999;
    minY = 999999999;
    minZ = 999999999;
    maxX = -999999999;
    maxY = -999999999;
    maxZ = -999999999;

    ObjData *object = gf3d_obj_load_from_file(filePath);

    if(!object)
    {
        slog("failed to get object");
        return vector3d(0,0,0);
    }


    for(int i=0; i<object->vertex_count; i++)
    {

        if(object->vertices[i].x < minX) minX = object->vertices[i].x;
        if(object->vertices[i].y < minY) minY = object->vertices[i].y;
        if(object->vertices[i].z < minZ) minZ = object->vertices[i].z;

        if(object->vertices[i].x > maxX) maxX = object->vertices[i].x;
        if(object->vertices[i].y > maxY) maxY = object->vertices[i].y;
        if(object->vertices[i].z > maxZ) maxZ = object->vertices[i].z;

        //slog("idk %f", (object->vertices[i].x));

    }

    slog("Width: %f",(maxX - minX));
    //gf3d_model_free(model);

    gf3d_obj_free(object);

    return vector3d(maxX-minX, maxY-minY, maxZ-minZ);


}

void BillboardSnapToPlayer(Entity* ent)
{
}
void BillboardRotateToPlayer(Entity* ent, float speed)
{
    float angleToPlayer = GetAngleToPlayer(ent);

    float dist = ent->rotation.z - angleToPlayer;

    //slog("uhm %f", dist);
    if(dist< speed && dist > -speed) return;

    if(dist > 3.14) ent->rotation.z += speed;
    if(dist> 0 && dist < 3.14) ent->rotation.z -= speed;
    if(dist < 0 && dist> -3.14) ent->rotation.z += speed;
    if(dist < -3.14) ent->rotation.z -= speed;


}

Entity* GetNearestEnemy(Entity* ent)
{
    float tempDistSquared;
    float distanceSquared = 999999999999999;
    Entity* closestEnemy = NULL;
    for(int i=0; i<entity_manager.entity_count; i++)
    {
        if (!entity_manager.entity_list[i]._inuse)// not used yet
        {
            continue;// skip this iteration of the loop
        }
        else if(entity_manager.entity_list[i].type == 1)
        {
            //slog("1");
            tempDistSquared =  ((entity_manager.entity_list[i].position.x-ent->position.x)*(entity_manager.entity_list[i].position.x-ent->position.x)) + ((entity_manager.entity_list[i].position.y-ent->position.y)*(entity_manager.entity_list[i].position.y-ent->position.y)) + ((entity_manager.entity_list[i].position.z-ent->position.z)*(entity_manager.entity_list[i].position.z-ent->position.z));
                //        slog("2");

            if(tempDistSquared < distanceSquared )
            {
              //              slog("3");

                distanceSquared = tempDistSquared;
                closestEnemy = &entity_manager.entity_list[i];
            //slog("4");
            //slog("huh %f",closestEnemy->position.x);
            }
            //slog("Apply gravity to player hopefully");
            //ApplyVelocity(&entity_manager.entity_list[i], vector3d(0,0,-0.15));

        }


    }
    //slog("ok %f",closestEnemy->position.z);
    return closestEnemy;
}


float GetAngleToPlayer(Entity* ent)
{
    Entity* player = GetPlayer();

    float angle;

    if(player->position.x > ent->position.x && player->position.y > ent->position.y)
    {
        //first quadrant
        angle =  atan( (( player->position.y - ent->position.y ) / ( player->position.x - ent->position.x )) ) ;
        return angle + 1.57;
    }
    else if(player->position.x < ent->position.x && player->position.y > ent->position.y)
    {
        //second quadrant
        angle =  atan( (( player->position.y - ent->position.y ) / ( player->position.x - ent->position.x )) ) ;
        return angle +4.71;
    }
    else if(player->position.x < ent->position.x && player->position.y < ent->position.y)
    {
        //third quadrant
        angle =  atan( (( player->position.y - ent->position.y ) / ( player->position.x - ent->position.x )) ) ;
        return angle +4.71;
    }
    else if(player->position.x > ent->position.x && player->position.y < ent->position.y)
    {
        //third quadrant
        angle =  atan( (( player->position.y - ent->position.y ) / ( player->position.x - ent->position.x )) ) ;
        return angle +1.57;
    }
    else
    {
        return 0;
    }

}












/*eol@eof*/
