# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: nzenzela <nzenzela@student.le-101.fr>      +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2018/01/18 21:26:38 by jfeve        #+#   ##    ##    #+#        #
#    Updated: 2019/04/29 02:13:44 by nzenzela    ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

#******************************************************************************#
#-----------------------------------GCC----------------------------------------#
#******************************************************************************#

CC = x86_64-w64-mingw32-gcc
CC_FLAGS = -g3 -O3
SDL_FLAGS = -I/opt/local/x86_64-w64-mingw32/include/SDL2 -Dmain=SDL_main -L/opt/local/x86_64-w64-mingw32/lib -lmingw32 -lSDL2main -mwindows -Wl,--no-undefined -lm -ldinput8 -ldxguid -ldxerr8 -luser32 -lgdi32 -lwinmm -limm32 -lole32 -loleaut32 -lshell32 -lsetupapi -lversion -luuid -static-libgcc -lSDL2_mixer -lSDL2_ttf -lSDL2_image

#******************************************************************************#
#----------------------------------LIBFT---------------------------------------#
#******************************************************************************#

NAME_LIB = libft.a
PATH_LIB = ./libft/

#******************************************************************************#
#----------------------------------SDL__---------------------------------------#
#******************************************************************************#

NAME_SDLLIB = SDL2.dll
NAME_SDLTTFLIB = SDL2_ttf.dll
NAME_SDLMIXERLIB = SDL2_mixer.dll
NAME_SDLIMAGELIB = SDL2_image.dll
PATH_SDLLIB = ./lib/

#******************************************************************************#
#-----------------------------------DOOM----------------------------------------#
#******************************************************************************#

NAME = doom-nukem
PATH_SRC_DOOM = ./src/
PATH_OBJ_DOOM = ./obj/
PATH_INC_DOOM = ./incs/
FILES_DOOM = $(shell ls src | cut -d "." -f 1)
OBJ_DOOM = $(addprefix $(PATH_OBJ_DOOM), $(addsuffix .o, $(FILES_DOOM)))
SRC_DOOM = $(addprefix $(PATH_SRC_DOOM), $(addsuffix .c, $(FILES_DOOM)))
INC_DOOM = $(addprefix $(PATH_INC_DOOM), doom.h)

#******************************************************************************#
#----------------------------------RULES---------------------------------------#
#******************************************************************************#

#.PHONY = all re

all: $(NAME)

$(NAME): $(PATH_LIB)$(NAME_LIB) $(PATH_OBJ_DOOM) $(OBJ_DOOM)
	@$(CC) $(CC_FLAGS) $(SDL_FLAGS) $(OBJ_DOOM) $(PATH_LIB)$(NAME_LIB) $(PATH_SDLLIB)$(NAME_SDLLIB) $(PATH_SDLLIB)$(NAME_SDLTTFLIB) $(PATH_SDLLIB)$(NAME_SDLMIXERLIB) $(PATH_SDLLIB)$(NAME_SDLIMAGELIB)\
		-o $(NAME)
	@echo "*******\nexecutable doom-nukem cree.\n*******\n"

$(PATH_OBJ_DOOM):
	@mkdir $(PATH_OBJ_DOOM)
	@echo "*******\ndossier objet cree\n*******\n"

$(PATH_OBJ_DOOM)%.o: $(PATH_SRC_DOOM)%.c $(INC_DOOM)
	@$(CC) $(CC_FLAGS) -o $@ -c $< -I $(PATH_INC_DOOM)

$(PATH_LIB)$(NAME_LIB):
	@make -C $(PATH_LIB)
	@echo "*******\nlibft.a cree\n*******\n"

re: fclean all

re_wolf3d: fclean_doom all

#******************************************************************************#
#----------------------------------CLEAN---------------------------------------#
#******************************************************************************#

#.PHONY = clean clean_lib clean_wolf3d clean_mlx

clean_doom:
	@rm -f $(OBJ_DOOM)
	@rm -rf obj
	@echo "*******\nfichiers objet de doom-nukem supprimes\n*******\n"

clean_lib :
	@make -C $(PATH_LIB) clean
	@echo "*******\nfichiers objet de la lib supprimes\n*******\n"

clean: clean_lib clean_doom
	@echo "******\ntous les fichiers objets supprimes\n*******\n"

#******************************************************************************#
#---------------------------------FCLEAN---------------------------------------#
#******************************************************************************#

fclean_doom: clean_doom
	@rm -f $(NAME)
	@echo "*******\nExecutable doom-nukem supprime\n*******\n"

fclean_lib: clean_lib
	@make -C $(PATH_LIB) fclean
	@echo "*******\nExecutable lib supprime\n*******\n"

fclean : fclean_lib fclean_doom clean
	@echo "*******\nTout executable supprime\n*******\n"
