#include <SDL.h>
#include <math.h>
#include "simple_logger.h"
#include "gfc_types.h"
#include "gfc_input.h"
#include "gf3d_camera.h"
#include "collision.h"
#include "player.h"


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
    ent->think = player_think;
    ent->update = player_update;
    vector3d_copy(ent->position,position);
    ent->rotation.x = -M_PI;
    ent->cameraMove = vector2d(0,0);
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


    //if( self->rotation.x >= 6.
    if(self->rotation.z >= 6.283) self->rotation.z = 0;
    else if(self->rotation.z <=0) self->rotation.z =6.283;


    //if(self->rotation.z<= 0
    //wif(self->rotation.z <= 0) self->rotation.z = 6.283 - self->rotation.z;
    //slog("z: %f", self->rotation.z);


    vector3d_angle_vectors(self->rotation, &forward, &right, &up);
    vector3d_set_magnitude(&forward,0.1);
    vector3d_set_magnitude(&right,0.1);
    vector3d_set_magnitude(&up,0.1);

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
    if (keys[SDL_SCANCODE_W])
    {
        moveY = sin(self->rotation.z+1.57);
        moveX = cos(self->rotation.z+1.57);
        self->position.x += moveX;
        self->position.y += moveY;
    }
    if(keys[SDL_SCANCODE_A])
    {
        moveY = sin(self->rotation.z+3.14);
        moveX = cos(self->rotation.z+3.14);
        self->position.x += moveX;
        self->position.y += moveY;
    }

    if(keys[SDL_SCANCODE_D])
    {
        moveY = sin(self->rotation.z);
        moveX = cos(self->rotation.z);
        self->position.x += moveX;
        self->position.y += moveY;
    }
    if(keys[SDL_SCANCODE_S])
    {
        moveY = sin(self->rotation.z+4.71);
        moveX = cos(self->rotation.z+4.71);
        self->position.x += moveX;
        self->position.y += moveY;
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
