#include "damage.h"
#include "simple_logger.h"

void DoDamage(Entity* attacker, Entity* receiver, int damage)
{

    if(attacker->type == 0) //PLAYER ATTACKER INTERACTIONS
    {


        if(receiver->type ==1)//PLAYER ATTACKIGN MONSTER
        {

            if(attacker->hasCritChance == 1)
            {
                if(gfc_random() > 0.5) damage = damage*2;
            }
            if(attacker->hasLifeSteal == 1)
            {
             attacker->health += damage;
             if(attacker->health > attacker->maxHealth) attacker->health = attacker->maxHealth;
            }
            if(receiver->damageBuffer > 0) return;

            receiver->health -= damage;
            //slog("HELELLEOEOEOELEOLE???");
            receiver->damageBuffer = receiver->damageBufferCount;
            if(receiver->health <= 0) // mob died
            {
                receiver->health = 0;
                attacker->experience += 50;
                if(attacker->experience >= 200)
                {
                    attacker->level++;
                    attacker->experience = 0;
                    attacker->skillPoints++;
                }
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
            if(receiver->hasHolyShield)
            {
                if(gfc_random() > 0.5) damage = 0;
            }

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
