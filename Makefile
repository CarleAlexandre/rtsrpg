NAME		=	client

SERVER_NAME	=	server

BUILDDIR	=	build/

CC			=	gcc


CFLAGS		=	-Wall -Wextra -pedantic -std=c99 -O3

HEADERDIR	=	include/

HEADER		=	${HEADERDIR}engineFramework.h

OBJ		=	$(SRC:%.c=%.o)

SERVER_OBJ	=	$(SERVER_SRC:%.c=%.o)

SRC		+=	source/math.c
SRC		+=	source/engine.c
SRC		+=	source/asset.c
SRC		+=	source/game.c
SRC		+=	source/logic.c
SRC		+=	source/menu.c
SRC		+=	source/render.c
SRC		+=	source/setting.c
SRC		+=	source/loot.c
SRC		+=	source/entity.c

SERVER_SRC	+=	source/server.c

#$(wildcard ./source/*.c)

INCLUDE		=	-I C:/mingw64/include

ifeq ($(OS), Windows_NT)
LIBS		=	-lraylib -lopengl32 -lgdi32 -lwinmm
endif
ifeq ($(shell uname -s), Linux)
LIBS		=	-lraylib -lGL -lm -lpthread -ldl -lrt -lX11
endif

$(NAME)		:	$(OBJ)
		$(CC) $(OBJ) ${LIBS} -o $@

#add this above after lib to have no console: <-mwindows -Wl,--subsystem,windows>

$(OBJ)		:	%.o	:	%.c
		$(CC) $(CFLAGS) ${INCLUDE} -c $< -o $@

$(SERVER_NAME)	:	$(OBJ)
		$(CC) $(SERVER_OBJ) ${SERVER_LIBS} -o $@

$(SERVER_OBJ)	:	%.o	:	%.c
		$(CC) $(CFLAGS) ${INCLUDE} -c $< -o $@

all		:	$(NAME) $(SERVER_NAME)

clean		:
		rm $(OBJ)

fclean		:	clean
		rm $(NAME).exe

re		:	fclean all

