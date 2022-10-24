#include "physics.h"



void ApplyVelocity(Entity* ent, Vector3D velocity)
{


    if(ent->type == 0) //handle any player specific velocities
    {
        //float moveMagSquared = (ent->x * ent->x)+(ent->y * ent->y);

        if(ent->moveType == 1) //walkspeed handling
        {
            //if(ent->velocity.x >= ent->maxWalkSpeed || ent->velocity.y >= ent->maxWalkSpeed)
            {
                ent->velocity.x = 0;
                ent->velocity.y = 0;
            }
        }
    }

    if(ent->position.z >= ent->height/2) //also assuming world is at z=0
    {
    ent->velocity.x += velocity.x;
    ent->velocity.y += velocity.y;
    ent->velocity.z += velocity.z;


    ent->position.x += velocity.x;
    ent->position.y += velocity.y;
    ent->position.z += velocity.z;
    }
    if(ent->position.z < ent->height/2) //VERY BAD WORLD COLLISION BUT IT WORKS FOR NOW p.s. this assumes world is at z=0
    {
        ent->position.z = ent->height/2;
        ent->velocity.z = 0;
    }

}
