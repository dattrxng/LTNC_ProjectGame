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
int main(int argc, char* args[]){

}
