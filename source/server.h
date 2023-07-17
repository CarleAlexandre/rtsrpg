#include <stdlib.h>
#include <stdio.h>

#ifdef WIN32
	#undef UNICODE
	#define WIN32_LEAN_AND_MEAN

	#include <windows.h>
	#include <winsock2.h>
	#include <ws2tcpip.h>
#elif _unix_
	#include <>
#endif

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"

typedef struct Vector2 {
		float x, y;
} Vec2;

typedef struct Vector3 {
		float x, y, z;
} Vec3;

typedef struct s_Data {
	int	id;
	Vec2	pos;
} Data;
