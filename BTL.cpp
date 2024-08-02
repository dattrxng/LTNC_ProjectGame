/*This source code copyrighted by Lazy Foo' Productions (2004-2022)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <cstdlib>
#include <sstream>
#include <SDL_ttf.h>
#include <vector>
#include <iostream>
#include <SDL_mixer.h>
#include <cmath>
//Screen dimension constants
bool quit = false;
const int SCREEN_WIDTH = 500;
const int SCREEN_HEIGHT = 750;
const int SCREEN_FPS = 60;
const int SCREEN_TICK_PER_FRAME = 1000 / SCREEN_FPS;
const int MAX_NUM_ENEMY_1=6;
const int MAX_NUM_ENEMY_2=6;
const int MAX_NUM_ENEMY_3=6;
int NUM_ENEMY3 =1;
int NUM_ENEMY1 = 3;
int NUM_ENEMY2 = 3;
const int ENEMY1_HEART = 3;
int ENEMY1_VELY = 2;
double ENEMY2_VELY = 1;
const int ENEMY2_HEART = 2;
const double ENEMY3_VELX = 1;
const int ENEMY3_HEART = 30;

const int SPEED_BACKGROUND = 1;

const int NUM_IMG_EXPLOSION = 9;
const int NUM_IMG_DOT_MOVE=9;
const int NUM_IMG_DOT_STAND=6;
const int NUM_IMG_ENEMY1=6;
const int NUM_IMG_ENEMY2=7;
const int NUM_IMG_ENEMY3=7;
const int NUM_IMG_AMO_DOT = 9;
const int NUM_IMG_SPECIAL_AMO = 8;
const int NUM_IMG_AMO_ENEMY2 = 7;
const int NUM_IMG_FOOD_HEART=8;
const int NUM_IMG_FOOD_RED=5;
const int NUM_IMG_FOOD_YELLOW=9;
const int NUM_IMG_FOOD_PURPLE=9;
const int NUM_IMG_LEVEL = 9;
//MENU
const int NUM_ITEM_MENU = 3;
const int NUM_ITEM_PAUSE = 3;
const int NUM_ITEM_GAMEOVER = 3;

bool bool_pause=false;
bool bool_game_over = false;
bool fight=true;
std::string char_tmp;
int type_amo = 0;
int time_special_amo = SCREEN_FPS*7;
int count_remain_special_amo = 0;
int DOT_HEART = 3;
int COMMON_DOT_AMO_VEL = 7;//dot_amo_vel
int MAX_DOT_AMO_VEL = 20;//dot_amo_vel
const int MAX_DOT_HEART = 3;
int SCORE =0;
int HIGH_SCORE=0;
int time;
int point=0;
double goc=0.466;
const int MAX_DAMAGE_AMO = 3;
const int COMMON_DAMAGE_AMO = 1;
int DAMAGE_AMO = COMMON_DAMAGE_AMO;

const int SPEED_ANIMATION = 5;

int count_appear_food1=0;
int SPEED_APPEAR_FOOD1 =SCREEN_FPS*10;// thoi gian xuat hien trai tim

int count_appear_special_food=0;
int SPEED_APPEAR_SPECIAL_FOOD =SCREEN_FPS*15;//thoi gian xuaat dan ddac biet

const int reload_enemy_amo =120;//reload dan enemy
int dot_amo_rate = 0;
const int common_reload_dot_amo = 15;
const int max_reload_dot_amo = 0;
int reload_dot_amo = common_reload_dot_amo;
const int time_limit_render_level = SCREEN_FPS*3;
int count_time_render_level=0;
bool level_render_success = false;
int level = 1;


std::string path_img_dot_stand="";
std::string path_img_dot_move="";
std::string path_img_enemy1="";
std::string path_img_enemy3="";
std::string path_img_enemy2="";
std::string path_img_amo_enemy2="";
std::string path_img_amo_dot="";
std::string path_img_food_heart="";
std::string path_img_food_red="";
std::string path_img_food_yellow="";
std::string path_img_food_purple="";
std::string path_img_special_amo="";
std::string path_img_explosion="";
std::string path_img_level="";


int moveY_BG=0;

int GetRandom(int min,int max){
    return min + (int)(rand()*(max-min+1.0)/(1.0+RAND_MAX));
}
std::string int_to_str(int a)
{
    std::string res;
    while (a>0)
    {
        res = char (a%10 + '0') + res;
        a/=10;
    }
  return res;
}
//Texture wrapper class

//The dot that will move around on the screen
//LTexture
//Food class
//Shuriken class
//LTimer class
// enemy class



//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//Box collision detector
bool checkCollision( SDL_Rect a, SDL_Rect b );

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

TTF_Font* gFont = NULL;
/*TTF_Font* gFont2 = NULL;
TTF_Font* gFont3 = NULL;
TTF_Font* gMenu_Font = NULL;
*/
//The window renderer
SDL_Renderer* gRenderer = NULL;

#include "LTexture.h"

LTexture gBackground;
LTexture gMenu_IMG;
LTexture Map_IMG;
LTexture gTutorial_IMG;
LTexture gPause_IMG;
LTexture gGameOver_IMG;
LTexture gHeart_Data;
LTexture Score_Data;
//Scene textures
LTexture gDotTexture_Stand[NUM_IMG_DOT_STAND];//ban than
LTexture gDotTexture_Move[NUM_IMG_DOT_MOVE];

LTexture gFoodTexture1[NUM_IMG_FOOD_HEART];//ITEM_HEART
LTexture gFoodTexture_Red[NUM_IMG_FOOD_RED];//ITEM_RED
LTexture gFoodTexture_Yellow[NUM_IMG_FOOD_YELLOW];//ITEM_YELLOW
LTexture gFoodTexture_Purple[NUM_IMG_FOOD_PURPLE];//ITEM_PURPLE

LTexture gShurikenTexture[NUM_IMG_AMO_DOT];//dan minh
LTexture gShurikenTexture_SPECIAL[NUM_IMG_SPECIAL_AMO];

LTexture gShuriken2Texture[NUM_IMG_AMO_ENEMY2];//dan dich

LTexture gEnemy1Texture[NUM_IMG_ENEMY1];//dich
LTexture gEnemy2Texture[NUM_IMG_ENEMY2];//dich2
LTexture gEnemy3Texture[NUM_IMG_ENEMY3];//dich2
LTexture gExplosion[NUM_IMG_EXPLOSION];

LTexture gTextTexture;//heart
LTexture gTextTexture2;//score
LTexture gTextTexture3;//time
LTexture gTextHighScore;//highscore
LTexture gTextMenu[NUM_ITEM_MENU];//menu
LTexture gTextPause[NUM_ITEM_PAUSE];//pause
LTexture gTextGameOver[NUM_ITEM_GAMEOVER];//gameover
LTexture gTutorial_Text;

LTexture pause_on_play;
LTexture button_img;
LTexture button_pause_img[NUM_ITEM_PAUSE];
LTexture button_gameover_img[NUM_ITEM_GAMEOVER];
LTexture LevelTexture[NUM_IMG_LEVEL];

Mix_Chunk *gKunai = NULL;

Mix_Chunk *gEnemyHurt = NULL;

Mix_Chunk* gPickItem = NULL;

Mix_Chunk* gMenuClick = NULL;
Mix_Chunk* gMenuMotion = NULL;
//food
#include "Food.h"
//shuriken
#include "Shuriken.h"
//LTimer
#include "LTimer.h"
//enemy
#include "Enemy.h"
//Dot
#include "Dot.h"
bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "DinoRun", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
				if( TTF_Init() == -1 )
				{
					printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
					success = false;
				}

				if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
				{
					printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
					success = false;
				}
			}
		}
	}

	if (success)
    {
        SDL_Surface* icon = IMG_Load("logo.png");
        SDL_SetWindowIcon(gWindow,icon);
    }
    return success;
}
bool loadMedia()
{
	//Loading success flag
	bool success = true;
	if( !Map_IMG.loadFromFile( "menu_map.png" ) )
	{
		printf( "Failed to load map texture!\n" );
		success = false;
	}
    if( !button_img.loadFromFile( "button.png" ) )
	{
		printf( "Failed to load button texture!\n" );
		success = false;
	}
	if( !gHeart_Data.loadFromFile( "data_tmp.png" ) )
	{
		printf( "Failed to load heartdata texture!\n" );
		success = false;
	}
	if( !Score_Data.loadFromFile( "data_tmp.png" ) )
	{
		printf( "Failed to load score data texture!\n" );
		success = false;
	}
	for(int i=0;i<NUM_ITEM_PAUSE;i++)
    {
         if( !button_pause_img[i].loadFromFile( "motion_button.png" ) )
        {
            printf( "Failed to load button texture!\n" );
            success = false;
        }
    }
    for(int i=0;i<NUM_ITEM_GAMEOVER;i++)
    {
         if( !button_gameover_img[i].loadFromFile( "motion_button.png" ) )
        {
            printf( "Failed to load button texture!\n" );
            success = false;
        }
    }
    if( !gGameOver_IMG.loadFromFile( "gameover.png" ) )
	{
		printf( "Failed to load button texture!\n" );
		success = false;
	}
	if( !gPause_IMG.loadFromFile( "pause_img.png" ) )
	{
		printf( "Failed to load button texture!\n" );
		success = false;
	}
	if( !pause_on_play.loadFromFile( "motion_button.png" ) )
	{
		printf( "Failed to load mottion button texture!\n" );
		success = false;
	}
    if( !gMenu_IMG.loadFromFile( "menu.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}
	if( !gTutorial_IMG.loadFromFile( "tutorial.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}

	if( !gBackground.loadFromFile( "theway.jpg" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}


	//Load press texture
    gFont = TTF_OpenFont( "font.ttf", 42 );
    if( gFont == NULL )
    {
        printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );

    }

    //end font
    //sound
	gKunai = Mix_LoadWAV( "kunaieffect.wav" );
	if( gKunai == NULL )
	{
		printf( "Failed to load kunai sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}
	gEnemyHurt = Mix_LoadWAV( "enemy_hurt.mp3" );
	if( gEnemyHurt == NULL )
	{
		printf( "Failed to load enemy sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}
	gPickItem = Mix_LoadWAV( "pickitem.wav" );
	if( gPickItem == NULL )
	{
		printf( "Failed to load kunai sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}
	gMenuClick = Mix_LoadWAV( "menu_click.mp3" );
	if( gMenuClick == NULL )
	{
		printf( "Failed to load menuclick sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}
	gMenuMotion = Mix_LoadWAV( "menu_motion.wav" );
	if( gMenuMotion == NULL )
	{
		printf( "Failed to load menumotion sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}

	//end sound
}
void close()
{
    gPause_IMG.free();
    gGameOver_IMG.free();
    pause_on_play.free();
    button_img.free();
    Map_IMG.free();

	for (int i=0;i<NUM_IMG_DOT_STAND;i++)
	gDotTexture_Stand[i].free();
	for (int i=0;i<NUM_IMG_LEVEL;i++)
	LevelTexture[i].free();

	for (int i=0;i<NUM_IMG_DOT_MOVE;i++)
	gDotTexture_Move[i].free();

    for (int i=0;i<NUM_ITEM_PAUSE;i++)
	button_pause_img[i].free();

    for (int i=0;i<NUM_ITEM_PAUSE;i++)
	gTextPause[i].free();

	for (int i=0;i<NUM_ITEM_GAMEOVER;i++)
	button_gameover_img[i].free();

    for (int i=0;i<NUM_ITEM_GAMEOVER;i++)
	gTextGameOver[i].free();

    gMenu_IMG.free();
    gTutorial_IMG.free();
	for (int i=0;i<NUM_IMG_FOOD_HEART;i++)
    gFoodTexture1[i].free();
    for (int i=0;i<NUM_IMG_FOOD_RED;i++)
    gFoodTexture_Red[i].free();
    for (int i=0;i<NUM_IMG_FOOD_YELLOW;i++)
    gFoodTexture_Yellow[i].free();
    for (int i=0;i<NUM_IMG_FOOD_PURPLE;i++)
    gFoodTexture_Purple[i].free();

    for (int i=0;i<NUM_IMG_AMO_DOT;i++)
    gShurikenTexture[i].free();
    for (int i=0;i<NUM_IMG_SPECIAL_AMO;i++)
    gShurikenTexture_SPECIAL[i].free();

    for (int i=0;i<NUM_IMG_AMO_ENEMY2;i++)
    gShuriken2Texture[i].free();

    gBackground.free();
    for (int i=0;i<NUM_IMG_ENEMY1;i++)
    gEnemy1Texture[i].free();
    for (int i=0;i<NUM_IMG_ENEMY2;i++)
    gEnemy2Texture[i].free();
    for (int i=0;i<NUM_IMG_ENEMY3;i++)
    gEnemy3Texture[i].free();
    for (int i=0;i<NUM_IMG_EXPLOSION;i++)
    gExplosion[i].free();
    gHeart_Data.free();
    Score_Data.free();
    TTF_CloseFont( gFont );
	gFont = NULL;

    gTextTexture.free();
    gTextTexture2.free();
    gTextTexture3.free();
    for (int i =0 ;i<NUM_ITEM_MENU;i++)
    gTextMenu[i].free();
    gTutorial_Text.free();
	//Destroy window
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	Mix_FreeChunk(gKunai);
    gKunai = NULL;
    Mix_FreeChunk(gEnemyHurt);
    gEnemyHurt = NULL;
    Mix_FreeChunk(gPickItem);
    gPickItem = NULL;
    Mix_FreeChunk(gMenuClick);
    gMenuClick = NULL;
    Mix_FreeChunk(gMenuMotion);
    gMenuMotion = NULL;

	//Quit SDL subsystems
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	Mix_Quit();
}
bool checkCollision( SDL_Rect a, SDL_Rect b )
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    //Calculate the sides of rect B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    //If any of the sides from A are outside of B
    if( bottomA <= topB )
    {
        return false;
    }

    if( topA >= bottomB )
    {
        return false;
    }

    if( rightA <= leftB )
    {
        return false;
    }

    if( leftA >= rightB )
    {
        return false;
    }

    //If none of the sides from A are outside B
    return true;
}
int main(int argc, char* args[]){

}
