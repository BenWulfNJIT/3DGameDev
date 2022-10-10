#include "physics.h"



void ApplyVelocity(Entity* ent, Vector3D velocity)
{


    if(ent->type == 0) //handle any player specific velocities
    {
        if(ent->moveType == 1) //walkspeed handling
        {
            if(ent->velocity.x >= ent->maxWalkSpeed || ent->velocity.y >= ent->maxWalkSpeed)
            {
                velocity.x = 0;
                velocity.y = 0;
            }
        }
    }

    if(ent->position.z >= 10)
    {
    ent->velocity.x += velocity.x;
    ent->velocity.y += velocity.y;
    ent->velocity.z += velocity.z;


    ent->position.x += velocity.x;
    ent->position.y += velocity.y;
    ent->position.z += velocity.z;
    }
    if(ent->position.z <= 10) //VERY BAD WORLD COLLISION BUT IT WORKS FOR NOW
    {
        ent->position.z = 10;
        ent->velocity.z = 0;
    }

}
