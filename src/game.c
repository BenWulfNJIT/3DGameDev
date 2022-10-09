#include <SDL.h>            

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

extern int __DEBUG;

int main(int argc,char *argv[])
{
    int done = 0;
    int a;
    
    Sprite *mouse = NULL;
    int mousex,mousey;

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
    
    w = world_load("config/testworld.json");

    //w = world_load("config/grassTest.json");
    for (a = 0; a < 10;a++)
    {
        agumon_new(vector3d(a * 10 -50,0,0));
    }
    
    slog_sync();
    gf3d_camera_set_scale(vector3d(1,1,1));
    player = player_new(vector3d(1200,-1200,500));


    player->cameraLock = 0;

    
    //WULF
    int beginTime = 0;
    Uint8 snapCamera = 0;
    float startMouseX, startMouseY, diffX, diffY;

    SDL_SetRelativeMouseMode(1);
    SDL_SetWindowGrab(gf3d_vgraphics_get_SDL_Window(), 1);

    int screenWidth, screenHeight;

    SDL_GetWindowSize(gf3d_vgraphics_get_SDL_Window(), &screenWidth, &screenHeight);

    //WULF


    // main game loop
    slog("gf3d main loop begin");
    while(!done)
    {

        //WULF
        beginTime = SDL_GetTicks64();
    //slog("x: %f, y: %f, z: %f", player->rotation.x, player->rotation.y, player->rotation.z);
        slog("height: %f", player->position.z);



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
                if(player->cameraLock)
                {
                    gf3d_sprite_draw(mouse,vector2d(mousex,mousey),vector2d(2,2),(Uint32)mouseFrame);
                }

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
