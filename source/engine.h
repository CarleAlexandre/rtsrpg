#ifndef ENGINE_H
# define ENGINE_H

# ifdef _WIN64
#  include <C:/mingw64/include/raylib.h>
#  include <C:/mingw64/include/raymath.h>
#  include <C:/mingw64/include/rlgl.h>
# else
#  include <raylib.h>
#  include <raymath.h>
#  include <rlgl.h>
# endif

# include <time.h>
# include <stdint.h>
# include <stddef.h>
# include <stdbool.h>
# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <assert.h>

typedef unsigned int uint32;
typedef short i16;
typedef unsigned short u16;
typedef float f32;
typedef int	i32;
typedef unsigned int u32;
typedef double f64;
typedef long long i64;
typedef unsigned long long u64;
typedef void *ptr;

static inline
char	*flstrdup(const char *str) {
	int len = strlen(str);
	char *newptr = NULL;

	newptr = (char *)malloc(len + 1);
	assert(newptr);
	for(int i = 0; i < len; i++) {
		newptr[i] = str[i];
	}
	newptr[len] = 0x00;
	return (newptr);
}

/*
	up to 32 flag
*/
enum itemProperties {
	PLACABLE = 1 << 0,
	BREAKABLE = 1 << 1,
	TRANSPARENT = 1 << 2,
	LOOTABLE = 1 << 3,
};

/*
	Item structure 
	int		id
	int		texture index
	char	*name
	int		properties
*/
typedef struct s_Item {
	int 	id;
	int 	texture;
	char	*name;
	int		properties;
}	Item;

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
#define N_BUTTON_SETTINGUI	4
#define STAGE_SIZE			120
#define N_TEXTURE			3
#define MAX_FADE_TEXT		5

typedef struct s_Context		Ctx;
typedef struct s_Player			Player;
typedef struct s_Stage			Stage;
typedef struct s_Button			Button;
typedef struct s_Attribut		Attribut;
typedef struct s_Map			Map;
typedef struct s_EntityTemplate	EntityTemplate;
typedef struct s_Entity			Entity;
typedef struct s_LootTable		LootTable;

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

struct s_LootTable {
	u32	size;
	u32	*item_id;
	f32	*drop_rate;
};

struct s_EntityTemplate {
	float		speed;
	int			damage;
	int			life;
	int			armor;
	LootTable	loot;
};

struct s_Entity {
	char			*name;
	Vector2			pos;
	Texture2D		text;
	Vector2			toPos;
	float			speed;
	int				damage;
	int				life;
	int				armor;
	LootTable		loot;
	u32				id;
	Entity			*next;
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
	Button		*settingbutton;
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
