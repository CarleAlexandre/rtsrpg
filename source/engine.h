#ifndef ENGINE_H
# define ENGINE_H

#include <raylib.h>
#include <raymath.h>
#include <rlgl.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "C:/Users/emilia/Desktop/fat_std/include/fatstd.h"

enum stats {
	menu = 0,
	game = 1,
	close = 2,
	setting = 3,
	pause = 4,
};

enum player {
	isregen = 1,
	isdamage = 2,
};

enum reservedfadingtext {
	deathtxt = 0,
	healingtxt = 1,
	damagetxt = 2,
	debufftxt = 3,
	bufftxt = 4,
};

typedef struct s_TextDelay {
	char	*fmt;
	int		font_size;
	double	delay;
	Color	color;
	double	time;
	float	alpha;
	Vector2	pos;
} TextDelay;

#define N_BUTTON_STARTUI	3
#define N_BUTTON_SETTINGUI	5
#define STAGE_SIZE			120
#define N_TEXTURE			3
#define MAX_FADE_TEXT		5

typedef struct s_Context	Ctx;
typedef struct s_Player		Player;
typedef struct s_Stage		Stage;
typedef struct s_Button		Button;
typedef struct s_Attribut	Attribut;
typedef struct s_Map		Map;

typedef struct s_Vector {
	void	*array;
	int		size;
}	Vector;

struct s_Attribut {
	int		max_life;
	int		armor;
	int		stamina;
	int		speed;
	int		weapon_masteries;
	int		agility;
	int		classes;
	float	life_regen;
};

struct s_Stage {
	Rectangle	rec;
	Texture		text;
	Vector2		pos;
	Color		tint;
};

//button, if you click on it (left mouse click + mouse is in boundaries, then execute the function)
struct s_Button {
	Rectangle	bound;
	Texture2D	text;
	Vector2		pos;
	char		*name;
};

struct s_Map {
	Stage	*stage;
	Vector2	spawn;
	int		id;
};

struct s_Player {
	Vector2		pos;
	Vector2		topos;
	Rectangle	bound;
	Texture2D	text;
	Vector2		vel;
	Camera2D	cam;
	char		*name;
	int			id;
	Attribut	attribut;
	float		angle;
	Vector2		origin;
	Rectangle	textsrc;
	double		life;
	int			last_damage_taken;
};

struct s_Context {
	int			w;
	int			h;
	int			stats;
	char		*name;
	Texture2D	*text;
	Font		font;
	Player		player;
	Map			map;
	double		delta_time;
	TextDelay	*fadetxt;
};


Vector2	worldPosToScreenPos(Vector2 world_pos, Vector2 camera_target, int s_width, int s_height, float zoom);
int	gcd(int a, int b);
float smoothStep(float t);
float flDistance(struct Vector2 a, struct Vector2 b);
float	Q_rsqrt( float number );
Vector2 toTravel(struct Vector2 current, struct Vector2 target, float velocity, float delta_time);
Vector2	screenPosToWorldPos(Vector2 screen_pos, Vector2 camera_target, int s_width, int s_height, float zoom);


Texture2D *LoadTextureAtlas();
void UnloadTextureAtlas(Texture2D *atlas); 


void LoopGame1(Ctx *ctx);
void GameInput(Ctx *ctx);
int UpdatePlayer(Ctx *ctx);

void LoopSettingMenu(Ctx *ctx);
void LoopStartMenu(Ctx *ctx);


bool IsMouseInBound(Rectangle rec, Vector2 pos, Vector2 mouse_pos);


int			RenderTextDelay(TextDelay *td, double delta_time);
TextDelay	*createFadingText(const char* text, double delay, Color color, int font_size, Vector2 pos);
TextDelay	*initFadingRender(void);

#define BG (Color){ 40, 40, 40, 255 }
#define FG (Color){ 235, 219, 178, 255 }

#endif
