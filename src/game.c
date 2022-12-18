#include <SDL.h>
#include <SDL_ttf.h>
//#include <SDL2/SDL_mixer.h>
#include <math.h>
#include "simple_logger.h"
#include "gfc_input.h"
#include "gfc_vector.h"
#include "gfc_matrix.h"
#include "gfc_audio.h"

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

#include "barrel_experience.h"
#include "barrel_health.h"
#include "barrel_trap.h"
#include "barrel_mimic.h"
#include "barrel_jump.h"




extern int __DEBUG;

int main(int argc,char *argv[])
{
    int done = 0;
    int a;
    int GameState = 1;// 0 default, 1 title menu, 2 game, 3 editor
    Sprite *mouse = NULL;
    Sprite *healthBar = NULL;
    Sprite *crosshair = NULL;
    Sprite *skillTree = NULL;

    Sprite *doubleJump = NULL;
    Sprite* lifeSteal = NULL;
    Sprite* holyShield = NULL;
    Sprite* critChance= NULL;
    Sprite* knockBackBoost= NULL;
    Sprite* raininAgus= NULL;
    Sprite* brokenStopwatch= NULL;
    Sprite* slowFall= NULL;
    Sprite* superJump= NULL;
    Sprite* sonicSpeed= NULL;
    Sprite* title = NULL;


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


//AUDIO OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO

//Mix_Music *gMusic = NULL;
//SDL_Init(  SDL_INIT_AUDIO );
//Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 );

    gfc_audio_init(4, 4, 4, 4, 1, 1);

    Sound  * titleMusic = gfc_sound_load("audio/title.mp3",100,0);
    Sound  * dayMusic = gfc_sound_load("audio/day.mp3",100,0);
    Sound  * nightMusic = gfc_sound_load("audio/night.mp3",100,0);


    gfc_sound_play(titleMusic,-1,100,1,1);

    int nightFlag = 0;

    mouse = gf3d_sprite_load("images/pointer.png",32,32, 16);
    healthBar = gf3d_sprite_load("images/healthBar.png", 1000, 40, 1);
    crosshair = gf3d_sprite_load("images/crosshair.png", 32,32,1);
    skillTree = gf3d_sprite_load("images/skillTree.png", 700, 700, 1);


    doubleJump = gf3d_sprite_load("images/doubleJump.png", 256, 256, 1);
    lifeSteal = gf3d_sprite_load("images/lifeSteal.png", 256, 256, 1);
    holyShield = gf3d_sprite_load("images/holyShield.png", 256, 256, 1);
    critChance= gf3d_sprite_load("images/critChance.png", 256, 256, 1);
    knockBackBoost= gf3d_sprite_load("images/knockBack.png", 256, 256, 1);
    raininAgus= gf3d_sprite_load("images/raininAgus.png", 256, 256, 1);
    brokenStopwatch= gf3d_sprite_load("images/brokenStopwatch.png", 256, 256, 1);
    slowFall= gf3d_sprite_load("images/slowFall.png", 256, 256, 1);
    superJump= gf3d_sprite_load("images/superJump.png", 256, 256, 1);
    sonicSpeed= gf3d_sprite_load("images/sonicSpeed.png", 256, 256, 1);

    title = gf3d_sprite_load("images/title.png", 1920, 1080, 1);

    w = world_load("config/testworld.json");

    //w = world_load("config/grassTest.json");
    //Entity* agu = agumon_new(vector3d(4500,4500, 4000));
    //agu->scale = vector3d(250,250,250);
    //agu->rotation.z -= 0.7;
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
    /*
    Entity* blackMush = mushroom_black_new(vector3d(600,-600,30));
    Entity* redMush = mushroom_red_new(vector3d(500,-500,30));
    Entity* greenMush = mushroom_green_new(vector3d(400,-400,30));
    Entity* blueMush = mushroom_blue_new(vector3d(300,-300,30));
    //Entity* greenSmallMush = mushroom_green_small_new(vector3d(700,-700,30));
    Entity* bfmMush = mushroom_bfm_new(vector3d(200,-200,30));
*/
    /*

    Entity* healthBarrel = barrel_health_new(vector3d(1200, -1200, 30));
    Entity* experienceBarrel = barrel_experience_new(vector3d(1250, -1200, 30));
    Entity* jumpBarrel = barrel_jump_new(vector3d(1300, -1200, 30));
    Entity* mimicBarrel = barrel_mimic_new(vector3d(1350, -1200, 30));
    Entity* trapBarrel = barrel_trap_new(vector3d(1400, -1200, 30));
*/

    Entity* sky1 = sky_new(vector3d(0,2000,0), vector3d(0,0,0));
    Entity* sky2 = sky_new(vector3d(0,-2000,0),vector3d(0,0,0));
    Entity* sky3 = sky_new(vector3d(2000,0,0), vector3d(0,0,1.57));

    Entity* sky4 = sky_new(vector3d(-2000,0,0), vector3d(0,0,1.57));

    Entity* sky5 = sky_new(vector3d(400,500,3000), vector3d(1.57,0,0));









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
        /*
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

*/

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



        if(nightFlag == 1)
        {
            float num = gfc_random()*1000;

            if(num > 998)
            {
                mushroom_red_new(vector3d(gfc_random()*500+500,gfc_random()*500-500,30));

            }
            else if(num > 996)
            {
                mushroom_blue_new(vector3d(gfc_random()*500,gfc_random()*500,30));

            }
            else if(num > 994)
            {
                mushroom_blue_new(vector3d(gfc_random()*1000,gfc_random()*1000,30));

            }
            else if(num > 992)
            {
                mushroom_green_new(vector3d(gfc_random()*1000,gfc_random()*1000,30));

            }
        }
        //while(GameState == 1)//DO TITLE STUFF
        //{
/*
            gfc_input_update();

        SDL_GetMouseState(&mousex,&mousey);
        mouseFrame += 0.01;
        if (mouseFrame >= 16)mouseFrame = 0;*/
        slog("OOGA?");
        slog("OOGA!");
        //}

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
    int broke = 0;
                while(GameState == 1)
                {
                     gfc_input_update();

        SDL_GetMouseState(&mousex,&mousey);
        gf3d_vgraphics_render_start();

                    //SDL_GetMouseState(&mousex,&mousey);


                    gf3d_sprite_draw(title, vector2d(screenWidth/4, screenHeight/4), vector2d(1,1), 1);
                    gf3d_sprite_draw(mouse,vector2d(mousex,mousey),vector2d(2,2),(Uint32)mouseFrame);





                                    gf3d_vgraphics_render_end();



                                    if(gfc_input_key_pressed("l"))
                                    {
                                        GameState = 2;
                                        broke = 1;
                                        gfc_sound_play(dayMusic,-1,100,1,1);

                                        break;
                                    }

                }
                if(broke == 1)
                {
                    broke = 0;

                    continue;
                }
                slog("BROKE OUT I GUESS");
                if(player->cameraLock == 0)//DO GAME UI STUFF
                {

                    //HEALTH DRAW
                    gf3d_sprite_draw(player->weaponSprite, vector2d(screenWidth-128, screenHeight-256), vector2d(1,1), 1);
                    gf3d_sprite_draw(healthBar, vector2d( (-(500-((player->health/player->maxHealth)*500)))    , screenHeight-100), vector2d(1,1), 1);
                    gf3d_sprite_draw(crosshair, vector2d(screenWidth/2-16, screenHeight/2-16), vector2d(1,1), 1);

                    //gf3d_sprite_draw(doubleJump,vector2d(screenWidth-500, screenHeight-500), vector2d(1,1), 1);




                    if(player->level >10) player->level = 10;
                    switch(player->level)
                    {
                                                case 10:
                            gf3d_sprite_draw(sonicSpeed,vector2d(screenWidth-1280, 0), vector2d(1,1), 1);
                            player->hasSonicSpeed = 1;

                                                    case 9:
                            gf3d_sprite_draw(superJump,vector2d(screenWidth-1152, 0), vector2d(1,1), 1);
                            player->hasSuperJump = 1;
                                                    case 8:
                            gf3d_sprite_draw(slowFall,vector2d(screenWidth-1024, 0), vector2d(1,1), 1);
                            player->hasSlowFall = 1;
                                                    case 7:
                            gf3d_sprite_draw(brokenStopwatch,vector2d(screenWidth-896, 0), vector2d(1,1), 1);
                            player->hasBrokenStopwatch = 1;

                                                    case 6:
                            gf3d_sprite_draw(raininAgus,vector2d(screenWidth-768, 0), vector2d(1,1), 1);
                            player->hasAguRain = 1;

                                                    case 5:
                            gf3d_sprite_draw(knockBackBoost,vector2d(screenWidth-640, 0), vector2d(1,1), 1);
                            player->hasKnockbackBoost = 1;


                        case 4:
                            gf3d_sprite_draw(critChance,vector2d(screenWidth-512, 0), vector2d(1,1), 1);
                            player->hasCritChance = 1;
                        case 3:
                            gf3d_sprite_draw(holyShield,vector2d(screenWidth-384, 0), vector2d(1,1), 1);
                            player->hasHolyShield = 1;

                        case 2:
                            gf3d_sprite_draw(lifeSteal,vector2d(screenWidth-256, 0), vector2d(1,1), 1);
                            player->hasLifeSteal = 1;
                        case 1:
                            gf3d_sprite_draw(doubleJump,vector2d(screenWidth-128, 0), vector2d(1,1), 1);
                            player->jumpCountMax = 2;
                            //if(player->jumpCount < 2)player->jumpCount++;















                    }


                //slog("UHH %i", player->level);
                    //if(player->level >=1)gf3d_sprite_draw(doubleJump,vector2d(screenWidth-500, screenHeight-500), vector2d(1,1), 1);
                }
                if(player->cameraLock)//DO MENU UI STUFF
                {
                    //gf3d_sprite_draw(skillTree, vector2d(screenWidth-400,100), vector2d(1,1), 1);


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
        if(gfc_input_key_pressed("k"))
        {
         Entity* night1 = night_new(vector3d(0,1980,0), vector3d(0,0,0));
    Entity* night2 = night_new(vector3d(0,-1980,0),vector3d(0,0,0));
    Entity* night3 = night_new(vector3d(1980,0,0), vector3d(0,0,1.57));

    Entity* night4 = night_new(vector3d(-1480,0,0), vector3d(0,0,1.57));

    Entity* night5 = night_new(vector3d(400,500,2980), vector3d(1.57,0,0));
    nightFlag = 1;
                                            gfc_sound_play(nightMusic,-1,100,1,1);

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
