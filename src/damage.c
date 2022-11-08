#include "damage.h"
#include "simple_logger.h"

void DoDamage(Entity* attacker, Entity* receiver, int damage)
{

    if(attacker->type == 0) //PLAYER ATTACKER INTERACTIONS
    {


        if(receiver->type ==1)//PLAYER ATTACKIGN MONSTER
        {

            if(receiver->damageBuffer > 0) return;

            receiver->health -= damage;
            //slog("HELELLEOEOEOELEOLE???");
            receiver->damageBuffer = receiver->damageBufferCount;
            if(receiver->health < 0) // mob died
            {
                receiver->health = 0;
                //entity_free(receiver);
                return;
            }


        }
    }

    if(attacker->type == 1) //MONSTER SPECIFIC ATTACKS
    {
        if(receiver->type == 1) return; //ignore friendly fire

        if(receiver->type == 0) //monster attacking player
        {


            if(receiver->damageBuffer > 0) return;

            receiver->health -= damage;
            receiver->damageBuffer = receiver->damageBufferCount;
            if(receiver->health < 0) //player died lol
            {
                receiver->health = 0;
                return;
            }
                        slog("HEALTH: %f", receiver->health);


        }



    }

}
