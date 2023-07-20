#include "engine.h"

TextDelay	*initFadingRender(void) {
	TextDelay *fadetxt = NULL;

	fadetxt = malloc(sizeof(TextDelay) * MAX_FADE_TEXT);
	assert(fadetxt);

	for(int i = 0; i < MAX_FADE_TEXT; i++) {
		fadetxt[i] = (TextDelay){
			.delay = 0,
			.alpha = 1,
			.color = WHITE,
			.fmt = NULL,
			.font_size = 20,
			.time = 0,
			.pos = (Vector2){0, 0},
		};
	}
	return (fadetxt);
}

TextDelay *createFadingText(const char* text, double delay, Color color, int font_size, Vector2 pos) {
    TextDelay	*ft;
    
	ft = malloc(sizeof(TextDelay));
	assert(ft);
	ft->fmt = flstrdup(text);
	assert(ft->fmt);
	ft->delay = delay;
	ft->alpha = 1.0f;
	ft->color = color;
	ft->font_size = font_size;
	ft->pos = pos;
	ft->time = 0.0f;
    return (ft);
}

//cannot spawn two time this function for different element as it will sync them on the shortest one
int RenderTextDelay(TextDelay *td, double delta_time) {
	if (td->time >= td->delay || td->fmt == NULL) {
		return (1);
	}
	td->alpha = ((td->delay - td->time) / td->delay);
	DrawText(td->fmt, td->pos.x, td->pos.y, td->font_size, Fade(td->color, td->alpha));
	td->time += delta_time;
	return (0);
}
