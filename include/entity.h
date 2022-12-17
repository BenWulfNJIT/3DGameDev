#ifndef __ENTITY_H__
#define __ENTITY_H__
#include "gfc_types.h"

#include "gf3d_model.h"

#include "collision.h"
#include "gf3d_sprite.h"

typedef struct Entity_S
{
    Uint8       _inuse;     /**<keeps track of memory usage*/
    Matrix4     modelMat;   /**<orientation matrix for the model*/
    Model      *model;      /**<pointer to the entity model to draw  (optional)*/
    void       (*think)(struct Entity_S *self); /**<pointer to the think function*/
    void       (*update)(struct Entity_S *self); /**<pointer to the update function*/
    void       (*draw)(struct Entity_S *self); /**<pointer to an optional extra draw funciton*/
    void       (*damage)(struct Entity_S *self, float damage, struct Entity_S *inflictor); /**<pointer to the think function*/
    void       (*onDeath)(struct Entity_S *self); /**<pointer to an funciton to call when the entity dies*/
    
    Uint8       cameraLock; //0 for unlock, 1 for locked
    Vector2D    cameraMove;


    Vector3D    size; // x: height, y: width, z: depth;

    //new size system?
    float       height;
    float       width;
    float       depth;




    float       iFrame; //0 for false (can be damaged) 1 for true (invincible)
    int         iFrameMax;
    int         iFrameTime;
    Uint8       attacking; //0 for not attacking, 1 for attacking
    float       attackRange;

    Vector3D    initSize;
    Vector3D    currentSize;
    //HitBox      hitbox;
    Uint8       type; //0 for player, 1 for monster, 2 for item, 3 for world, 4 for projectiles
    Uint8       team; //1 for player, 2 for monster
    Uint8       moveType; //0 for standstill, 1 for walk, 2 for sprint, 3 for air

    float       maxRunSpeed;
    float       maxWalkSpeed; //unsure of a number rn
    float       currentSpeed;

    //Enemy info
    Uint8       state; //idle, searching, fighting, fleeing? idk
    int         jumpTimerMax;
    int         jumpTimer;
    int         bfmSpawnTimer;
    int         bfmSpawnTimerMax;

    int         damageBuffer;
    int         damageBufferCount;

    Vector3D    position;  
    Vector3D    velocity;
    Vector3D    acceleration;
    
    int         ttl; //time to live for projectiles
    int         airttl;
    int         airttlMAX;
    int         hasGravity; //0 for no 1 for yes

    Uint8       hasSword1;
    Uint8       hasSword2;
    Uint8       hasBow1;
    Uint8       hasBow2;
    Uint8       hasStaff1;
    Uint8       hasStaff2;
    Uint8       hasHammer1;
    Uint8       hasHammer2;
    Uint8       hasFist1;
    Uint8       hasFist2;

    //SKILLS or whatever
    Uint8       jumpCount;
    Uint8       jumpCountMax;
    float       jumpPower;
    Uint8       hasSuperJump;
    Uint8       hasLifeSteal; //0 for no 1 for yes
    Uint8       hasSlowFall;// 0 for no 1 for yes
    Uint8       isSlowFallActive; //0 for no 1 for yes
    Uint8       hasHolyShield;
    Uint8       hasCritChance;
    Uint8       hasKnockbackBoost;
    Uint8       hasAguRain;
    Uint8       hasBrokenStopwatch;
    Uint8       hasSonicSpeed;
    Uint8       timeCold;

    int         experience;
    int         level;
    int         skillPoints;

    Uint8       giveUpgrade;

    //Animation things
    Uint8       animationState;//0 return to normal? 1 squash down, 2 stretch up
    int         squashTimer;
    int         squashTimerMax;

    Vector3D    scale;
    Vector3D    rotation;
    
    Uint8       currentWeapon; //1 for sword, 2, for bow, 3 for staff, 4 for hammer, 5 for fist
    Sprite*     weaponSprite;


    float      health;     /**<entity dies when it reaches zero*/
    float      maxHealth;
    // WHATEVER ELSE WE MIGHT NEED FOR ENTITIES
    struct Entity_S *target;    /**<entity to target for weapons / ai*/
    
    void *customData;   /**<IF an entity needs to keep track of extra data, we can do it here*/
}Entity;
/*
typedef struct HitBox_S
{
    Vector3D size;


}HitBox;
*/

/**
 * @brief initializes the entity subsystem
 * @param maxEntities the limit on number of entities that can exist at the same time
 */
void entity_system_init(Uint32 maxEntities);

/**
 * @brief provide a pointer to a new empty entity
 * @return NULL on error or a valid entity pointer otherwise
 */
Entity *entity_new();

/**
 * @brief free a previously created entity from memory
 * @param self the entity in question
 */
void entity_free(Entity *self);


/**
 * @brief Draw an entity in the current frame
 * @param self the entity in question
 */
void entity_draw(Entity *self);

/**
 * @brief draw ALL active entities
 */
void entity_draw_all();

/**
 * @brief Call an entity's think function if it exists
 * @param self the entity in question
 */
void entity_think(Entity *self);

/**
 * @brief run the think functions for ALL active entities
 */
void entity_think_all();

/**
 * @brief run the update functions for ALL active entities
 */
void entity_update_all();

/**
 * @brief perform gravity to all monsters & player
 */
void ApplyGravity();

Entity* GetPlayer();

/**
 * @brief get the original height width and depth of a model before scaling
 */
Vector3D GetOrigModelSize(char* filePath);

/**
 * @brief sets entity rotation to face player instantly
 */
void BillboardSnapToPlayer(Entity* ent);



/**
 * @brief sets entity rotation to face player at desired speed
 */
void BillboardRotateToPlayer(Entity* ent, float speed);


/**
 * @brief get angle towards player
 * @returns angle entity needs to face to be facing player
 */
float GetAngleToPlayer(Entity* ent);

Entity* GetNearestEnemy(Entity* ent);



#endif
