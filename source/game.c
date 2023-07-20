#include "engine.h"

int UpdatePlayer(Ctx *ctx) {
	static double acc_time;
	if (flDistance(ctx->player.pos, ctx->player.topos) > 0.01f) {
		ctx->player.pos = toTravel(ctx->player.pos, ctx->player.topos, ctx->player.attribut.speed * ctx->delta_time, ctx->delta_time);
	}
	ctx->player.bound.x = ctx->player.pos.x;
	ctx->player.bound.y = ctx->player.pos.y;\
	if (ctx->player.life < 0) {
		ctx->player.life = 0;
	}
	if (ctx->player.life > ctx->player.attribut.max_life) {
		ctx->player.life = ctx->player.attribut.max_life; 
	}
	if (acc_time >= 1) {
		if (ctx->player.life < ctx->player.attribut.max_life) {
			ctx->player.life += ctx->player.attribut.life_regen;
			ctx->fadetxt[healingtxt].delay = 0.2f;
			ctx->fadetxt[healingtxt].alpha = 0.8f;
			ctx->fadetxt[healingtxt].color = GREEN;
			ctx->fadetxt[healingtxt].fmt = flstrdup(TextFormat("%.2f", ctx->player.attribut.life_regen));
			ctx->fadetxt[healingtxt].font_size = 12;
			ctx->fadetxt[healingtxt].time = 0;
		}
		acc_time = 0;
	}
	for (int i = 0; i < MAX_FADE_TEXT; i++) {
		ctx->fadetxt[i].pos = (Vector2){ctx->player.pos.x - 48, ctx->player.pos.y - 48};
	}
	acc_time += ctx->delta_time;
	return (0);
}

int updateEntity(Ctx *ctx) {
	return (0);
}

// GAME LOGIC HERE
void GameInput(Ctx *ctx) {
	if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON) || IsMouseButtonDown(MOUSE_RIGHT_BUTTON)) {
		ctx->player.topos = screenPosToWorldPos(GetMousePosition(), ctx->player.cam.target, ctx->w, ctx->h, ctx->player.cam.zoom);
		//should move this line after pathfinding find next point and not here
		ctx->player.angle = atan2(ctx->player.topos.y - ctx->player.pos.y, ctx->player.topos.x - ctx->player.pos.x) * 180 * Q_rsqrt(PI * PI);
	}
	ctx->player.cam.zoom += ((float)GetMouseWheelMove() * 0.05f);
	Vector2 mouse_pos = GetMousePosition();
	if (IsMouseInBound((Rectangle){0, 0, ctx->w, ctx->h}, (Vector2){ 0, 0}, mouse_pos)) {
		if (mouse_pos.x <= 0) {
			mouse_pos.x = 1;
		} else if (mouse_pos.x >= ctx->w) {
			mouse_pos.x = ctx->w - 1;
		}
		if (mouse_pos.y <= 0) {
			mouse_pos.y = 1;
		} else if (mouse_pos.y >= ctx->h) {
			mouse_pos.y = ctx->h - 1;
		}
		SetMousePosition(mouse_pos.x, mouse_pos.y);
	}
	if (IsMouseInBound((Rectangle){0, 0, ctx->w, 20}, (Vector2){ 0, 0}, mouse_pos)) {
		ctx->player.cam.target.y--;
	}
	if (IsMouseInBound((Rectangle){0, 0, 20, ctx->h}, (Vector2){ 0, 0}, mouse_pos)) {
		ctx->player.cam.target.x--;
	}
	if (IsMouseInBound((Rectangle){0, 0, ctx->w, 20}, (Vector2){ 0, ctx->h - 20}, mouse_pos)) {
		ctx->player.cam.target.y++;
	}
	if (IsMouseInBound((Rectangle){0, 0, 20, ctx->h}, (Vector2){ ctx->w - 20, 0}, mouse_pos)) {
		ctx->player.cam.target.x++;
	}
	if (ctx->player.cam.zoom > 2.0f) {
		ctx->player.cam.zoom = 2.0f;
	} else if (ctx->player.cam.zoom < 0.7f) {
		ctx->player.cam.zoom = 0.7f;
	}
	switch (GetKeyPressed()) {
		//spellone
		case (KEY_Q):
			ctx->player.life -= 100;
			break;
		case (KEY_W):
		//spelltwo
			break;
		//spellthree
		case (KEY_E):
			break;
		//spellfour
		case (KEY_R):
			break;
		//interact
		case (KEY_T):
			break;
		//warp or dash or leap
		case (KEY_F):
			break;
		//center camera or jump (jump if iso or 3d game)
		case (KEY_SPACE):
			ctx->player.cam.target = ctx->player.pos;
			break;
		//openmenu
		case (KEY_ESCAPE):
			ctx->stats = menu;
			break;
		default:
			break;
	}
	if (IsKeyDown(KEY_SPACE)) {
		ctx->player.cam.target = ctx->player.pos;
	}
}

void LoopGame1(Ctx *ctx) {
	GameInput(ctx);
	UpdatePlayer(ctx);
	BeginDrawing();
	ClearBackground(BLACK);
	BeginMode2D(ctx->player.cam);
	//for (int i = 0; i < STAGE_SIZE; i++) {
	//	DrawTextureRec(ctx->stage[i].text, ctx->stage[i].rec, ctx->stage[i].pos, ctx->stage[i].tint);
	//}
	DrawTexturePro(ctx->player.text, ctx->player.textsrc, ctx->player.bound,
		ctx->player.origin, ctx->player.angle + 90,WHITE);
	DrawLine(ctx->player.pos.x, ctx->player.pos.y,
		ctx->player.topos.x, ctx->player.topos.y, RED);
	for(int i = 0; i < MAX_FADE_TEXT; i++){
		if (1 == RenderTextDelay(&(ctx->fadetxt[i]), ctx->delta_time)) {
			if (ctx->fadetxt->fmt != NULL) {
				free(ctx->fadetxt->fmt);
				ctx->fadetxt->fmt = NULL;
			}
		}
	}
	EndMode2D();
	DrawRectangle(ctx->w * 0.5 - 100, ctx->h - 60, 200, 20, RED);
	DrawRectangle(ctx->w * 0.5 - 100, ctx->h - 60, ctx->player.life * 200 / ctx->player.attribut.max_life, 20, GREEN);
	DrawText(TextFormat("%.0f/%d", ctx->player.life, ctx->player.attribut.max_life), ctx->w * 0.5 - 50, ctx->h - 60, 20, BLACK);
	EndDrawing();
}
