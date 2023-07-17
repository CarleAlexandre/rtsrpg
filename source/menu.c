#include "engine.h"

// SETTING MENU HERE
void LoopSettingMenu(Ctx *ctx) {
	/*
	Button button[N_BUTTON_SETTINGUI] = {
		{
			.bound = {
				20, 50, 20, 20
			},
		},
		{
			.bound = {

			},
			
		},
		{

		},
		{

		},
		{

		}
	};
	*/
	if (IsKeyPressed(KEY_ESCAPE))
		ctx->stats = menu; 
	BeginDrawing();
	ClearBackground(FG);	
	DrawText("Setting", 20, 20, 30, BG);
	EndDrawing();
}

// START MENU HERE
void LoopStartMenu(Ctx *ctx) {
	static bool window_close = false;
	int		i = 0;

	Button button[N_BUTTON_STARTUI] = {
		{
			.bound = {
				0, 0, 64, 32
			},
			.text = {0},//LoadTexture("./asset/button.png"),
			.pos = { 20, 50},
			.name = "play",	
		},
		{
			.bound = {
				0, 0, 64, 32
			},
			.text = {0},//LoadTexture("./asset/button.png"),
			.pos = { 104, 50},
			.name = "setting",
		},
		{
			.bound = {
				0, 0, 64, 32
			},
			.text = {0},//LoadTexture("./asset/button.png"),
			.pos = { 188, 50},
			.name = "leave",
		}
	};

	Vector2 mouse_pos = GetMousePosition();
		
	if (window_close == true) {
		if (IsKeyPressed(KEY_Y)) {
			ctx->stats = close;
		}
		else if (IsKeyPressed(KEY_N)) {
			window_close = false;
		}
	}

	if (IsKeyPressed(KEY_ESCAPE)) {
		window_close = true;
	}
	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
		while (i < N_BUTTON_STARTUI && !IsMouseInBound(button[i].bound, button[i].pos, mouse_pos))
			i++;
		switch(i) {
			case (0):
				ctx->stats = game;
				break;
			case (1):
				ctx->stats = setting;
				break;
			case (2):
				window_close = true;
				break;
			default:
				break;
		}
		i = 0;
	}
	BeginDrawing();
	ClearBackground(FG);
	//render ui element here
	for (int k = 0; k < N_BUTTON_STARTUI; k++) {
		DrawTextureRec(ctx->text[0], button[k].bound, button[k].pos, WHITE);
		DrawTextEx(ctx->font, button[k].name, (Vector2){ button[k].pos.x + 10, button[k].pos.y + button[k].bound.height * 0.5 - 6}, 22, 0, FG);
	}
	DrawText("Menu", 0, 0, 25, BG);
	if (window_close == true) {
		DrawRectangle(0, ctx->h * 0.5 - 100, ctx->w, 200, BG);
		DrawTextEx(ctx->font, "Are you sure you want to exit program? [Y/N]", (Vector2){40, ctx->h * 0.5 - 20}, 24, 0, FG);
	}
	if (IsMouseInBound(button[0].bound, button[0].pos, mouse_pos)) {
		DrawTextureRec(ctx->text[1], button[0].bound, button[0].pos, WHITE);
	}
	if (IsMouseInBound(button[0].bound, button[1].pos, mouse_pos)) {
		DrawTextureRec(ctx->text[1], button[1].bound, button[1].pos, WHITE);
	}
	if (IsMouseInBound(button[0].bound, button[2].pos, mouse_pos)) {		
		DrawTextureRec(ctx->text[1], button[2].bound, button[2].pos, WHITE);
	}
	EndDrawing();
}
