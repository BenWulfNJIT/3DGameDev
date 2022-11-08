#include <SDL.h>            
#include <math.h>
#include "simple_logger.h"
#include "gfc_input.h"
#include "gfc_vector.h"
#include "gfc_matrix.h"

#include "gf3d_vgraphics.h"
#include "gf3d_pipeline.h"
#include "gf3d_swapchain.h"
#include "gf3d_model.h"
#include "gf3d_camera.h"
#include "gf3d_texture.h"
#include "gf3d_sprite.h"

#include "entity.h"
#include "agumon.h"
#include "player.h"
#include "world.h"
#include "physics.h"
#include "wire_frame.h"

#include "mushroom_black.h"
#include "mushroom_blue.h"
#include "mushroom_green.h"
#include "mushroom_red.h"
#include "mushroom_green_small.h"
#include "mushroom_bfm.h"


extern int __DEBUG;

int main(int argc,char *argv[])
{
    int done = 0;
    int a;
    
    Sprite *mouse = NULL;
    Sprite *healthBar = NULL;
    Sprite *crosshair = NULL;
    int mousex,mousey;
    float healthWidth, healthHeight;
    //SDL_GetWindowSize(gf3d_vgraphics_get_SDL_Window(), &screenWidth, &screenHeight);
    float mouseFrame = 0;
    World *w;
    Entity* player = NULL;


    for (a = 1; a < argc;a++)
    {
        if (strcmp(argv[a],"--debug") == 0)
        {
            __DEBUG = 1;
        }
    }
    
    init_logger("gf3d.log");    
    gfc_input_init("config/input.cfg");
    slog("gf3d begin");
    gf3d_vgraphics_init("config/setup.cfg");
    slog_sync();
    
    entity_system_init(1024);




    
    mouse = gf3d_sprite_load("images/pointer.png",32,32, 16);
    healthBar = gf3d_sprite_load("images/healthBar.png", 1000, 40, 1);
    crosshair = gf3d_sprite_load("images/crosshair.png", 32,32,1);
    w = world_load("config/testworld.json");

    //w = world_load("config/grassTest.json");
    Entity* agu = agumon_new(vector3d(4500,4500, 4000));
    agu->scale = vector3d(250,250,250);
    agu->rotation.z -= 0.7;
    //agu->rotation.x = -2;

   // gf3d_model_draw(agu->model, agu->modelMat);


    //gfc_matrix_scale(agu->modelMat, vector3d(10000,10000,10000));
    
    slog_sync();
    gf3d_camera_set_scale(vector3d(1,1,1));
    player = player_new(vector3d(1200,-1200,500));


    player->cameraLock = 0;

    //Entity* wireTest = wire_frame_line_new();
    //Entity* wireTwo = wire_frame_line_new();
    //WULF
    int beginTime = 0;
    Uint8 snapCamera = 0;
    float startMouseX, startMouseY, diffX, diffY;

    SDL_SetRelativeMouseMode(1);
    SDL_SetWindowGrab(gf3d_vgraphics_get_SDL_Window(), 1);

    int screenWidth, screenHeight;

    SDL_GetWindowSize(gf3d_vgraphics_get_SDL_Window(), &screenWidth, &screenHeight);

    //agu->scale = vector3d(10,10,10);


    //vector3d_copy(wireTest->position, vector3d(1400, -1400, 20));
    //vector3d_copy(wireTest->scale, vector3d(5,100,5));
    //vector3d_copy(wireTest->scale, vector3d(player->size.y, player->size.z, player->size.x));
    //wireTest->scale = vector3d(15,3,3);
    //WULF

    //ENEMY SPAWNS
    Entity* blackMush = mushroom_black_new(vector3d(1100,-1100,30));
    //Entity* redMush = mushroom_red_new(vector3d(1000,-1000,30));
    //Entity* greenMush = mushroom_green_new(vector3d(900,-900,30));
    //Entity* blueMush = mushroom_blue_new(vector3d(800,-800,30));
    //Entity* greenSmallMush = mushroom_green_small_new(vector3d(700,-700,30));
    //Entity* bfmMush = mushroom_bfm_new(vector3d(600,-600,30));


    //Vector3D Test = GetSize(agu);
    //Test = GetOrigModelSize(agu);
    //wireTest->scale.x += 100;
    int grow = 1; //1 for big 0 for mall
    // main game loop

    int bigTestAAA= 0;
    slog("gf3d main loop begin");
    while(!done)
    {
    //slog("orig width?: %f", Test.x);
    //slog("current width?: %f", (Test.x * agu->scale.x));
    //slog("currentWidth: %f", Test.x*agu->scale.x);


        //WULF
        beginTime = SDL_GetTicks64();
    //slog("x: %f, y: %f, z: %f", player->rotation.x, player->rotation.y, player->rotation.z);
        //slog("height: %f", player->position.z);

        //vector3d_copy(wireTest->rotation, player->rotation);
        agu->rotation.y += 0.1;
        agu->rotation.z += 0.1;
        if(agu->scale.x >= 250) grow = 0;
        else if(agu->scale.x <= 0) grow = 1;

        if(grow == 1)
        {
            vector3d_copy(agu->scale, vector3d(agu->scale.x++, agu->scale.y++, agu->scale.z++));
        }
        else if(grow == 0)
        {
            vector3d_copy(agu->scale, vector3d(agu->scale.x--, agu->scale.y--, agu->scale.z--));
        }



        /*
         * GOOD HITBOX STUFF, OFFSET FROM CHAR KINDA
         * MAKE THIS NOT ACTUALLY DRAW EVENTUALLY IDK
         *

        wireTest->scale.z = player->size.x;
        wireTest->rotation.z = player->rotation.z;
        wireTest->position.x = player->position.x+100;
        wireTest->position.y = player->position.y;
        wireTest->position.z = player->position.z - player->size.x/2;


        wireTwo->position.x = player->position.x + 100 + (player->size.y/2);
        wireTwo->position.y = player->position.y + (player->size.z + 5);
        wireTwo->position.z = player->size.x/2 + player->position.z;
*/
        //reset stuff first

        //Vector3D Test = GetSize(agu);


        //wireTest->position.x += 100;


        //wireTest->rotation.z += 0.1;
        //vector3d_copy(wireTest->scale, player->rotation);
        //vector3d_copy(wireTest->rotation, player->rotation);
        //vector3d_copy(wireTest->position, player->position);


        if(mousex == screenWidth/2 && mousey == screenHeight/2)
        {

            startMouseX = mousex;
            startMouseY = mousey;
        }
        if(!player->cameraLock) SDL_WarpMouseInWindow(gf3d_vgraphics_get_SDL_Window(), screenWidth/2, screenHeight/2);

        gfc_input_update();

        SDL_GetMouseState(&mousex,&mousey);


        diffX = (mousex - startMouseX)/16;
        diffY = (mousey - startMouseY)/16;
        //if(diffX != 0){ slog("Speed = %f", diffX); }
        player->cameraMove = vector2d(diffX, diffY);


//WULF
        mouseFrame += 0.01;
        if (mouseFrame >= 16)mouseFrame = 0;

        entity_think_all();
        entity_update_all();
        gf3d_camera_update_view();
        gf3d_camera_get_view_mat4(gf3d_vgraphics_get_view_matrix());

        //physics and collision here?
        ApplyGravity();

        // configure render command for graphics command pool
        // for each mesh, get a command and configure it from the pool
        gf3d_vgraphics_render_start();
            //3D draws
                world_draw(w);
                entity_draw_all();
            //2D draws


            //player->health--;

                if(player->cameraLock == 0)//DO GAME UI STUFF
                {

                    //HEALTH DRAW
                    gf3d_sprite_draw(player->weaponSprite, vector2d(screenWidth-128, screenHeight-256), vector2d(1,1), 1);
                    gf3d_sprite_draw(healthBar, vector2d( (-(500-((player->health/player->maxHealth)*500)))    , screenHeight-100), vector2d(1,1), 1);
                    gf3d_sprite_draw(crosshair, vector2d(screenWidth/2-16, screenHeight/2-16), vector2d(1,1), 1);

                }
                if(player->cameraLock)//DO MENU UI STUFF
                {
                    gf3d_sprite_draw(mouse,vector2d(mousex,mousey),vector2d(2,2),(Uint32)mouseFrame);

                }

                //ATTEMPT UI HERE






                gf3d_vgraphics_render_end();

        //WULF
        //Timeout to lock at 60 fps, can adjust by changing this int
        while(SDL_GetTicks64() < (beginTime + 16)){}
        //WULF

        //initial character spawn view set. it's weird idk
        if(snapCamera == 0)
        {
            player->rotation.x = -3.14;
            player->rotation.z = 0.5;
            snapCamera = 1;
        }
        if(gfc_input_key_pressed("ESCAPE"))
        {
            //slog("Pressed");
            if(!player->cameraLock)
            {
                player->cameraLock = 1;
                SDL_SetRelativeMouseMode(0);
                SDL_SetWindowGrab(gf3d_vgraphics_get_SDL_Window(), 0);




            }
            else {
                player->cameraLock = 0;
                SDL_SetRelativeMouseMode(1);
                SDL_SetWindowGrab(gf3d_vgraphics_get_SDL_Window(), 1);


            }
        }


        if (gfc_input_command_down("exit"))done = 1; // exit condition
    }    
    
    world_delete(w);
    
    vkDeviceWaitIdle(gf3d_vgraphics_get_default_logical_device());    
    //cleanup
    slog("gf3d program end");
    slog_sync();
    return 0;
}

/*eol@eof*/
