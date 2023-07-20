#include "engine.h"

static inline
Ctx
InitCtx(void) {
	return  ((Ctx) {
		.name = "rts",
		.w = 720,
		.h = 480,
		.stats = menu,
	});
}

static inline
Player
InitPlayer(void) {
	return ((Player) {
		.pos = {
			.x = 60,
			.y = 60
		},
		.vel = {
			.x = 0,
			.y = 0
		},
		.topos = {
			.x = 60,
			.y = 60
		},
		.cam = {
			.zoom = 1.0f,
			.rotation = 0,
			.target = {
		 		.x = 60,
				.y = 60,
			}
		},
		.bound = { 0, 0, 64, 64},
		.attribut = {
			.speed = 20000.0f,
			.max_life = 1500,
			.life_regen = 12.0f,
		},
		.origin = { 32, 32},
		.textsrc = { 0, 0, 64, 64},
	});
}

int main(void) {
	Ctx		ctx;

	ctx = InitCtx();
	InitWindow(ctx.w, ctx.h, ctx.name);
//	SetWindowState(FLAG_FULLSCREEN_MODE);
	ctx.text = LoadTextureAtlas();
	ctx.font = LoadFont("asset/font/SF_Atarian_System.ttf");
	ctx.player = InitPlayer();
	ctx.player.text = ctx.text[2];
	ctx.player.cam.offset.x = ctx.w * 0.5;
	ctx.player.cam.offset.y = ctx.h * 0.5;
	ctx.player.pos = ctx.map.spawn;
	ctx.player.life = ctx.player.attribut.max_life;
	SetTextureFilter(ctx.font.texture, TEXTURE_FILTER_TRILINEAR);
	SetTargetFPS(120);

	ctx.fadetxt = initFadingRender();
	while (ctx.stats != close) {
		ctx.delta_time = GetFrameTime();
		switch (ctx.stats){
			case (menu):
				LoopStartMenu(&ctx);
				break;
			case (game):
				LoopGame1(&ctx);
				break;
			case (setting):
				LoopSettingMenu(&ctx);
				break;
			case (pause):
				break;
			default:
				ctx.stats = close;
				break;
		}
	}
	UnloadFont(ctx.font);
	UnloadTextureAtlas(ctx.text);
	CloseWindow();
	return (0);
}
