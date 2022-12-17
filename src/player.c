#include <SDL.h>
#include <math.h>
#include "simple_logger.h"
#include "gfc_types.h"
#include "gfc_input.h"
#include "gf3d_camera.h"
#include "collision.h"
#include "player.h"
#include "gf3d_sprite.h"
#include "projectile.h"
#include "gfc_vector.h"
#include "mushroom_green.h"

void player_think(Entity *self);
void player_update(Entity *self);

Entity *player_new(Vector3D position)
{
    Entity *ent = NULL;


    
    ent = entity_new();
    if (!ent)
    {
        slog("UGH OHHHH, no player for you!");
        return NULL;
    }
    
//    ent->model = gf3d_model_load("dino");
    ent->rotation.x = -3.14;
    ent->rotation.z = 0.5;
    ent->think = player_think;
    ent->update = player_update;
    vector3d_copy(ent->position,position);

    //vector3d_copy(ent->size, vector3d(50, 12, 7));
    ent->height = 120;
    ent->width = 10;
    ent->depth = 10;
    ent->health = 100;
    ent->maxHealth = 100;
    ent->cameraMove = vector2d(0,0);
    ent->type = 0;
    ent->moveType = 0;
    ent->currentSpeed = 0;
    ent->maxWalkSpeed = 2.5;
    ent->maxRunSpeed = 4;
    ent->damageBuffer = 0;
    ent->damageBufferCount = 100;
    ent->currentWeapon = 1;
    ent->hasSword1 = 1;
    ent->hasSword2 = 1;
    ent->hasBow1 = 1;
    ent->hasBow2 = 1;
    ent->hasStaff1 = 1;
    ent->hasStaff2 = 1;
    ent->hasHammer1 = 1;
    ent->hasHammer2 = 1;
    ent->hasFist1 = 1;
    ent->hasFist2 = 1;
    ent->jumpCount = 0;
    ent->jumpCountMax =1;
    ent->jumpPower = 5;
    ent->hasLifeSteal = 0;
    ent->hasSlowFall = 0;
    ent->hasSuperJump = 0;
    ent->isSlowFallActive = 0;
    ent->hasHolyShield = 0;
    ent->hasCritChance = 0;
    ent->hasKnockbackBoost = 0;
    ent->hasAguRain = 0;
    ent->hasBrokenStopwatch = 0;
    ent->hasSonicSpeed = 0;
    ent->experience = 0;
    ent->level = 0;
    ent->timeCold = 0;
    ent->skillPoints=0;
    /*

         Uint8       jumpCount;
    Uint8       jumpCountMax;
    float       jumpPower;
    Uint8       hasLifeSteal; //0 for no 1 for yes
    Uint8       hasSlowFall;// 0 for no 1 for yes
    Uint8       isSlowFallActive; //0 for no 1 for yes
    Uint8       hasHolyShield;
    Uint8       hasCritChance;
    Uint8       hasKnockbackBoost;
    Uint8       hasAguRain;
    Uint8       hasBrokenStopwatch;
    Uint8       hasSonicTime;
     */
    ent->weaponSprite = gf3d_sprite_load("images/sword.png", 128, 256, 1);
    ent->iFrame = 0;
    ent->iFrameTime = 0;
    ent->iFrameMax = 32; // i think 16 = 1 second?
    return ent;
}


void player_think(Entity *self)
{
    Vector3D forward;
    Vector3D right;
    Vector3D up;
    float moveY, moveX;
    const Uint8 * keys;
    keys = SDL_GetKeyboardState(NULL); // get the keyboard state for this frame
    //int newMouseX, newMouseY, currentMouseX, currentMouseY;
    //Vector2D cameraChangeVector = {0,0};
    //newMouseX = SDL_GetMouseState(&newMouseX,&newMouseY);
SDL_PumpEvents();

    //if( self->rotation.x >= 6.
    //if(self->rotation.z >= 6.283) self->rotation.z = 0;
    //else if(self->rotation.z <=0) self->rotation.z =6.283;



    //if(self->rotation.z<= 0
    //wif(self->rotation.z <= 0) self->rotation.z = 6.283 - self->rotation.z;
    //slog("z: %f", self->rotation.z);


    vector3d_angle_vectors(self->rotation, &forward, &right, &up);
    vector3d_set_magnitude(&forward,0.1);
    vector3d_set_magnitude(&right,0.1);
    vector3d_set_magnitude(&up,0.1);


slog("X: %f Y: %f", self->position.x, self->position.y);

    if(self->damageBuffer > 0) self->damageBuffer--;

if(self->hasBrokenStopwatch == 1)
{
 if(self->timeCold == 0)
 {
     if(gfc_random() < 0.05)self->timeCold =1;
 }
 else
 {
     if(gfc_random() < 0.05) self->timeCold = 0;
 }
}

if(gfc_input_key_pressed("o"))
{
    self->level++;
}
//old move system
    /*
    if (keys[SDL_SCANCODE_W])
    {   
        vector3d_add(self->position,self->position,forward);
    }
    if (keys[SDL_SCANCODE_S])
    {
        vector3d_add(self->position,self->position,-forward);        
    }
    if (keys[SDL_SCANCODE_D])
    {
        vector3d_add(self->position,self->position,right);
    }
    if (keys[SDL_SCANCODE_A])    
    {
        vector3d_add(self->position,self->position,-right);
    }
    if (keys[SDL_SCANCODE_SPACE])self->position.z += 0.10;
    if(self->position.z >= 0){ if (keys[SDL_SCANCODE_Z])self->position.z -= 0.10; }
    
    if (keys[SDL_SCANCODE_UP])self->rotation.x -= 0.0050;
    if (keys[SDL_SCANCODE_DOWN])self->rotation.x += 0.0050;
    if (keys[SDL_SCANCODE_RIGHT])self->rotation.z -= 0.0050;
    if (keys[SDL_SCANCODE_LEFT])self->rotation.z += 0.0050;
*/

    //temp1 = self->rotation.x * 0.1;
    //temp2 = self->rotation.z * 0.1;

    //moveY = sin(self->rotation.z+1.57);
    //moveX = cos(self->rotation.z+1.57);

    //slog("x %f, y %f", temp1, moveX);
    //slog("1 %i",temp1);

    //TODO: move this into a physics apply_velocity function
    //TODO: also sorry the random floats are divisions of pie
    //TODO: the walking is all sorts of weird sorry
    if (keys[SDL_SCANCODE_W])
    {
        moveY = sin(self->rotation.z+1.57);
        moveX = cos(self->rotation.z+1.57);
        //self->position.x += moveX;
        //self->position.y += moveY;
        //self->velocity.x += moveX;
        //self->velocity.y += moveY;
        //if(keys[SDL_SCANCODE_LSHIFT])

        if(keys[SDL_SCANCODE_LSHIFT] && self->hasSonicSpeed == 1)
        {
            if(self->currentSpeed <=self->maxRunSpeed) self->currentSpeed += 0.6;
        }
        else
        {
            if(self->currentSpeed > self->maxWalkSpeed) self->currentSpeed -= 0.6;
            if(self->currentSpeed <=self->maxWalkSpeed) self->currentSpeed += 0.3;
            if(self->currentSpeed > self->maxWalkSpeed) self->currentSpeed = self->maxWalkSpeed;

        }


        ApplyVelocity(self, vector3d(moveX*self->currentSpeed, moveY*self->currentSpeed, 0));
        self->moveType = 1;
    }
    if(keys[SDL_SCANCODE_A])
    {
        moveY = sin(self->rotation.z+3.14);
        moveX = cos(self->rotation.z+3.14);
        //self->position.x += moveX;
        //self->position.y += moveY;
if(self->currentSpeed <=self->maxWalkSpeed) self->currentSpeed += 0.3;
        ApplyVelocity(self, vector3d(moveX*self->currentSpeed*0.75, moveY*self->currentSpeed*0.75, 0));
        self->moveType = 1;


    }
    if(keys[SDL_SCANCODE_D])
    {
        moveY = sin(self->rotation.z);
        moveX = cos(self->rotation.z);
        //self->position.x += moveX;
       // self->position.y += moveY;
if(self->currentSpeed <=self->maxWalkSpeed) self->currentSpeed += 0.3;
        ApplyVelocity(self, vector3d(moveX*self->currentSpeed*0.75, moveY*self->currentSpeed*0.75, 0));
        self->moveType = 1;


    }
    if(keys[SDL_SCANCODE_S])
    {
        moveY = sin(self->rotation.z+4.71);
        moveX = cos(self->rotation.z+4.71);
        //self->position.x += moveX;
        //self->position.y += moveY;
if(self->currentSpeed <=self->maxWalkSpeed) self->currentSpeed += 0.3;
        ApplyVelocity(self, vector3d(moveX*self->currentSpeed*0.5, moveY*self->currentSpeed*0.5, 0));
        self->moveType = 1;


    }
    if(!keys[SDL_SCANCODE_W] && !keys[SDL_SCANCODE_A] && !keys[SDL_SCANCODE_S] && !keys[SDL_SCANCODE_D])
    {
        self->currentSpeed = 0;
        self->moveType = 0;
        ApplyVelocity(self, vector3d(-self->velocity.x*0.1,-self->velocity.y*0.1, 0)); //TODO only apply this while on ground eventually

    }

    //if(keys[SDL_SCANCODE_SPACE])


    //WEAPON ZONE
    if(self->hasAguRain == 1)
    {
        if(gfc_random() < 0.1)
        {
            projectile_new(vector3d(self->position.x+(gfc_random()*1000-500), self->position.y+(gfc_random()*1000-500), self->position.z+100), vector3d(0,0,-1), 100, 1);
        }
    }

    if(self->hasSlowFall == 1 && keys[SDL_SCANCODE_SPACE])
    {
        self->isSlowFallActive = 1;
    }
    else
    {
        self->isSlowFallActive = 0;
    }

    if(gfc_input_key_pressed("p"))
    {
        mushroom_green_new(self->position);
    }
    if(gfc_input_key_pressed("1"))
    {
        self->currentWeapon = 1;
        self->weaponSprite = gf3d_sprite_load("images/sword.png", 128,256, 1);
    }
    if(gfc_input_key_pressed("2"))
    {
        self->currentWeapon = 2;
        self->weaponSprite = gf3d_sprite_load("images/bow.png", 128,256, 1);
    }
    if(gfc_input_key_pressed("3"))
    {
        self->currentWeapon = 3;
        self->weaponSprite = gf3d_sprite_load("images/staff.png", 128,256, 1);
    }
    if(gfc_input_key_pressed("4"))
    {
        self->currentWeapon = 4;
        self->weaponSprite = gf3d_sprite_load("images/hammer.png", 128,256, 1);
    }
    if(gfc_input_key_pressed("5"))
    {
        self->currentWeapon = 5;
        self->weaponSprite = gf3d_sprite_load("images/fist.png", 128,256, 1);
    }

    Vector3D direction;

    if(self->cameraLock == 0 && gfc_input_key_pressed("e"))
    {
        switch(self->currentWeapon)
        {
            case 1://sword
                if(self->hasSword1 == 0) break;
                direction = vector3d(cos(self->rotation.z + 1.57), sin(self->rotation.z+1.57), sin(self->rotation.x));
                vector3d_normalize(&direction);
                //vector3d_set_magnitude(&direction, 3),
                direction.x = direction.x * 5;
                direction.y = direction.y * 5;
                direction.z = direction.z * 5;

                //Vector3D startPos = vector3d(self->position.x, self->position.y, self->position.z/2);
                projectile_new(vector3d(self->position.x, self->position.y, self->position.z), direction, 10, 0);

                break;
            case 2://bow
                if(self->hasBow1 == 0) break;
                direction = vector3d(cos(self->rotation.z + 1.57), sin(self->rotation.z+1.57), sin(self->rotation.x));
                vector3d_normalize(&direction);
                //vector3d_set_magnitude(&direction, 3),
                direction.x = direction.x * 20;
                direction.y = direction.y * 20;
                direction.z = direction.z * 20;

                //Vector3D startPos = vector3d(self->position.x, self->position.y, self->position.z/2);
                projectile_new(vector3d(self->position.x, self->position.y, self->position.z), direction, 1000, 1);

                break;
            case 3://staff
                if(self->hasStaff1 == 0) break;
                direction = vector3d(cos(self->rotation.z + 1.57), sin(self->rotation.z+1.57), sin(self->rotation.x));
                vector3d_normalize(&direction);
                //vector3d_set_magnitude(&direction, 3),

                direction.z = direction.z +2;

                //Vector3D startPos = vector3d(self->position.x, self->position.y, self->position.z/2);
                projectile_new(vector3d(self->position.x, self->position.y, self->position.z), direction, 1000, 1);

                break;
            case 4://hammer
                if(self->hasHammer1 == 0) break;

                direction = vector3d(cos(self->rotation.z + 1.57), sin(self->rotation.z+1.57), sin(self->rotation.x));
                vector3d_normalize(&direction);
                //vector3d_set_magnitude(&direction, 3),
                direction.x = direction.x * 0.5;
                direction.y = direction.y * 0.5;
                direction.z = direction.z * 0.5;

                direction.z = direction.z + 0.1;
                projectile_new(vector3d(self->position.x, self->position.y, self->position.z), direction, 40, 0);

                direction.z = direction.z + 0.2;
                projectile_new(vector3d(self->position.x, self->position.y, self->position.z), direction, 40, 0);

                direction.z = direction.z + 0.3;
                projectile_new(vector3d(self->position.x, self->position.y, self->position.z), direction, 40, 0);

                direction.z = direction.z + 0.4;
                projectile_new(vector3d(self->position.x, self->position.y, self->position.z), direction, 40, 0);

                break;
            case 5://fist
                if(self->hasFist1 == 0) break;
direction = vector3d(cos(self->rotation.z +1.57), sin(self->rotation.z+1.57), sin(self->rotation.x));
                vector3d_normalize(&direction);
                //vector3d_set_magnitude(&direction, 3),
                direction.x = direction.x + gfc_random()*0.4-0.2;
                direction.y = direction.y + gfc_random()*0.4-0.2;
                direction.z = direction.z + gfc_random()*0.4-0.2;
                projectile_new(vector3d(self->position.x, self->position.y, self->position.z), direction, 30, 0);


                direction.x = direction.x + gfc_random()*0.4-0.2;
                direction.y = direction.y + gfc_random()*0.4-0.2;
                direction.z = direction.z + gfc_random()*0.4-0.2;
                projectile_new(vector3d(self->position.x, self->position.y, self->position.z), direction, 30, 0);

                direction.x = direction.x + gfc_random()*0.4-0.2;
                direction.y = direction.y + gfc_random()*0.4-0.2;
                direction.z = direction.z + gfc_random()*0.4-0.2;
                projectile_new(vector3d(self->position.x, self->position.y, self->position.z), direction, 30, 0);

                direction.x = direction.x + gfc_random()*0.4-0.2;
                direction.y = direction.y + gfc_random()*0.4-0.2;
                direction.z = direction.z + gfc_random()*0.4-0.2;
                projectile_new(vector3d(self->position.x, self->position.y, self->position.z), direction, 30, 0);

                direction.x = direction.x + gfc_random()*0.4-0.2;
                direction.y = direction.y + gfc_random()*0.4-0.2;
                direction.z = direction.z + gfc_random()*0.4-0.2;
                projectile_new(vector3d(self->position.x, self->position.y, self->position.z), direction, 30, 0);
                break;

        }
    }

   if(self->cameraLock == 0 && gfc_input_key_pressed("q"))
    {
        switch(self->currentWeapon)
        {
            case 1://sword
                if(self->hasSword2 == 0) break;
                direction = vector3d(cos(self->rotation.z +1.57), sin(self->rotation.z+1.57), sin(self->rotation.x));
                vector3d_normalize(&direction);
                //vector3d_set_magnitude(&direction, 3),
                direction.x = direction.x + gfc_random()*0.4-0.2;
                direction.y = direction.y + gfc_random()*0.4-0.2;
                direction.z = direction.z + gfc_random()*0.4-0.2;
                projectile_new(vector3d(self->position.x, self->position.y, self->position.z), direction, 30, 0);


                direction.x = direction.x + gfc_random()*0.4-0.2;
                direction.y = direction.y + gfc_random()*0.4-0.2;
                direction.z = direction.z + gfc_random()*0.4-0.2;
                projectile_new(vector3d(self->position.x, self->position.y, self->position.z), direction, 30, 0);

                direction.x = direction.x + gfc_random()*0.4-0.2;
                direction.y = direction.y + gfc_random()*0.4-0.2;
                direction.z = direction.z + gfc_random()*0.4-0.2;
                projectile_new(vector3d(self->position.x, self->position.y, self->position.z), direction, 30, 0);

                direction.x = direction.x + gfc_random()*0.4-0.2;
                direction.y = direction.y + gfc_random()*0.4-0.2;
                direction.z = direction.z + gfc_random()*0.4-0.2;
                projectile_new(vector3d(self->position.x, self->position.y, self->position.z), direction, 30, 0);

                direction.x = direction.x + gfc_random()*0.4-0.2;
                direction.y = direction.y + gfc_random()*0.4-0.2;
                direction.z = direction.z + gfc_random()*0.4-0.2;
                projectile_new(vector3d(self->position.x, self->position.y, self->position.z), direction, 30, 0);

                break;
            case 2://bow
                if(self->hasBow2 == 0) break;
                direction = vector3d(cos(self->rotation.z + 1.57), sin(self->rotation.z+1.57), sin(self->rotation.x));
                vector3d_normalize(&direction);
                //vector3d_set_magnitude(&direction, 3),


                direction.x = direction.x * 20;
                direction.y = direction.y * 20;
                direction.z = direction.z * 20;
                projectile_new(vector3d(self->position.x, self->position.y, self->position.z), direction, 1000, 1);

                direction.x = direction.x + gfc_random();
                direction.y = direction.y + gfc_random();
                projectile_new(vector3d(self->position.x, self->position.y, self->position.z), direction, 1000, 1);


                direction.x = direction.x + gfc_random();
                direction.y = direction.y + gfc_random();
                projectile_new(vector3d(self->position.x, self->position.y, self->position.z), direction, 1000, 1);


                direction.x = direction.x + gfc_random();
                direction.y = direction.y + gfc_random();
                projectile_new(vector3d(self->position.x, self->position.y, self->position.z), direction, 1000, 1);



                break;
            case 3://staff
                if(self->hasStaff2 == 0) break;
                direction = vector3d(cos(self->rotation.z + 1.57), sin(self->rotation.z+1.57), sin(self->rotation.x));
                vector3d_normalize(&direction);
                //vector3d_set_magnitude(&direction, 3),
                direction.z = direction.z  + 0.5;

                projectile_new(vector3d(self->position.x, self->position.y, self->position.z), direction, 500, 1);

                direction.z = direction.z +1;
                projectile_new(vector3d(self->position.x, self->position.y, self->position.z), direction, 500, 1);

                                direction.z = direction.z +1.5;
                projectile_new(vector3d(self->position.x, self->position.y, self->position.z), direction, 500, 1);

                                direction.z = direction.z +2;
                projectile_new(vector3d(self->position.x, self->position.y, self->position.z), direction, 500, 1);

                                direction.z = direction.z +2.5;
                projectile_new(vector3d(self->position.x, self->position.y, self->position.z), direction, 500, 1);

                                direction.z = direction.z +3;
                projectile_new(vector3d(self->position.x, self->position.y, self->position.z), direction, 500, 1);

                                direction.z = direction.z +3.5;
                projectile_new(vector3d(self->position.x, self->position.y, self->position.z), direction, 500, 1);

                                direction.z = direction.z +4;
                projectile_new(vector3d(self->position.x, self->position.y, self->position.z), direction, 500, 1);

                                direction.z = direction.z +4.5;
                projectile_new(vector3d(self->position.x, self->position.y, self->position.z), direction, 500, 1);

                                direction.z = direction.z +5;
                projectile_new(vector3d(self->position.x, self->position.y, self->position.z), direction, 500, 1);

                break;
            case 4://hammer
                if(self->hasHammer2 == 0) break;


                  direction = vector3d(cos(self->rotation.z + 1.57), sin(self->rotation.z+1.57), sin(self->rotation.x));
                vector3d_normalize(&direction);
                //vector3d_set_magnitude(&direction, 3),
                direction.x = direction.x * 1;
                direction.y = direction.y * 1;
                direction.z = direction.z * 1;

                direction.z = direction.z + 0.1;
                projectile_new(vector3d(self->position.x, self->position.y, self->position.z), direction, 60, 0);

                direction.z = direction.z + 0.2;
                projectile_new(vector3d(self->position.x, self->position.y, self->position.z), direction, 60, 0);

                direction.z = direction.z + 0.3;
                projectile_new(vector3d(self->position.x, self->position.y, self->position.z), direction, 60, 0);

                direction.z = direction.z + 0.4;
                projectile_new(vector3d(self->position.x, self->position.y, self->position.z), direction, 60, 0);


                direction.z = direction.z - 0.1;
                projectile_new(vector3d(self->position.x, self->position.y, self->position.z), direction, 60, 0);

                direction.z = direction.z - 0.2;
                projectile_new(vector3d(self->position.x, self->position.y, self->position.z), direction, 60, 0);

                direction.z = direction.z - 0.3;
                projectile_new(vector3d(self->position.x, self->position.y, self->position.z), direction, 60, 0);

                direction.z = direction.z - 0.4;
                projectile_new(vector3d(self->position.x, self->position.y, self->position.z), direction, 60, 0);


                break;
            case 5://fist
                if(self->hasFist2 == 0) break;

                break;

        }
    }


    //WEAPON ZONE




    if(gfc_input_key_pressed(" ") && self->jumpCount > 0)
    {
        self->jumpCount--;
        self->velocity.z = 0;
        if(self->hasSuperJump == 1)
        {
                        ApplyVelocity(self, vector3d(0,0, 10));

        }
        else
        {
                        ApplyVelocity(self, vector3d(0,0, 5));


        }
    }

//slog("angle: %f", self->rotation.x);

    //slog("Height? %f", self->position.z);
    if(self->cameraLock == 0)
    {
        //self->cameraMove.x +=1;
        //self->cameraMove.y += 1;
        //vector2d_set_magnitude(&self->cameraMove, 0.02);
        //
        //if((self->cameraMove.y + self->rotation.x) <= -1.57 && (self->cameraMove.y + self->rotation.x) >= -4.71)
        //{


        if(self->cameraMove.y >= 0 && self->rotation.x >= -1.57) self->cameraMove.y = 0;
        else if(self->cameraMove.y <= 0 && self->rotation.x <= -4.71) self->cameraMove.y = 0;
        else { self->rotation.x += (self->cameraMove.y * 0.1); }
        //}





        self->rotation.z += -(self->cameraMove.x * 0.1);

    }

}

void player_update(Entity *self)
{
    if (!self)return;
    gf3d_camera_set_position(self->position);
    gf3d_camera_set_rotation(self->rotation);
}

/*eol@eof*/
