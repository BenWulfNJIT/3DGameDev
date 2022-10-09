#include "physics.h"



void ApplyVelocity(Entity* ent, Vector3D velocity)
{

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
