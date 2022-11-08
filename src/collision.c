#include "simple_logger.h"
#include "collision.h"

//currently unused
//Hitbox_Cluster *CreateHitboxCluster()
//{

//}

//bool CheckCollision(Entity* attacker, Entity* receiver)
//{

    //if(attacker.type == receiver.type){return 0;} // reject friendly fire


//}
int BadCollisionCheck(Entity* ent1, Entity* ent2)
{

    //aaaaa
    float d2, colDist;
    //slog("before dist");
    d2 = ((ent2->position.x - ent1->position.x)*(ent2->position.x - ent1->position.x)) + ((ent2->position.y - ent1->position.y)*(ent2->position.y - ent1->position.y)) + ((ent2->position.z - ent1->position.z)*(ent2->position.z - ent1->position.z));
    //slog("after dist");
    colDist = (ent1->width + ent2->width) * (ent1->width + ent2->width);

    if(d2 <= colDist) return 1;
    else return 0;


}
