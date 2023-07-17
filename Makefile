NAME		=	client

SERVER_NAME	=	server

BUILDDIR	=	build/

CC			=	gcc

CFLAGS		=	-Wall -Wextra -Werror -pedantic -std=c99 #-O2 

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

SERVER_SRC	+=	source/server.c

#$(wildcard ./source/*.c)

INCLUDE		=	-Iinclude
LIBS		=	-lraylib -lopengl32 -lgdi32 -lwinmm C:/Users/emilia/Desktop/fat_std/build/fatlib.a

$(NAME)		:	$(OBJ)
		$(CC) $(OBJ) ${LIBS} -o $@

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

