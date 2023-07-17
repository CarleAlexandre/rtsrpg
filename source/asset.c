#include "engine.h"

Texture2D *LoadTextureAtlas() {
	Texture2D	*atlas;
	
	atlas = malloc(sizeof(Texture2D) * N_TEXTURE);
	if (atlas == NULL)
		return (NULL);
	atlas[0] = LoadTexture("asset/texture/button.png");
	atlas[1] = LoadTexture("asset/texture/highlight.png");
	atlas[2] = LoadTexture("asset/texture/character.png");
	return (atlas);
}

void UnloadTextureAtlas(Texture2D *atlas) {
	for (int i = 0; i < N_TEXTURE; i++) {
		UnloadTexture(atlas[i]);
	}
	free(atlas);
}
